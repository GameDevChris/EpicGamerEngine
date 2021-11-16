#pragma once
#include "SubSystem.h"
#include <PxPhysicsAPI.h>

using namespace physx;

class PhysicsSystem :
	public SubSystem
{
private:
	PxDefaultErrorCallback defaultErrorCallback;
	PxDefaultCpuDispatcher* dispatcher = NULL;
	PxTolerancesScale toleranceScale;
	PxDefaultAllocator defaultAllocator;

	PxFoundation* foundation = NULL;
	PxPhysics* physics = NULL;
	PxCooking* cooking;

	PxScene* scene = NULL;
	PxMaterial* material = NULL;

	PxPvd* pvd = NULL;

	bool doMemoryProfiling = true;

	void StartPhysX();
	void CreateSimulation();
	void RunPhysX();

public:
	virtual void Start();
	virtual void Update();
	virtual void Exit();
};


