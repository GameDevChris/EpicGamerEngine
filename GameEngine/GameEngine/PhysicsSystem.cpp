#include "PhysicsSystem.h"

PxFilterFlags PhysicsFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	//// let triggers through
	//if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
	//{
	//	pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
	//	return PxFilterFlag::eDEFAULT;
	//}
	//
	//// generate contacts for all that were not filtered above
	//pairFlags = PxPairFlag::eCONTACT_DEFAULT;
	//
	//// trigger the contact callback for pairs (A,B) where
	//// the filtermask of A contains the ID of B and vice versa.
	//if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
	//	pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
	//
	//return PxFilterFlag::eDEFAULT;

	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	// all initial and persisting reports for everything, with per-point data
	pairFlags = PxPairFlag::eSOLVE_CONTACT | PxPairFlag::eDETECT_DISCRETE_CONTACT
		| PxPairFlag::eNOTIFY_TOUCH_FOUND
		| PxPairFlag::eNOTIFY_TOUCH_PERSISTS
		| PxPairFlag::eNOTIFY_CONTACT_POINTS;
	return PxFilterFlag::eDEFAULT;
}

void PhysicsSystem::StartPhysX()
{  
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocator, defaultErrorCallback);

	if (!foundation)
	{
		std::cout << "Failed to create Foundation!" << std::endl;
	}

	pvd = PxCreatePvd(*foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	toleranceScale.length = 100;
	toleranceScale.speed = 981;
	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, toleranceScale, doMemoryProfiling, pvd);
	if (!physics)
	{
		std::cout << "Failed to create Physics!" << std::endl;
	}

	cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(PxTolerancesScale()));
	if (!cooking)
	{
		std::cout << "Failed to create Cooking!" << std::endl;
	}

	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

	dispatcher = PxDefaultCpuDispatcherCreate(2);

	sceneDesc.cpuDispatcher = dispatcher;

	sceneDesc.filterShader = PhysicsFilterShader;
	sceneDesc.simulationEventCallback = &myContactReportCallback;

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

void PhysicsSystem::CheckColisions()
{
	if (myContactReportCallback.colShape1 != NULL && myContactReportCallback.colShape2 != NULL)
	{
		std::string collider1 = myContactReportCallback.colShape1->getName();
		std::string collider2 = myContactReportCallback.colShape2->getName();

		if (collider1 == "Player" && collider2 == "Ground")
		{
			if (myPlayer->isGrounded == false)
			{
				std::cout << "Player can now jump" << std::endl;
				myPlayer->isGrounded = true;
			}
		}

		else
		{
			std::cout << collider1 << " coliding with " << collider2 << std::endl;
		}

		myContactReportCallback.colShape1 = NULL;
		myContactReportCallback.colShape2 = NULL;
	}
}

void PhysicsSystem::AddRB(GameObject* obj, std::string type, std::string filterType)
{
	if(obj->myRB == NULL)
	{
		obj->myRB = new Rigidbody(type);
		
		obj->myRB->filterType = filterType;

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
				std::cout << "Unknown filter type" << std::endl;
			}

			obj->myRB->staticRB = newRB;

			const PxU32 numShapes = newRB->getNbShapes();
			PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*) * numShapes);
			newRB->getShapes(shapes, numShapes);

			for (PxU32 i = 0; i < numShapes; i++)
			{
				shapes[i]->setName(obj->myRB->filterType.c_str());
				std::cout << "Created a " << obj->myRB->filterType << std::endl;
			}
			scene->addActor(*newRB);

		}

		else if (type == "dynamic" || type == "Dynamic")
		{
			material = physics->createMaterial(0.5f, 0.5f, 0.6f);

			PxRigidDynamic* newRB = physics->createRigidDynamic(PxTransform(PxVec3(obj->Position.x, obj->Position.y, obj->Position.z)));

			PxRigidBodyExt::updateMassAndInertia(*newRB, 10.0f, &PxVec3(0, 0, 0));
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
				std::cout << "Unknown filter type" << std::endl;
			}

			obj->myRB->dynamicRB = newRB;

			const PxU32 numShapes = newRB->getNbShapes();
			PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*) * numShapes);
			newRB->getShapes(shapes, numShapes);

			for (PxU32 i = 0; i < numShapes; i++)
			{
				shapes[i]->setName(obj->myRB->filterType.c_str());
				std::cout << "Created a " << obj->myRB->filterType << std::endl;
			}
			scene->addActor(*newRB);
		}

		else
		{
			std::cout << "Unknown Rigidbody type!" << std::endl;
		}
	}
}



void PhysicsSystem::setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask)
{
	PxFilterData filterData;
	filterData.word0 = filterGroup; // word0 = own ID
	filterData.word1 = filterMask;	// word1 = ID mask to filter pairs that trigger a contact callback;
	const PxU32 numShapes = actor->getNbShapes();
	
	PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*)*numShapes);
	actor->getShapes(shapes, numShapes);

	for (PxU32 i = 0; i < numShapes; i++)
	{
		PxShape* shape = shapes[i];
		shape->setSimulationFilterData(filterData);
	}

	free(shapes);
}

void PhysicsSystem::Start()
{
	std::cout << "Subsystem " << name << " -started!" << std::endl;

	StartPhysX();
}

void PhysicsSystem::Update()
{
	RunPhysX();
	CheckColisions();
}

void PhysicsSystem::ProcessEvents()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->PhysicsSub)
			{
				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->PHYSDefault)
				{
					std::cout << "Default PHYS event happened" << std::endl;
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->PHYSSpawn)
				{
					AddRB((*engineEventQueue)[i]->myData->targetObject, (*engineEventQueue)[i]->myData->RBType, (*engineEventQueue)[i]->myData->CFType);
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
					(*engineEventQueue)[i]->myData->targetPlayer->myRB->dynamicRB->addForce(force);

				}

				else
				{
					std::cout << "ERROR! Unrecognised Graphics event" << std::endl;
				}

				delete((*engineEventQueue)[i]);
				engineEventQueue->erase(engineEventQueue->begin() + i);
			}

		}
	}
}

void PhysicsSystem::Exit()
{
}
