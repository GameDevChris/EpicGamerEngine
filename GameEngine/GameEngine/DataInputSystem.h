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
	void ParseTextData(std::vector<char>* dataVector);

public:
	std::vector<char> dataVector;
	void ShowData();
	virtual void Start();
};

