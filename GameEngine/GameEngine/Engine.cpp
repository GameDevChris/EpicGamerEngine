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

	if (!eventQueue.empty())
	{
		for (int i = 0; i < eventQueue.size(); i++)
		{
			std::cout << "Event to happen in subsystem " << eventQueue[i]->ReturnSubsystem() << std::endl;
		}
	}
	
	UI.Update();
	assets.Update();

	if (!eventQueue.empty())
	{
		
		/*for (std::vector<Event*>::iterator it = eventQueue.begin(); it != eventQueue.end();)
		{
			bool hasErased = false;

			if ((*it)->eventSubsystem == (*it)->General)
			{
				if ((*it)->eventType == (*it)->Instantiate)
				{
					InstantiateRequest();

					delete(*it);
					it = eventQueue.erase(it);
					hasErased = true;
				}

				else if ((*it)->eventType == (*it)->ChrisLegion)
				{
					for (int i = 0; i < 1; i++)
					{
						InstantiateRandom();
					}

					delete(*it);
					it = eventQueue.erase(it);
					hasErased = true;
				}
			}

			if (hasErased == false)
				it++;
		}*/

		for (int i = 0; i < eventQueue.size(); i++)
		{
			if (eventQueue[i]->eventSubsystem == eventQueue[i]->General)
			{
				if (eventQueue[i]->eventType == eventQueue[i]->Instantiate)
				{
					InstantiateRequest();
					
					delete(eventQueue[i]);
				//	eventQueue.erase(eventQueue.begin() + i);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->ChrisLegion)
				{
					for (int i = 0; i < 1; i++)
					{
						InstantiateRandom();
					}

					delete(eventQueue[i]);
				//	eventQueue.erase(eventQueue.begin() + i);
				}
			}
		}
	}

	graphics.Update();

	//dataInput.Update();
	
	
	physics.Update();


	

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
					//	eventQueue.erase(eventQueue.begin() + i);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->InstantiatePlayer)
				{

					InstantiatePlayer(*(eventQueue[i]->myData->myModID), *(eventQueue[i]->myData->myTexID), *(eventQueue[i]->myData->myPos), *(eventQueue[i]->myData->myScale), *(eventQueue[i]->myData->myRot));
					delete(eventQueue[i]);
					//	eventQueue.erase(eventQueue.begin() + i);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->LoadLevel)
				{
					LoadLevel(*(eventQueue[i]->myData->levelNumber));
					delete(eventQueue[i]);
					//	eventQueue.erase(eventQueue.begin() + i);
				}
			}
		}

		/*for (std::vector<Event*>::iterator it = eventQueue.begin(); it != eventQueue.end();)
		{
			bool hasErased = false;

			if ((*it)->eventSubsystem == (*it)->General)
			{
				if ((*it)->eventType == (*it)->InstantiateCustom)
				{

					Instantiate(*((*it)->myData->myModID), *((*it)->myData->myTexID), *((*it)->myData->myPos), *((*it)->myData->myScale),
						*((*it)->myData->myRot), (*it)->myData->RBType, (*it)->myData->CFType);
					delete((*it));
					it = eventQueue.erase(it);
					hasErased = true;
				}

				else if ((*it)->eventType == (*it)->InstantiatePlayer)
				{

					InstantiatePlayer(*((*it)->myData->myModID), *((*it)->myData->myTexID), *((*it)->myData->myPos),
						*((*it)->myData->myScale), *((*it)->myData->myRot));
					delete((*it));
					it = eventQueue.erase(it);
					hasErased = true;
				}

				else if ((*it)->eventType == (*it)->LoadLevel)
				{
					LoadLevel(*((*it)->myData->levelNumber));
					delete((*it));
					it = eventQueue.erase(it);
					hasErased = true;
				}

				if (hasErased == false)
					it++;
			}
		}
	}*/

		graphics.Update();
		physics.Update();

		network.Update();


		UI.LateUpdate();

		if (!eventQueue.empty())
		{
			for (int i = 0; i < eventQueue.size(); i++)
			{
				if (eventQueue[i]->eventSubsystem == eventQueue[i]->General)
				{
					if (eventQueue[i]->eventType == eventQueue[i]->InstantiateCustom)
					{

						Instantiate(*(eventQueue[i]->myData->myModID), *(eventQueue[i]->myData->myTexID), *(eventQueue[i]->myData->myPos), *(eventQueue[i]->myData->myScale), *(eventQueue[i]->myData->myRot), eventQueue[i]->myData->RBType, eventQueue[i]->myData->CFType);
						//	eventQueue.erase(eventQueue.begin() + i);
						delete(eventQueue[i]);
					}

					else if (eventQueue[i]->eventType == eventQueue[i]->InstantiatePlayer)
					{

						InstantiatePlayer(*(eventQueue[i]->myData->myModID), *(eventQueue[i]->myData->myTexID), *(eventQueue[i]->myData->myPos), *(eventQueue[i]->myData->myScale), *(eventQueue[i]->myData->myRot));
						delete(eventQueue[i]);
						//	eventQueue.erase(eventQueue.begin() + i);
					}

					else if (eventQueue[i]->eventType == eventQueue[i]->LoadLevel)
					{
						LoadLevel(*(eventQueue[i]->myData->levelNumber));
						delete(eventQueue[i]);
						//	eventQueue.erase(eventQueue.begin() + i);
					}
				}
			}

			/*for (std::vector<Event*>::iterator it = eventQueue.begin(); it != eventQueue.end();)
			{
				bool hasErased = false;

				if ((*it)->eventSubsystem == (*it)->General)
				{
					if ((*it)->eventType == (*it)->InstantiateCustom)
					{

						Instantiate(*((*it)->myData->myModID), *((*it)->myData->myTexID), *((*it)->myData->myPos), *((*it)->myData->myScale),
							*((*it)->myData->myRot), (*it)->myData->RBType, (*it)->myData->CFType);
						delete((*it));
						it = eventQueue.erase(it);
						hasErased = true;
					}

					else if ((*it)->eventType == (*it)->InstantiatePlayer)
					{

						InstantiatePlayer(*((*it)->myData->myModID), *((*it)->myData->myTexID), *((*it)->myData->myPos),
							*((*it)->myData->myScale), *((*it)->myData->myRot));
						delete((*it));
						it = eventQueue.erase(it);
						hasErased = true;
						//	eventQueue.erase(eventQueue.begin() + i);
					}

					else if ((*it)->eventType == (*it)->LoadLevel)
					{
						LoadLevel(*((*it)->myData->levelNumber));
						delete((*it));
						it = eventQueue.erase(it);
						hasErased = true;
						//	eventQueue.erase(eventQueue.begin() + i);
					}
				}

				if (hasErased == false)
					it++;
			}*/
		}
	}

	if (graphics.QuitCall)
	{
		finished = true;
	}

	if (finished)
	{
		graphics.Exit();
	}
	
	/*for(int i = 0; i < eventQueue.size(); i++)
	{ 
		delete (eventQueue[i]);
	}*/

	eventQueue.clear();
	lateEventQueue.clear();

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->SyncTransform();
	}
}

void Engine::Instantiate(int modelID, int textureID, MyVec3 position, MyVec3 scale, MyVec3 rotation, std::string rbType, std::string cfType)
{

	std::cout << std::endl << "Instantiating..." << std::endl;

	//modelID = 6;
	//textureID = 0;
	//rbType = "static";
	//cfType = "Ground";

	//position = MyVec3(0, 0, 0);
	//scale = MyVec3(1, 1, 1);
	//rotation = MyVec3(0, 0, 0);

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
	number = 1;
	std::vector<SpawnData*> spawnData;
	bool success = false;

	dataInput.LoadDataObjects(&spawnData, number, &success);

	if (success)
	{
		for (int i = 0; i < 1; i++)
		{
		
			std::cout << "Instantiating scene element " << i << std::endl;
			Instantiate(spawnData[i]->modelID, spawnData[i]->textureID, spawnData[i]->position, spawnData[i]->scale, spawnData[i]->rotation, spawnData[i]->rbType, spawnData[i]->cfType);
		}

		//InstantiateTimer(1, spawnData, 0);
		//InstantiateTimer(1, spawnData, 1);
		//InstantiateTimer(0, spawnData, 0);
		//InstantiateTimer(1, spawnData, 1);


		//Instantiate(spawnData[0]->modelID, spawnData[0]->textureID, spawnData[0]->position, spawnData[0]->scale, spawnData[0]->rotation, spawnData[0]->rbType, spawnData[0]->cfType);
		//Instantiate(spawnData[1]->modelID, spawnData[1]->textureID, spawnData[1]->position, spawnData[1]->scale, spawnData[1]->rotation, spawnData[1]->rbType, spawnData[1]->cfType);
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
