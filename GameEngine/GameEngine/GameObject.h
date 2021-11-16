#pragma once
#include "Model.h"
#include "Vec3.h"
class GameObject
{
public:
	GameObject(Model* mod, Vec3 pos, Vec3 rot, Vec3 sca);
	GameObject();

	Model* myModel;
	Vec3 Position = Vec3(0,0,0);
	Vec3 Scale = Vec3(0, 0, 0);
	Vec3 Rotation = Vec3(0, 0, 0);
};

