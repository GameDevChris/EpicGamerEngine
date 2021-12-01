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

	lvl1 = luaL_newstate();
	luaL_dofile(lvl1, lvl1Path.c_str());
	luaL_openlibs(lvl1);
	lua_pcall(lvl1, 0, 0, 0);
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

void DataInputSystem::LoadDataObjects()
{
	std::vector<std::string> objList = loadObjects("gameObjectList", lvl1);
	LuaRef objectsData = getGlobal(lvl1, "gameObjectList");


	for (int i = 0; i < objList.size(); i++)
	{
		LuaRef object = objectsData[objList[i]];
		LuaRef Pos = object["objPosition"];
		LuaRef Scale = object["objScale"];
		LuaRef Rot = object["objRot"];

		//int modelID = object["modID"].cast<int>();
		//int textureID = object["textureID"].cast<int>();
		//std::string rbType = object["rigidType"].cast<std::string>();
		//std::string cfType = object["filterType"].cast<std::string>();
		//MyVec3 position = MyVec3(Pos["X"].cast<float>(), Pos["Y"].cast<float>(), Pos["Z"].cast<float>());
		//MyVec3 scale = MyVec3(Scale["X"].cast<float>(), Scale["Y"].cast<float>(), Scale["Z"].cast<float>());
		//MyVec3 rotation = MyVec3(Rot["X"].cast<float>(), Rot["Y"].cast<float>(), Rot["Z"].cast<float>());



		int UIIDTexHolder = 0;
		int UIIDModelHolder = 6;

		std::string rbVal = "static";
		std::string colVal = "Ground";

		MyVec3 UIPosHolder(0.0f,0.0f,0.0f);
		MyVec3 UIRotHolder(0.0f,0.0f,0.0f);
		MyVec3 UIScaleHolder(1.0f,1.0f,1.0f);

		Event* instantiateEvent = new Event("InstantiateCustom", engineEventQueue, &UIIDModelHolder, &UIIDTexHolder, &rbVal, &colVal, &UIPosHolder, &UIScaleHolder, &UIRotHolder);



		//int modelID = 6;
		//int textureID = 0;
		//std::string rbType = "static";
		//std::string cfType = "Ground";
		//MyVec3 position = MyVec3(0.0f, 0.0f, 0.0f);
		//MyVec3 scale = MyVec3(1.0f, 1.0f, 1.0f);
		//MyVec3 rotation = MyVec3(0.0f, 0.0f, 0.0f);
		//
		//
		//Event* instantiate =
		//	new Event("InstantiateCustom",
		//		engineEventQueue,
		//		&modelID,
		//		&textureID,
		//		&rbType,
		//		&cfType,
		//		&position,
		//		&scale,
		//		&rotation);
	}
}

void DataInputSystem::DataToManager()
{
	subManager->EngineTitle = gameTitle;
	subManager->EngineWidth = ScreenWidth;
	subManager->EngineHeight = ScreenHeight;
}

std::vector<std::string> DataInputSystem::loadObjects(const std::string& table, lua_State* state)
{
	std::string source = 
		"function loadObjects(table)"
		"s = \"\""
		"for k, v in pairs(_G[table]) do "
		"    s = s..k..\"|\" "
		"    end "
		"return s "
		"end";

	luaL_loadstring(state, source.c_str());
	lua_pcall(state, 0, 0, 0);
	lua_getglobal(state, "loadObjects");
	lua_pushstring(state, table.c_str());
	lua_pcall(state, 1, 1, 0);

	std::string ans = lua_tostring(state, -1);
	std::vector<std::string> objects;
	std::string temp = "";
	for (unsigned int i = 0; i < ans.size(); i++) {
		if (ans.at(i) != '|') {
			temp += ans.at(i);
		}
		else {
			objects.push_back(temp);
			temp = "";
		}
	}

	int n = lua_gettop(state);
	lua_pop(state, 1);

	return objects;
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

void DataInputSystem::Update()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->DataSub)
			{

				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->DataLoadLevel)
				{

					LoadDataObjects();
				}

				delete((*engineEventQueue)[i]);
				engineEventQueue->erase(engineEventQueue->begin() + i);
			}
		}
	}
}
