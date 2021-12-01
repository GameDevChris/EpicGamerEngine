#include "DataInputSystem.h"

void DataInputSystem::StartLua()
{
	GetDirectories();
	GetData();
	DataToManager();
}

void DataInputSystem::GetDirectories()
{
	dir = luaL_newstate();
	luaL_dofile(dir, dirPath.c_str());
	luaL_openlibs(dir);
	lua_pcall(dir, 0, 0, 0);
}

void DataInputSystem::GetData()
{
	LuaRef windowData = getGlobal(dir, "window");

	//Title
	gameTitle = windowData["title"].cast<std::string>();

	//ScreenDimensions
	ScreenWidth = windowData["width"].cast<int>();
	ScreenHeight = windowData["height"].cast<int>();
}

void DataInputSystem::DataToManager()
{
	subManager->EngineTitle = gameTitle;
	subManager->EngineWidth = ScreenWidth;
	subManager->EngineHeight = ScreenHeight;
}

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
	StartLua();
}
