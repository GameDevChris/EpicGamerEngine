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
	void RunPhysX();
	void AddRB(GameObject* obj, std::string type);

	

public:

	struct FilterGroup
	{
		enum Enum
		{
			eGround = (1 << 0),
			ePlayer = (1 << 1),
			eButton = (1 << 2),
			eEnemy = (1 << 3),
		};
	};

	PxFilterFlags PhysicsFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize);

	void setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask);

	virtual void Start();
	virtual void Update();
	virtual void Exit();
};


