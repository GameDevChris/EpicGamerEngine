#pragma once
#include "Model.h"
#include "Vec3.h"
class GameObject
{
public:

	GameObject(Model* mod, Vec3 pos, Vec3 rot, Vec3 sca);
	GameObject();

	Model* myModel;
	Vec3 Position;
	Vec3 Scale;
	Vec3 Rotation;
};

