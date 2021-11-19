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

	//PxSimulationFilterShader newShader = PhysicsFilterShader;


	scene = physics->createScene(sceneDesc);

	PxPvdSceneClient* pvdClient = scene->getScenePvdClient();
	if(pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
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
			
	
			if (obj->myRB->filterType == "Ground") 
			{
				setupFiltering(newRB, FilterGroup::eGround, FilterGroup::ePlayer | FilterGroup::eButton);
			}

			else if (obj->myRB->filterType == "Player")
			{
				setupFiltering(newRB, FilterGroup::ePlayer, FilterGroup::eButton | FilterGroup::eGround | FilterGroup::eEnemy);
			}
			
			else if (obj->myRB->filterType == "Button")
			{
				setupFiltering(newRB, FilterGroup::eButton, FilterGroup::ePlayer);
			}

			else if (obj->myRB->filterType == "Enemy")
			{
				setupFiltering(newRB, FilterGroup::eEnemy, FilterGroup::ePlayer);
			}

			else
			{
				cout << "Unknow filter type" << endl;
			}

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

			if (obj->myRB->filterType == "Ground")
			{
				setupFiltering(newRB, FilterGroup::eGround, FilterGroup::ePlayer | FilterGroup::eButton);
			}

			else if (obj->myRB->filterType == "Player")
			{
				setupFiltering(newRB, FilterGroup::ePlayer, FilterGroup::eButton | FilterGroup::eGround | FilterGroup::eEnemy);
			}

			else if (obj->myRB->filterType == "Button")
			{
				setupFiltering(newRB, FilterGroup::eButton, FilterGroup::ePlayer);
			}

			else if (obj->myRB->filterType == "Enemy")
			{
				setupFiltering(newRB, FilterGroup::eEnemy, FilterGroup::ePlayer);
			}

			else
			{
				cout << "Unknow filter type" << endl;
			}

			obj->myRB->dynamicRB = newRB;
			scene->addActor(*newRB);
		}

		else
		{
			cout << "Unknown Rigidbody type!" << endl;
		}
	}
}

PxFilterFlags PhysicsSystem::PhysicsFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	// let triggers through
	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
		return PxFilterFlag::eDEFAULT;
	}

	// generate contacts for all that were not filtered above
	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	// trigger the contact callback for pairs (A,B) where
	// the filtermask of A contains the ID of B and vice versa.
	if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;

	return PxFilterFlag::eDEFAULT;
}

void PhysicsSystem::setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask)
{
	PxFilterData filterData;
	filterData.word0 = filterGroup; // word0 = own ID
	filterData.word1 = filterMask;	// word1 = ID mask to filter pairs that trigger a contact callback;
	const PxU32 numShapes = actor->getNbShapes();
	
	PxShape** shapes = (PxShape**)(sizeof(PxShape*) * numShapes);
	actor->getShapes(shapes, numShapes);
	for (PxU32 i = 0; i < numShapes; i++)
	{
		PxShape* shape = shapes[i];
		shape->setSimulationFilterData(filterData);
	}
}

void PhysicsSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	StartPhysX();
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
					AddRB((*engineEventQueue)[i]->myData->targetObject, (*engineEventQueue)[i]->myData->RBType);
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->PlayerMove)
				{

					PxVec3 force((*engineEventQueue)[i]->myData->myForce->x, (*engineEventQueue)[i]->myData->myForce->y, (*engineEventQueue)[i]->myData->myForce->z);

					(*engineEventQueue)[i]->myData->targetPlayer->myRB->dynamicRB->addForce(force);
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->PlayerRotate)
				{

					PxVec3 force((*engineEventQueue)[i]->myData->myForce->x, (*engineEventQueue)[i]->myData->myForce->y, (*engineEventQueue)[i]->myData->myForce->z);

					(*engineEventQueue)[i]->myData->targetPlayer->myRB->dynamicRB->addTorque(force);
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->PlayerImpulse)
				{

					PxVec3 force((*engineEventQueue)[i]->myData->myForce->x, (*engineEventQueue)[i]->myData->myForce->y, (*engineEventQueue)[i]->myData->myForce->z);

					(*engineEventQueue)[i]->myData->targetPlayer->myRB->dynamicRB->addForce(force, PxForceMode::eIMPULSE);
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
