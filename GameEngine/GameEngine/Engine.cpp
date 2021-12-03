#include "Engine.h"

void Engine::InstantiateTimer(int cooldown, std::vector<SpawnData*> spawnData, int index)
{
	std::cout << "Started instantiation of element " << index << std::endl;
	clock_t startTime = clock();
	clock_t cooldownTime = cooldown * CLOCKS_PER_SEC;
	clock_t elapsed = clock() - startTime;;

	while (elapsed < cooldownTime)
	{
		elapsed = clock() - startTime;
	}

	Instantiate(spawnData[index]->modelID, spawnData[index]->textureID, spawnData[index]->position, spawnData[index]->scale, spawnData[index]->rotation, spawnData[index]->rbType, spawnData[index]->cfType);
}

void Engine::ClearScene()
{
	for (int j = 0; j < objects.size(); j++)
	{
		objects[j]->Delete();
	}

	objects.clear();

	UI.myPlayer = NULL;
	physics.myPlayer = NULL;
	graphics.myPlayer = NULL;

	graphics.AddCamera(0, 200, -200, 0, 0, 0);
}

void Engine::GetTargetColour()
{
	buttons.clear();
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->myModel->type == mainManager->buttonID)
		{
			buttons.push_back(objects[i]);
		}
	}

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> randCol(0, buttons.size() - 1);

	int choice = randCol(rng);

	MyVec3 colourChosen = buttons[choice]->myModel->myColour;

	mainManager->targetColor = colourChosen;

	buttons.clear();
}

void Engine::CheckButtonColor()
{
	buttons.clear();
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->myModel->type == mainManager->buttonID)
		{
			buttons.push_back(objects[i]);
		}
	}

	GameObject* targetObj = new GameObject();
	float currentShortestDistance = 1000;

	for(int i = 0; i<buttons.size(); i++)
	{
		float xdist=0, ydist=0, zdist=0;
		if (buttons[i]->myRB->myType == "static" || buttons[i]->myRB->myType == "Static")
		{
			float xdist = buttons[i]->myRB->staticRB->getGlobalPose().p.x - physics.myPlayer->myRB->dynamicRB->getGlobalPose().p.x;
			float ydist = buttons[i]->myRB->staticRB->getGlobalPose().p.y - physics.myPlayer->myRB->dynamicRB->getGlobalPose().p.y;
			float zdist = buttons[i]->myRB->staticRB->getGlobalPose().p.z - physics.myPlayer->myRB->dynamicRB->getGlobalPose().p.z;
		}

		else
		{
			float xdist = buttons[i]->myRB->dynamicRB->getGlobalPose().p.x - physics.myPlayer->myRB->dynamicRB->getGlobalPose().p.x;
			float ydist = buttons[i]->myRB->dynamicRB->getGlobalPose().p.y - physics.myPlayer->myRB->dynamicRB->getGlobalPose().p.y;
			float zdist = buttons[i]->myRB->dynamicRB->getGlobalPose().p.z - physics.myPlayer->myRB->dynamicRB->getGlobalPose().p.z;

		}

		float distance = sqrt((xdist * xdist) + (ydist * ydist) + (zdist * zdist));

		if (distance < currentShortestDistance)
		{
			currentShortestDistance = distance;
			targetObj = buttons[i];
		}
	}

	if (targetObj->myModel->myColour.x == mainManager->targetColor.x
		&& targetObj->myModel->myColour.y == mainManager->targetColor.y
		&& targetObj->myModel->myColour.z == mainManager->targetColor.z)
	{
		mainManager->score++;
		dataInput.Lvl1LayoutChoice++;
		LoadLevel(1);
	}

	else 
	{
		std::cout << "Wrong colour!" << std::endl;
	}

	buttons.clear();
}

void Engine::ProcessEngineEvent()
{
	if (!eventQueue.empty())
	{
		for (int i = 0; i < eventQueue.size(); i++)
		{
			if (eventQueue[i]->eventSubsystem == eventQueue[i]->General)
			{
				if (eventQueue[i]->eventType == eventQueue[i]->InstantiateCustom)
				{

					Instantiate(*(eventQueue[i]->myData->myModID), *(eventQueue[i]->myData->myTexID), *(eventQueue[i]->myData->myPos), *(eventQueue[i]->myData->myScale), *(eventQueue[i]->myData->myRot), eventQueue[i]->myData->RBType, eventQueue[i]->myData->CFType);
					delete(eventQueue[i]);
					//eventQueue.erase(eventQueue.begin() + i);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->InstantiatePlayer)
				{

					InstantiatePlayer(*(eventQueue[i]->myData->myModID), *(eventQueue[i]->myData->myTexID), *(eventQueue[i]->myData->myPos), *(eventQueue[i]->myData->myScale), *(eventQueue[i]->myData->myRot));
					delete(eventQueue[i]);
					//eventQueue.erase(eventQueue.begin() + i);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->LoadLevel)
				{
					LoadLevel(*(eventQueue[i]->myData->levelNumber));
					delete(eventQueue[i]);
					//eventQueue.erase(eventQueue.begin() + i);

				}

				else if (eventQueue[i]->eventType == eventQueue[i]->PlayerLost)
				{
					ClearScene();
					mainManager->currentScene = mainManager->End;
					delete(eventQueue[i]);
					//eventQueue.erase(eventQueue.begin() + i);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->ChrisLegion)
				{
					for (int i = 0; i < 1; i++)
					{
						InstantiateRandom();
					}

					delete(eventQueue[i]);
					//eventQueue.erase(eventQueue.begin() + i);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->GameStart)
				{
					mainManager->score = 0;
					GetTargetColour();
					delete(eventQueue[i]);
					//eventQueue.erase(eventQueue.begin() + i);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->ButtonCheck)
				{
					CheckButtonColor();
					delete(eventQueue[i]);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->DeleteAll)
				{
					ClearScene();

					delete(eventQueue[i]);
					//eventQueue.erase(eventQueue.begin() + i);
				}
			}
		}
	}
}

void Engine::ProcessSubsystemEvents()
{
	ProcessEngineEvent();
	UI.ProcessEvents();
	assets.ProcessEvents();
	graphics.ProcessEvents();
	dataInput.ProcessEvents();
	physics.ProcessEvents();
	network.ProcessEvents();
}



Engine::Engine()
{

}

void Engine::UseData()
{
	std::cout << std::endl;
	for (int i = 0; i < dataInput.dataVector.size(); i++) 
	{
		switch (dataInput.dataVector[i])
		{
			case '0':
			{
				std::cout << "adding physics event" << std::endl;
				Event newPhysEvent("PHYSDefault");
				ThrowEvent(newPhysEvent);
			}
			break;
			

			case '1':
			{
				std::cout << "adding graphics event" << std::endl;
				Event newGraphEvent("GFXDefault");
				ThrowEvent(newGraphEvent);
			}
			break;
		}
	}
}

void Engine::ThrowEvent(Event newEvent)
{
	eventQueue.push_back(&newEvent);
}

void Engine::Start()
{
	mainManager = new EpicGameManager();

	eventQueue.clear();
	lateEventQueue.clear();
	std::cout << "Engine started, help" << std::endl;

	dataInput.name = "EpicGamerDataInput";
	dataInput.subManager = mainManager;
	dataInput.engineEventQueue = &eventQueue;
	dataInput.lateEngineEventQueue = &lateEventQueue;
	dataInput.Start();

	physics.name = "EpicGamerPhysics";
	physics.subManager = mainManager;
	physics.engineEventQueue = &eventQueue;
	physics.lateEngineEventQueue = &lateEventQueue;
	physics.Start();

	graphics.name = "EpicGamerGraphics";
	graphics.subManager = mainManager;
	graphics.engineEventQueue = &eventQueue;
	graphics.lateEngineEventQueue = &lateEventQueue;
	graphics.Start();

	UI.name = "EpicGamerUI";
	UI.subManager = mainManager;
	UI.engineEventQueue = &eventQueue;
	UI.lateEngineEventQueue = &lateEventQueue;
	UI.Start();

	assets.name = "EpicGamerAssets";
	assets.subManager = mainManager;
	assets.engineEventQueue = &eventQueue;
	assets.lateEngineEventQueue = &lateEventQueue;
	assets.Start();

	assets.device = graphics.device;
	assets.driver = graphics.driver;
	assets.smgr = graphics.smgr;

	network.name = "EpicGamerNetwork";
	network.subManager = mainManager;
	network.engineEventQueue = &eventQueue;
	network.lateEngineEventQueue = &lateEventQueue;
	network.Start();

	UseData();
}

void Engine::Update()
{
	graphics.loadedModels = assets.models;

	UI.Update();
	assets.Update();
	graphics.Update();
	dataInput.Update();
	physics.Update();
	network.Update();

	ProcessSubsystemEvents();
	ProcessSubsystemEvents();
	ProcessSubsystemEvents();
	ProcessSubsystemEvents();

	if (graphics.QuitCall)
	{
		finished = true;
	}

	if (finished)
	{
		graphics.Exit();
	}

	eventQueue.clear();
	lateEventQueue.clear();

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->SyncTransform();
	}
}

void Engine::Instantiate(int modelID, int textureID, MyVec3 position, MyVec3 scale, MyVec3 rotation, std::string rbType, std::string cfType)
{
	std::cout << std::endl << "Instantiating... ID: " << modelID << std::endl;

	Model* newModel = new Model(assets.models[modelID]->mesh, assets.models[modelID]->texturePaths, assets.models[modelID]->modelPath, assets.models[modelID]->type, assets.models[modelID]->modelName);

	newModel->texturePath = (*newModel->texturePaths)[textureID];

	GameObject* newObject = new GameObject(newModel, position, rotation, scale);
	objects.push_back(newObject);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", newObject, &eventQueue);
	PhysEvent* newPhys = new PhysEvent("PHYSSpawn", &eventQueue, newObject, rbType, cfType);

}

void Engine::InstantiatePlayer(int modelID, int textureID, MyVec3 position, MyVec3 scale, MyVec3 rotation)
{
	std::cout << std::endl << "Instantiating Player..." << std::endl;

	Model* newModel = new Model(assets.models[modelID]->mesh, assets.models[modelID]->texturePaths, assets.models[modelID]->modelPath, assets.models[modelID]->type, assets.models[modelID]->modelName);

	newModel->texturePath = (*newModel->texturePaths)[textureID];

	Player* newPlayer = new Player(newModel, position, rotation, scale);
	objects.push_back(newPlayer);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", newPlayer, &eventQueue);
	PhysEvent* newPhys = new PhysEvent("PHYSSpawn", &eventQueue, newPlayer, "dynamic", "Player");

	UI.myPlayer = newPlayer;
	physics.myPlayer = newPlayer;
	graphics.myPlayer = newPlayer;
}

void Engine::InstantiateRequest()
{
	int modelID; int textureID; MyVec3 position; MyVec3 scale; MyVec3 rotation;

	std::cout << std::endl << "Welcome to instantiation! " << std::endl << "-----" << std::endl;

	std::cout << "Please select a model from the following list: " << std::endl;

	for (int i = 0; i < assets.models.size(); i++)
	{
		std::cout << i << "-" << assets.models[i]->modelName << std::endl;
	}

	bool modValid = false;
	while (!modValid)
	{
		std::cout << "Please make your selection: " << std::endl;
		std::cin >> modelID;

		if (modelID >= 0 && modelID <= assets.models.size())
		{
			modValid = true;
		}

		else
		{
			std::cout << std::endl << "Incorrect input please make a new selection" << std::endl;
		}
	}


	std::cout << "Please select texture from the following list: " << std::endl;

	for (int i = 0; i < assets.models[modelID]->texturePaths->size(); i++)
	{
		std::cout << i << "-" << (*assets.models[modelID]->texturePaths)[i] << std::endl;
	}

	bool texValid = false;
	while (!texValid)
	{
		std::cout << "Please make your selection: " << std::endl;
		std::cin >> textureID;

		if (textureID >= 0 && textureID <= assets.models[modelID]->texturePaths->size())
		{
			texValid = true;
		}

		else
		{
			std::cout << std::endl << "Incorrect input please make a new selection" << std::endl;
		}
	}

	std::cout << "-----" << std::endl;

	std::cout << "Enter X Pos:" << std::endl;
	std::cin >> position.x;

	std::cout << "Enter Y Pos:" << std::endl;
	std::cin >> position.y;

	std::cout << "Enter Z Pos:" << std::endl;
	std::cin >> position.z;

	std::cout << "-----" << std::endl;

	std::cout << "Enter X Scale:" << std::endl;
	std::cin >> scale.x;

	std::cout << "Enter Y Scale:" << std::endl;
	std::cin >> scale.y;

	std::cout << "Enter Z Scale:" << std::endl;
	std::cin >> scale.z;

	std::cout << "-----" << std::endl;

	std::cout << "Enter X Rotation:" << std::endl;
	std::cin >> rotation.x;

	std::cout << "Enter Y Rotation:" << std::endl;
	std::cin >> rotation.y;

	std::cout << "Enter Z Rotation:" << std::endl;
	std::cin >> rotation.z;

	std::cout << "-----" << std::endl;

	std::cout << std::endl << "Instantiating..." << std::endl;

	Model* newModel = new Model(assets.models[modelID]->mesh, assets.models[modelID]->texturePaths, assets.models[modelID]->modelPath, assets.models[modelID]->type, assets.models[modelID]->modelName);

	newModel->texturePath = (*newModel->texturePaths)[textureID];

	std::cout << "Position:" << position.x << "," << position.y << "," << position.z << std::endl;
	std::cout << "Scale:" << scale.x << "," << scale.y << "," << scale.z << std::endl;
	std::cout << "Rotation:" << rotation.x << "," << rotation.y << "," << rotation.z << std::endl;

	GameObject* newObject = new GameObject(newModel, position, rotation, scale);
	objects.push_back(newObject);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", newObject, &eventQueue);
	PhysEvent* newPhys = new PhysEvent("PHYSSpawn", &eventQueue, newObject, "dynamic", "Player");
}

void Engine::LoadLevel(int number)
{
	if (!(objects.empty()))
	{
		ClearScene();
	}


	number = 1;
	std::vector<SpawnData*> spawnData;
	bool success = false;

	dataInput.LoadDataObjects(&spawnData, number, &success);

	if (success)
	{
		bool firstPlatformSpawned = false;
		for (int i = 0; i < spawnData.size(); i++)
		{
			if ((spawnData[i]->modelID == mainManager->platformID) && firstPlatformSpawned)
			{
				std::cout << "Spawning button" << std::endl;
				Instantiate(mainManager->buttonID, 0, MyVec3(spawnData[i]->position.x, spawnData[i]->position.y + 10, spawnData[i]->position.z), MyVec3(0.1, 0.1, 0.1), spawnData[i]->rotation, spawnData[i]->rbType, "Button");
			}

			if ((spawnData[i]->modelID == mainManager->platformID) && !firstPlatformSpawned)
			{
				std::cout << "Spawning player" << std::endl;
				firstPlatformSpawned = true;
				InstantiatePlayer(mainManager->playerID, 2, MyVec3(spawnData[i]->position.x, spawnData[i]->position.y + 100, spawnData[i]->position.z), mainManager->PlayerSize, spawnData[i]->rotation);
			}

			std::cout << "Spawning platform" << std::endl;
			std::cout << "Instantiating scene element " << i << std::endl;
			Instantiate(spawnData[i]->modelID, spawnData[i]->textureID, spawnData[i]->position, spawnData[i]->scale, spawnData[i]->rotation, spawnData[i]->rbType, spawnData[i]->cfType);
		}
	}
	else
	{
		std::cout << "Failed to load level " << number << std::endl;
	}

	
}

void Engine::InstantiateRandom()
{
	int modelID = 1;
	int textureID = 0;
	
	MyVec3 position(0, 0, 0);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(-500, 500);

	position.x = dist(gen);
	position.y = dist(gen);
	position.z = dist(gen);

	MyVec3 scale(0.05, 0.05, 0.05);
	MyVec3 rotation(0, 0, 0);

	std::cout << std::endl << "Instantiating..." << std::endl;

	Model* newModel = new Model(assets.models[modelID]->mesh, assets.models[modelID]->texturePaths, assets.models[modelID]->modelPath, assets.models[modelID]->type, assets.models[modelID]->modelName);

	newModel->texturePath = (*newModel->texturePaths)[textureID];

	GameObject* newObject = new GameObject(newModel, position, rotation, scale);
	objects.push_back(newObject);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", newObject, &eventQueue);
	PhysEvent* newPhys = new PhysEvent("PHYSSpawn", &eventQueue, newObject, "dynamic", "Player");
}
