#include "PhysicsSystem.h"

void PhysicsSystem::StartPhysX()
{  
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocator, defaultErrorCallback);

	if (!foundation)
	{
		cout << "Failed to create Foundation!" << endl;
	}

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), doMemoryProfiling);
	if (!physics)
	{
		cout << "Failed to create Physics!" << endl;
	}

	cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(PxTolerancesScale()));
	if (!cooking)
	{
		cout << "Failed to create Cooking!" << endl;
	}
}

void PhysicsSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	StartPhysX();
}

void PhysicsSystem::Update()
{
}

void PhysicsSystem::Exit()
{
}
