#pragma once
#include <PxPhysicsAPI.h>
#include <iostream>;

using namespace physx;

struct Rigidbody
{
public:
	std::string myType = "";

	std::string filterType = "";

	PxRigidDynamic* dynamicRB = NULL;
	PxRigidStatic* staticRB = NULL;
	PxShape* trigger = NULL;

	Rigidbody(std::string type)
	{
		myType = type;
	}
};
