#include "GameObject.h"

GameObject::GameObject(Model* mod, Vec3 pos, Vec3 rot, Vec3 sca)
{
	myModel = mod;
	Position = pos;
	Scale = sca;
	Rotation = rot;
}

GameObject::GameObject()
{
}
