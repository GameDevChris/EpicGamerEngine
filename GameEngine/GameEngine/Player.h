#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	bool isGrounded = true;

	float score = 0;

	float linearSpeed = 20;
	float angularSpeed = 10;

	float jumpHeight = 100;

	Player(Model* mod, MyVec3 pos, MyVec3 rot, MyVec3 sca);

	void Update()
	{}
};

