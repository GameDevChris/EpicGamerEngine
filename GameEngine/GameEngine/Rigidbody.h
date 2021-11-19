#pragma once
#include <PxPhysicsAPI.h>
#include <iostream>;

using namespace physx;

struct Rigidbody
{
public:
	std::string myType = "";

	PxRigidDynamic* dynamicRB = NULL;
	PxRigidStatic* staticRB = NULL;

	Rigidbody(std::string type)
	{
		myType = type;
	}
};
