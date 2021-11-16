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
	cout << "Engine started, help" << endl;

	physics.name = "EpicGamerPhysics";
	physics.engineEventQueue = &eventQueue;
	physics.Start();

	graphics.name = "EpicGamerGraphics";
	graphics.engineEventQueue = &eventQueue;
	graphics.Start();

	dataInput.name = "EpicGamerDataInput";
	dataInput.engineEventQueue = &eventQueue;
	dataInput.Start();

	UI.name = "EpicGamerUI";
	UI.engineEventQueue = &eventQueue;
	UI.Start();

	assets.name = "EpicGamerAssets";
	assets.engineEventQueue = &eventQueue;
	assets.Start();

	assets.device = graphics.device;
	assets.driver = graphics.driver;
	assets.smgr = graphics.smgr;


	//Instantiate(0, Vec3(-60, 15, 0), Vec3(7, 7, 7), Vec3(0, 0, 0));

	UseData();
}

void Engine::Update()
{
	if (!eventQueue.empty())
	{
		cout << "There are "<< eventQueue.size() << " events!" << endl;
		for (int i = 0; i < eventQueue.size(); i++)
		{
			cout << "Event to happen in subsystem " << eventQueue[i]->ReturnSubsystem() << endl;
		}
	}
	
	UI.Update();
	physics.Update();
	assets.Update();

	if (!eventQueue.empty())
	{
		for (int i = 0; i < eventQueue.size(); i++)
		{
			if (eventQueue[i]->eventSubsystem == eventQueue[i]->General)
			{
				if (eventQueue[i]->eventType == eventQueue[i]->Instantiate)
				{
					//Instantiate(0, 0, Vec3(-60, 15, 0), Vec3(7, 7, 7), Vec3(0, 0, 0));
					
					for (int i = 0; i < 1000; i++)
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
}

void Engine::Instantiate(int modelID, int textureID, Vec3 position, Vec3 scale, Vec3 rotation)
{
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

	for(int i = 0; i < assets.models[modelID]->texturePaths->size(); i++)
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

	Model* newModel = new Model(assets.models[modelID]->mesh, assets.models[modelID]->texturePaths, assets.models[modelID]->modelPath, assets.models[modelID]->type);
		
	newModel->texturePath = (*newModel->texturePaths)[textureID];

	GameObject* newObject = new GameObject(newModel, position, rotation, scale);
	objects.push_back(newObject);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", newObject, &eventQueue);

	//GFXEvent* leftEvent = new GFXEvent("GFXLeft", &eventQueue);
}

void Engine::InstantiateRandom()
{
	int modelID = 1;
	int textureID = 0;
	
	Vec3 position(0, 0, 0);

	random_device rd;   
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 1000); // distribute results between 1 and 6 inclusive.

	position.x = dist(gen);
	position.y = dist(gen);
	position.z = dist(gen);

	Vec3 scale(0.02, 0.02, 0.02);
	Vec3 rotation(0, 0, 0);

	cout << endl << "Instantiating..." << endl;

	Model* newModel = new Model(assets.models[modelID]->mesh, assets.models[modelID]->texturePaths, assets.models[modelID]->modelPath, assets.models[modelID]->type);

	newModel->texturePath = (*newModel->texturePaths)[textureID];

	GameObject* newObject = new GameObject(newModel, position, rotation, scale);
	objects.push_back(newObject);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", newObject, &eventQueue);
}
