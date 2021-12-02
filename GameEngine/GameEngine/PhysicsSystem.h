#pragma once
#include "SubSystem.h"
#include "Player.h"
#include <PxPhysicsAPI.h>
#include "ContactCallback.h"
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
	void CheckColisions();
	void AddRB(GameObject* obj, std::string type, std::string filterType);


public:
	Player* myPlayer = NULL;

	ContactCallback myContactReportCallback;

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


	void setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask);

	virtual void Start();
	virtual void Update();
	virtual void ProcessEvents();
	virtual void Exit();
};


