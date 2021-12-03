#include "DataInputSystem.h"

void DataInputSystem::StartLua()
{
	GetDirectories();
	GetData();
}

void DataInputSystem::GetDirectories()
{
	dir = luaL_newstate();
	luaL_dofile(dir, dirPath.c_str());
	luaL_openlibs(dir);
	lua_pcall(dir, 0, 0, 0);

	lvl1 = luaL_newstate();
	luaL_dofile(lvl1, lvl1Settings.c_str());
	luaL_openlibs(lvl1);
	lua_pcall(lvl1, 0, 0, 0);
}

void DataInputSystem::GetData()
{
	LuaRef windowData = getGlobal(dir, "window");

	//Graphic Settings
		//Title
		subManager->EngineTitle = windowData["title"].cast<std::string>();

		//ScreenDimensions
		subManager->EngineWidth = windowData["width"].cast<int>();
		subManager->EngineHeight = windowData["height"].cast<int>();

		//BG Colour
		MyVec3 BG(windowData["bgColourR"].cast<float>(), windowData["bgColourG"].cast<float>(), windowData["bgColourB"].cast<float>());
		subManager->BGColour = BG;

		//Graphics Parameters
		subManager->BitPerPixel = windowData["BitPerPixel"].cast<int>();
		subManager->Fullscreen = windowData["Fullscreen"].cast<bool>();
		subManager->StencilBuffer = windowData["StencilBuffer"].cast<bool>();
		subManager->AntiAlias = windowData["AntiAlias"].cast<int>();
		subManager->VSync = windowData["VSync"].cast<bool>();

	//Gameplay Settings
		//Model IDs
		subManager->platformID = windowData["platformID"].cast<int>();
		subManager->buttonID = windowData["buttonID"].cast<int>();
		subManager->playerID = windowData["playerID"].cast<int>();

		//Player Settings
		subManager->PlayerLinearSpeed = windowData["PlayerLinearSpeed"].cast<int>();
		subManager->PlayerAngularSpeed = windowData["PlayerAngularSpeed"].cast<int>();
		subManager->PlayerJumpHeight = windowData["PlayerJumpHeight"].cast<int>();

		subManager->PlayerSize.x = windowData["PlayerSizeX"].cast<int>();
		subManager->PlayerSize.y = windowData["PlayerSizeY"].cast<int>();
		subManager->PlayerSize.z = windowData["PlayerSizeZ"].cast<int>();

	//Network Settings
		//Bot text paths
		subManager->botScoreTextPath = windowData["botScoreTextPath"].cast<std::string>();
		subManager->botJobTextPath = windowData["botJobTextPath"].cast<std::string>();
		subManager->discordLink = windowData["discordLink"].cast<std::string>();

	//GetModelFolders
	modelFolder = windowData["modelFolder"].cast<std::string>();

	//Sound Settings
	subManager->backgroundMusic = windowData["BgMusicPath"].cast<std::string>();
	musicFolder = windowData["musicFolder"].cast<std::string>();

	modelPaths.clear();
	for (const auto& entry : fs::directory_iterator(modelFolder))
		std::cout << entry.path().string() << std::endl,
		modelPaths.push_back(entry.path().string());

	std::vector<std::string> textures;
	
	for (int i = 0; i < modelPaths.size(); i++)
	{
		std::string objPath = "";
		textures.clear();
		for (const auto& entry : fs::directory_iterator(modelPaths[i]))
	
			if ((entry.path().string().substr(entry.path().string().find_last_of(".") + 1) == "png")
				|| (entry.path().string().substr(entry.path().string().find_last_of(".") + 1) == "PNG")
				|| (entry.path().string().substr(entry.path().string().find_last_of(".") + 1) == "jpg")
				|| (entry.path().string().substr(entry.path().string().find_last_of(".") + 1) == "jpeg"))
			{
				textures.push_back(entry.path().string());
			}
			
			else if (entry.path().string().substr(entry.path().string().find_last_of(".") + 1) == "obj")
			{
				objPath = entry.path().string();
			}
	
		AssetEvent* newAsset = new AssetEvent("ASSETLoad", objPath, &textures, i, modelPaths[i], engineEventQueue);
	}


	LuaRef lvl1Data = getGlobal(lvl1, "settings");
	Lvl1LayoutChoice = lvl1Data["layoutChoice"].cast<int>();

	lvl1LayoutFolder = lvl1Data["layoutFolder"].cast<std::string>();
	layout1Paths.clear();
	for (const auto& entry : fs::directory_iterator(lvl1LayoutFolder))
		layout1Paths.push_back(entry.path().string());

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

void DataInputSystem::Start()
{ 
	std::cout << "Subsystem " << name << " -started!" << std::endl;
	StartLua();
}

void DataInputSystem::Update()
{
	
}

void DataInputSystem::ProcessEvents()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->DataSub)
			{

				delete((*engineEventQueue)[i]);
				engineEventQueue->erase(engineEventQueue->begin() + i);
			}
		}
	}
}

void DataInputSystem::LoadDataObjects(std::vector<SpawnData*>* myData, int levelNum, bool* flag)
{
	if (levelNum == 1)
	{
		lua_State*  layout = luaL_newstate();

		if (Lvl1LayoutChoice > layout1Paths.size())
		{
			Lvl1LayoutChoice = 0;
		}

		else
		{
			luaL_dofile(layout, layout1Paths[Lvl1LayoutChoice].c_str());
		}

		luaL_openlibs(layout);
		lua_pcall(layout, 0, 0, 0);

		myData->clear();
		std::vector<std::string> objList = loadObjects("gameObjectList", layout);
		LuaRef objectsData = getGlobal(layout, "gameObjectList");
	
		for (int i = 0; i < objList.size(); i++)
		{
			LuaRef object = objectsData[objList[i]];
			LuaRef Pos = object["objPosition"];
			LuaRef Scale = object["objScale"];
			LuaRef Rot = object["objRot"];
	
			//int modelID = object["modID"].cast<int>();
			int modelID = subManager->platformID;

			int textureID = object["textureID"].cast<int>();
			std::string rbType = object["rigidType"].cast<std::string>();
			std::string cfType = object["filterType"].cast<std::string>();
			MyVec3 position = MyVec3(Pos["X"].cast<float>(), Pos["Y"].cast<float>(), Pos["Z"].cast<float>());
			MyVec3 scale = MyVec3(Scale["X"].cast<float>(), Scale["Y"].cast<float>(), Scale["Z"].cast<float>());
			MyVec3 rotation = MyVec3(Rot["X"].cast<float>(), Rot["Y"].cast<float>(), Rot["Z"].cast<float>());
			
			SpawnData* myNewData = new SpawnData();
			
			myNewData->modelID = modelID;
			myNewData->textureID = textureID;
			myNewData->rbType = rbType;
			myNewData->cfType = cfType;
			myNewData->position = position;
			myNewData->scale = scale;
			myNewData->rotation = rotation;
			
			*flag = true;
			myData->push_back(myNewData);
		}
	}
	
	else
	{
		std::cout << "Error, unknown level" << std::endl;
		*flag = false;
	}

}