#include "PhysicsSystem.h"

void PhysicsSystem::StartPhysX()
{  
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocator, defaultErrorCallback);

	if (!foundation)
	{
		cout << "Failed to create Foundation!" << endl;
	}

	pvd = PxCreatePvd(*foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	toleranceScale.length = 100;
	toleranceScale.speed = 981;
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, toleranceScale, doMemoryProfiling, pvd);
	if (!physics)
	{
		cout << "Failed to create Physics!" << endl;
	}

	cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(PxTolerancesScale()));
	if (!cooking)
	{
		cout << "Failed to create Cooking!" << endl;
	}

	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

	dispatcher = PxDefaultCpuDispatcherCreate(2);

	sceneDesc.cpuDispatcher = dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;


	scene = physics->createScene(sceneDesc);

	PxPvdSceneClient* pvdClient = scene->getScenePvdClient();
	if(pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
}

void PhysicsSystem::CreateSimulation()
{
	material = physics->createMaterial(0.5f, 0.5f, 0.6f);
	PxRigidStatic* groundPlane = PxCreatePlane(*physics, PxPlane(0, 1, 0, 1), *material);
	scene->addActor(*groundPlane);
}

void PhysicsSystem::RunPhysX()
{
	scene->simulate(1.0f / 60.f);
	scene->fetchResults(true);
}

void PhysicsSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	StartPhysX();
}

void PhysicsSystem::Update()
{

	//Event Checks

	RunPhysX();
}

void PhysicsSystem::Exit()
{
}
