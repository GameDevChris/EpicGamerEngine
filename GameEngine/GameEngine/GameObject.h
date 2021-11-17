#pragma once
#include "Model.h"
#include "MyVec3.h"
class GameObject
{
public:
	GameObject(Model* mod, MyVec3 pos, MyVec3 rot, MyVec3 sca);
	GameObject();

	Model* myModel;
	MyVec3 Rotation = MyVec3(0, 0, 0);
	MyVec3 Position = MyVec3(0,0,0);
	MyVec3 Scale = MyVec3(0, 0, 0);
};

