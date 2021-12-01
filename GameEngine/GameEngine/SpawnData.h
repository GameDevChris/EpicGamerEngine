#pragma once
#include <iostream>
#include "MyVec3.h"
struct SpawnData
{
	int modelID = 0;
	int textureID = 0;
	MyVec3 position;
	MyVec3 scale;
	MyVec3 rotation;
	std::string rbType;
	std::string cfType;
};