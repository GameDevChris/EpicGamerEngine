#pragma once
#include "SubSystem.h"
#include "MyVec3.h"
#include "SpawnData.h" 

#include <filesystem>
namespace fs = std::filesystem;

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge.h>

using namespace luabridge;

class DataInputSystem :
	public SubSystem
{
public:
	std::string dirPath = ".\\Game Parameters\\directory.lua";
	lua_State* dir;

	std::string lvl1Settings = "./LevelLayouts/level1Settings.lua";
	lua_State* lvl1;

	std::string gameTitle = "";
	int ScreenWidth = 0;
	int ScreenHeight = 0;

	int Lvl1LayoutChoice = 0;

	std::string lvl1LayoutFolder = "";
	std::vector<std::string> layout1Paths;

	std::string modelFolder = "";
	std::vector<std::string> modelPaths;

	std::string musicFolder = "";

	

	void StartLua();
	void GetDirectories();
	void GetData();
	void LoadDataObjects(std::vector<SpawnData*>* myData, int levelNum, bool* flag);

	std::vector<std::string> loadObjects(const std::string& table, lua_State* state);
	
	std::vector<char> dataVector;

	virtual void Start();
	virtual void Update();
	virtual void ProcessEvents();
};

