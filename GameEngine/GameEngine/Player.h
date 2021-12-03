#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	bool isGrounded = true;
	Player(Model* mod, MyVec3 pos, MyVec3 rot, MyVec3 sca);

	void Update()
	{}
};

