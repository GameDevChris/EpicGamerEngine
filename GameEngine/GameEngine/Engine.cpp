#include "Engine.h"

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
	eventQueue.clear();
	lateEventQueue.clear();
	std::cout << "Engine started, help" << std::endl;

	physics.name = "EpicGamerPhysics";
	physics.engineEventQueue = &eventQueue;
	physics.lateEngineEventQueue = &lateEventQueue;
	physics.Start();

	graphics.name = "EpicGamerGraphics";
	graphics.engineEventQueue = &eventQueue;
	graphics.lateEngineEventQueue = &lateEventQueue;
	graphics.Start();

	dataInput.name = "EpicGamerDataInput";
	dataInput.engineEventQueue = &eventQueue;
	dataInput.lateEngineEventQueue = &lateEventQueue;
	dataInput.Start();

	UI.name = "EpicGamerUI";
	UI.engineEventQueue = &eventQueue;
	UI.lateEngineEventQueue = &lateEventQueue;
	UI.Start();

	assets.name = "EpicGamerAssets";
	assets.engineEventQueue = &eventQueue;
	assets.lateEngineEventQueue = &lateEventQueue;
	assets.Start();

	assets.device = graphics.device;
	assets.driver = graphics.driver;
	assets.smgr = graphics.smgr;

	network.name = "EpicGamerNetwork";
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
		for (int i = 0; i < eventQueue.size(); i++)
		{
			if (eventQueue[i]->eventSubsystem == eventQueue[i]->General)
			{
				if (eventQueue[i]->eventType == eventQueue[i]->Instantiate)
				{
					InstantiateRequest();
					
					delete(eventQueue[i]);
					eventQueue.erase(eventQueue.begin() + i);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->ChrisLegion)
				{
					for (int i = 0; i < 1; i++)
					{
						InstantiateRandom();
					}

					delete(eventQueue[i]);
					eventQueue.erase(eventQueue.begin() + i);
				}
			}
		}
	}

	graphics.Update();
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
					eventQueue.erase(eventQueue.begin() + i);
				}

				else if (eventQueue[i]->eventType == eventQueue[i]->InstantiatePlayer)
				{

					InstantiatePlayer(*(eventQueue[i]->myData->myModID), *(eventQueue[i]->myData->myTexID), *(eventQueue[i]->myData->myPos), *(eventQueue[i]->myData->myScale), *(eventQueue[i]->myData->myRot));
					delete(eventQueue[i]);
					eventQueue.erase(eventQueue.begin() + i);
				}
			}
		}
	}

	graphics.Update();
	physics.Update();

	network.Update();

	UI.LateUpdate();

	if (graphics.QuitCall)
	{
		finished = true;
	}

	if (finished)
	{
		graphics.Exit();
	}
	
	//for(int i = 0; i < eventQueue.size(); i++)
	//{
	//	delete (eventQueue[i]);
	//}

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
