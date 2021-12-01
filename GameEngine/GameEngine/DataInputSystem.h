#pragma once
#include "SubSystem.h"
#include "MyVec3.h"
 
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
private:
	std::string dirPath = "directory.lua";
	lua_State* dir;

	std::string lvl1Path = "level1.lua";
	lua_State* lvl1;

	std::string gameTitle = "";
	int ScreenWidth = 0;
	int ScreenHeight = 0;

	void StartLua();
	void GetDirectories();
	void GetData();
	void LoadDataObjects();
	void DataToManager();

	std::vector<std::string> loadObjects(const std::string& table, lua_State* state);

	void ParseTextData(std::vector<char>* dataVector);


public:
	std::vector<char> dataVector;
	void ShowData();
	virtual void Start();
	virtual void Update();
};

