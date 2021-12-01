#pragma once
#include "SubSystem.h"

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


	std::string gameTitle = "";
	int ScreenWidth = 0;
	int ScreenHeight = 0;

	void StartLua();
	void GetDirectories();
	void GetData();
	void DataToManager();

	void ParseTextData(std::vector<char>* dataVector);

public:
	std::vector<char> dataVector;
	void ShowData();
	virtual void Start();
};

