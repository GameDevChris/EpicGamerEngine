#include "GameObject.h"

GameObject::GameObject(Model* mod, MyVec3 pos, MyVec3 rot, MyVec3 sca)
{
	myModel = mod;
	Position = pos;
	Scale = sca;
	Rotation = rot;
}

GameObject::GameObject()
{
}
