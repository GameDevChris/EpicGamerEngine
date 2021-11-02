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
	void ParseTextData(vector<char>* dataVector);

public:
	vector<char> dataVector;
	void ShowData();
	virtual void Start();
};

