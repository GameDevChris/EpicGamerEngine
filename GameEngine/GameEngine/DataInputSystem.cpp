#include "DataInputSystem.h"

void DataInputSystem::ParseTextData(vector<char>* dataVector)
{
	char dataValue;
	ifstream dataFile;
	dataFile.open("data.txt");
	while (dataFile >> dataValue)
	{
		dataVector->push_back(dataValue);
	}
	dataFile.close();
}

void DataInputSystem::ShowData()
{
	for (int i = 0; i < dataVector.size(); i++) 
	{
		cout << dataVector[i] << endl;
	}
}

void DataInputSystem::Start()
{ 
	cout << "Subsystem " << name << " -started!" << endl;
	ParseTextData(&dataVector);
}
