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
	cout << "Starting simulation..." << endl;
	material = physics->createMaterial(0.5f, 0.5f, 0.6f);
	PxRigidStatic* groundPlane = PxCreatePlane(*physics, PxPlane(0, 1, 0, 1), *material);
	scene->addActor(*groundPlane);
}

void PhysicsSystem::RunPhysX()
{
	scene->simulate(1.0f / 60.f);
	scene->fetchResults(true);
}

void PhysicsSystem::AddRB(GameObject* obj, std::string type)
{
	if(obj->myRB == NULL)
	{
		obj->myRB = new Rigidbody(type);


		if (type == "static" || type == "Static")
		{

			material = physics->createMaterial(0.5f, 0.5f, 0.6f);

			PxRigidStatic* newRB = physics->createRigidStatic(PxTransform(PxVec3(obj->Position.x, obj->Position.y, obj->Position.z)));
			PxRigidActorExt::createExclusiveShape(*newRB, PxBoxGeometry(obj->myModel->sizeX, obj->myModel->sizeY, obj->myModel->sizeZ), *material);

			//PxRigidActorExt::createExclusiveShape(*newRB, PxBoxGeometry(1, 1, 1), *material);
			
			newRB->setGlobalPose(PxTransform(PxVec3(obj->Position.x, obj->Position.y, obj->Position.z)));
			
			obj->myRB->staticRB = newRB;
			scene->addActor(*newRB);


		}

		else if (type == "dynamic" || type == "Dynamic")
		{
			material = physics->createMaterial(0.5f, 0.5f, 0.6f);

			PxRigidDynamic* newRB = physics->createRigidDynamic(PxTransform(PxVec3(obj->Position.x, obj->Position.y, obj->Position.z)));
			PxRigidActorExt::createExclusiveShape(*newRB, PxBoxGeometry(obj->myModel->sizeX, obj->myModel->sizeY, obj->myModel->sizeZ), *material);

			//newRB->setMass(50.0f);
			newRB->setGlobalPose(PxTransform(PxVec3(obj->Position.x, obj->Position.y, obj->Position.z)));


			obj->myRB->dynamicRB = newRB;
			scene->addActor(*newRB);
		}

		else
		{
			cout << "Unknown Rigidbody type!" << endl;
		}
	}
}

void PhysicsSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	StartPhysX();
	CreateSimulation();
}

void PhysicsSystem::Update()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->PhysicsSub)
			{
				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->PHYSDefault)
				{
					cout << "Default PHYS event happened" << endl;
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->PHYSSpawn)
				{
					cout << "Physics spawn event happened" << endl;

					AddRB((*engineEventQueue)[i]->myData->targetObject, (*engineEventQueue)[i]->myData->RBType);
				}

				else
				{
					cout << "ERROR! Unrecognised Graphics event" << endl;
				}

				delete((*engineEventQueue)[i]);
				engineEventQueue->erase(engineEventQueue->begin() + i);
			}

		}
	}

	//Event Checks

	RunPhysX();
}

void PhysicsSystem::Exit()
{
}
