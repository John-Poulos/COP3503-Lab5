#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class StarShip 
{

	string _name = "";
	string _ShipClass = "";
	short _length = 0;
	int _shield = 0;
	float _warp = 0.0;	
	

public:
	
	class Weapons
	{
	public:

		string _name = "";	//name of weapon
		int _power = 0;		//power rating of weapon, how strong its attack is	
		float _usage = 0.0; //power consumption, how much power it uses
		int _wepCount = 0;	//number of weapons per ship


		Weapons() {};		//default constructor
		Weapons(string name, int power, float usage, int wepCount)
		{
			_name = name;
			_power = power;
			_usage = usage;
			_wepCount = wepCount;
		}

		string getName() { return _name; }
		int getPower() { return _power; }
		float getUsage() { return _usage; }
		int getWepCount() { return _wepCount; }

		~Weapons();

	};

	vector<StarShip::Weapons> weps; //empty vector weps of type Weapons, purpose is to be able to store the variable amounts of weapons each ship may carry
	

	StarShip() {}; //default constructor
	StarShip(string name, string ShipClass, short length, int shield, float warp, vector<Weapons> &weps)
	{
		_name = name;
		_ShipClass = ShipClass;
		_length = length;
		_shield = shield;
		_warp = warp;
		//&weps;
	}

	string getName() { return _name; }
	string getShipClass() { return _ShipClass; }
	short getLength() { return _length; }
	int getShield() { return _shield; }
	float getWarp() { return _warp; }
	vector<Weapons> getWeps() { return weps; } // do I need this?? I am returning the vector of weps
	
	~StarShip();

};

void fileSelect(int option, vector<StarShip> &ships, vector<StarShip::Weapons> &weps);
void loadData(string path, vector<StarShip> &ships, vector<StarShip::Weapons> &weps);

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;
	vector<StarShip> ships;
	vector<StarShip::Weapons> weps;
	fileSelect(option, ships, weps);

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;

	cin >> option;

	switch (option) 
	{
	case 1:
	{
		int vecSize = ships.size();
		for (int i = 0; i < vecSize; i++)
		{			
			cout << ships[i].getName() << endl;
		}

		break;
	}
	case 2:
	{
		int vecSize = weps.size();
		int tempPower = 0, maxPower = 0;
		
		for (unsigned int i = 0; i < vecSize; i++)
		{
			tempPower = weps[i].getPower();
			if (maxPower < tempPower) 
			{
				maxPower = tempPower;
			}			
		}
		cout << "Most Powerful: " << maxPower << endl;



		// search for value returned by maxPower in ships vector and return matching ship name?


		//unsigned int vecSize = ships.size();
		//int maxPower = 0, tempPower = 0;
		//for (unsigned int i = 0; i < vecSize; i++)						//iterate through each ship in the vector
		//{												 	
		//	for (unsigned int j = 0; j < ships[i].weps.size(); j++)		//iterate through each weapons list of that ship - looking for size of weapons array associated with ship [i]		
		//	{
		//		 tempPower = ships[i].weps[j].getPower();				//set power rating of weapon to temPower
		//		 if (maxPower < tempPower)								//compare between weapons until max power is found
		//		 {
		//			 maxPower = tempPower;
		//			 cout << maxPower << endl;
		//		 }
		//	}

		//}

		break;
	}
	case 3:
		break;

	case 4:
		break;

	case 5:
		break;
	}
	/* Work your magic here */

	return 0;
}


void fileSelect(int option, vector<StarShip> &ships, vector<StarShip::Weapons>& weps)
{
	switch (option)
	{
	case 1:
		loadData("friendlyships.shp", ships, weps);
		break;

	case 2:
		loadData("enemyships.shp", ships, weps);
		break;

	case 3:
		loadData("friendlyships.shp", ships, weps);
		loadData("enemyships.shp", ships, weps);
		break;
	}

}

void loadData(string path, vector<StarShip>& ships, vector<StarShip::Weapons>& weps)
{
	ifstream tempFile(path, ios_base::binary);

	if (tempFile.is_open())
	{
		int shipCount, lengthName, lengthClass, shield, wepsCount, nameLength, power;
		short meters;
		float warp, consumes;

		tempFile.read((char*)&shipCount, 4);
		//cout << shipCount << endl; //How many ships are in each file
		
		for (int i = 0; i < shipCount; i++)
		{
			//next chunk of data - after count is length of the name including the null as an int		
			tempFile.read((char*)& lengthName, 4);
			
			//next, the string data for the name itself with the null terminator, length given above		
			char* nameArray = new char[lengthName];
			tempFile.read(nameArray, lengthName * sizeof(nameArray[0]));
			string name = nameArray;
			// name of ship!

			//next, length of the ships class
			tempFile.read((char*)& lengthClass, 4);
			
			//next, the name of the Class
			char* classArray = new char[lengthClass];
			tempFile.read(classArray, lengthClass * sizeof(classArray[0]));
			string Class = classArray;
			
			//ships length in meters 2 bytes
			tempFile.read((char*)& meters, 2);
			
			//shield capacity 4 bytes
			tempFile.read((char*)& shield, 4);
			
			//warp speed 4 bytes
			tempFile.read((char*)& warp, 4);
			
			//weapons count 4 bytes 
			tempFile.read((char*)& wepsCount, 4);
			
			for (int i = 0; i < wepsCount; i++)
			{
				//length of the weapons name
				tempFile.read((char*)& nameLength, 4);
				
				//name of the weapon
				char* wepNameArray = new char[nameLength];
				tempFile.read(wepNameArray, nameLength * sizeof(wepNameArray[0]));
				string wepNames = wepNameArray;
				
				//power rating of the weapons
				tempFile.read((char*)& power, 4);
				
				//power consumption of the weapons
				tempFile.read((char*)& consumes, 4);
				
				StarShip::Weapons w(wepNames, power, consumes, wepsCount);
				weps.push_back(w);
				delete[] wepNameArray;
			}

			StarShip s(name, Class, meters, shield, warp, weps);
			ships.push_back(s);
			delete[] nameArray;
			delete[] classArray;			

		}
		
	}
	tempFile.close();
	
}


StarShip::~StarShip()
{
}

StarShip::Weapons::~Weapons()
{
}
