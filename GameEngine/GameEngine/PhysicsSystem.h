#pragma once
#include "SubSystem.h"
#include <PxPhysicsAPI.h>

using namespace physx;

class PhysicsSystem :
	public SubSystem
{
private:
	PxDefaultErrorCallback defaultErrorCallback;
	PxDefaultAllocator defaultAllocator;

	PxFoundation* foundation;
	PxPhysics* physics;
	PxCooking* cooking;

	bool doMemoryProfiling = true;

	void StartPhysX();

public:
	virtual void Start();
	virtual void Update();
	virtual void Exit();
};


