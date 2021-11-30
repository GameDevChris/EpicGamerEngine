#include "DataInputSystem.h"

void DataInputSystem::ParseTextData(std::vector<char>* dataVector)
{
	char dataValue;
	std::ifstream dataFile;
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
		std::cout << dataVector[i] << std::endl;
	}
}

void DataInputSystem::Start()
{ 
	std::cout << "Subsystem " << name << " -started!" << std::endl;
	ParseTextData(&dataVector);
}
