#include "Engine.h"

Engine::Engine()
{

}

void Engine::UseData()
{
	cout << endl;
	for (int i = 0; i < dataInput.dataVector.size(); i++) 
	{
		switch (dataInput.dataVector[i])
		{
			case '0':
			{
				cout << "adding physics event" << endl;
				Event newPhysEvent("PHYSDefault");
				ThrowEvent(newPhysEvent);
			}
			break;
			

			case '1':
			{
				cout << "adding graphics event" << endl;
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
	cout << "Engine started, help" << endl;

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
			cout << "Event to happen in subsystem " << eventQueue[i]->ReturnSubsystem() << endl;
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

					Instantiate(*(eventQueue[i]->myData->myModID), *(eventQueue[i]->myData->myTexID), *(eventQueue[i]->myData->myPos), *(eventQueue[i]->myData->myScale), *(eventQueue[i]->myData->myRot), eventQueue[i]->myData->RBType);
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

void Engine::Instantiate(int modelID, int textureID, MyVec3 position, MyVec3 scale, MyVec3 rotation, std::string rbType)
{
	cout << endl << "Instantiating..." << endl;

	Model* newModel = new Model(assets.models[modelID]->mesh, assets.models[modelID]->texturePaths, assets.models[modelID]->modelPath, assets.models[modelID]->type, assets.models[modelID]->modelName);

	newModel->texturePath = (*newModel->texturePaths)[textureID];

	GameObject* newObject = new GameObject(newModel, position, rotation, scale);
	objects.push_back(newObject);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", newObject, &eventQueue);
	PhysEvent* newPhys = new PhysEvent("PHYSSpawn", &eventQueue, newObject, rbType);
}

void Engine::InstantiatePlayer(int modelID, int textureID, MyVec3 position, MyVec3 scale, MyVec3 rotation)
{
	cout << endl << "Instantiating Player..." << endl;

	Model* newModel = new Model(assets.models[modelID]->mesh, assets.models[modelID]->texturePaths, assets.models[modelID]->modelPath, assets.models[modelID]->type, assets.models[modelID]->modelName);

	newModel->texturePath = (*newModel->texturePaths)[textureID];

	Player* newPlayer = new Player(newModel, position, rotation, scale);
	objects.push_back(newPlayer);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", newPlayer, &eventQueue);
	PhysEvent* newPhys = new PhysEvent("PHYSSpawn", &eventQueue, newPlayer, "dynamic");

	UI.myPlayer = newPlayer;
}

void Engine::InstantiateRequest()
{
	int modelID; int textureID; MyVec3 position; MyVec3 scale; MyVec3 rotation;

	cout << endl << "Welcome to instantiation! " << endl << "-----" << endl;

	cout << "Please select a model from the following list: " << endl;

	for (int i = 0; i < assets.models.size(); i++)
	{
		cout << i << "-" << assets.models[i]->modelName << endl;
	}

	bool modValid = false;
	while (!modValid)
	{
		cout << "Please make your selection: " << endl;
		cin >> modelID;

		if (modelID >= 0 && modelID <= assets.models.size())
		{
			modValid = true;
		}

		else
		{
			cout << endl << "Incorrect input please make a new selection" << endl;
		}
	}


	cout << "Please select texture from the following list: " << endl;

	for (int i = 0; i < assets.models[modelID]->texturePaths->size(); i++)
	{
		cout << i << "-" << (*assets.models[modelID]->texturePaths)[i] << endl;
	}

	bool texValid = false;
	while (!texValid)
	{
		cout << "Please make your selection: " << endl;
		cin >> textureID;

		if (textureID >= 0 && textureID <= assets.models[modelID]->texturePaths->size())
		{
			texValid = true;
		}

		else
		{
			cout << endl << "Incorrect input please make a new selection" << endl;
		}
	}

	cout << "-----" << endl;

	cout << "Enter X Pos:" << endl;
	cin >> position.x;

	cout << "Enter Y Pos:" << endl;
	cin >> position.y;

	cout << "Enter Z Pos:" << endl;
	cin >> position.z;

	cout << "-----" << endl;

	cout << "Enter X Scale:" << endl;
	cin >> scale.x;

	cout << "Enter Y Scale:" << endl;
	cin >> scale.y;

	cout << "Enter Z Scale:" << endl;
	cin >> scale.z;

	cout << "-----" << endl;

	cout << "Enter X Rotation:" << endl;
	cin >> rotation.x;

	cout << "Enter Y Rotation:" << endl;
	cin >> rotation.y;

	cout << "Enter Z Rotation:" << endl;
	cin >> rotation.z;

	cout << "-----" << endl;

	cout << endl << "Instantiating..." << endl;

	Model* newModel = new Model(assets.models[modelID]->mesh, assets.models[modelID]->texturePaths, assets.models[modelID]->modelPath, assets.models[modelID]->type, assets.models[modelID]->modelName);

	newModel->texturePath = (*newModel->texturePaths)[textureID];

	cout << "Position:" << position.x << "," << position.y << "," << position.z << endl;
	cout << "Scale:" << scale.x << "," << scale.y << "," << scale.z << endl;
	cout << "Rotation:" << rotation.x << "," << rotation.y << "," << rotation.z << endl;

	GameObject* newObject = new GameObject(newModel, position, rotation, scale);
	objects.push_back(newObject);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", newObject, &eventQueue);
	PhysEvent* newPhys = new PhysEvent("PHYSSpawn", &eventQueue, newObject, "dynamic");
}

void Engine::InstantiateRandom()
{
	int modelID = 1;
	int textureID = 0;
	
	MyVec3 position(0, 0, 0);

	random_device rd;   
	mt19937 gen(rd());
	uniform_int_distribution<> dist(-500, 500);

	position.x = dist(gen);
	position.y = dist(gen);
	position.z = dist(gen);

	MyVec3 scale(0.05, 0.05, 0.05);
	MyVec3 rotation(0, 0, 0);

	cout << endl << "Instantiating..." << endl;

	Model* newModel = new Model(assets.models[modelID]->mesh, assets.models[modelID]->texturePaths, assets.models[modelID]->modelPath, assets.models[modelID]->type, assets.models[modelID]->modelName);

	newModel->texturePath = (*newModel->texturePaths)[textureID];

	GameObject* newObject = new GameObject(newModel, position, rotation, scale);
	objects.push_back(newObject);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", newObject, &eventQueue);
	PhysEvent* newPhys = new PhysEvent("PHYSSpawn", &eventQueue, newObject, "dynamic");
}
