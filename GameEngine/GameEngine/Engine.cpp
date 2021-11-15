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
	graphics.Update();
	assets.Update();

	if (!eventQueue.empty())
	{
		for (int i = 0; i < eventQueue.size(); i++)
		{
			if (eventQueue[i]->eventSubsystem == eventQueue[i]->General)
			{
				if (eventQueue[i]->eventType == eventQueue[i]->Instantiate)
				{
					cout << "Instantiating" << endl;
					Instantiate(0, Vec3(-60, 15, 0), Vec3(7, 7, 7), Vec3(0, 0, 0));

					delete (eventQueue[i]);
				}
			}
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

	eventQueue.clear();
}

void Engine::Instantiate(int ID, Vec3 position, Vec3 scale, Vec3 rotation)
{
	GameObject newObject;
	newObject.myModel = assets.models[ID];
	newObject.Position = position;
	newObject.Scale = scale;
	newObject.Rotation = rotation;

	objects.push_back(&newObject);

	GFXEvent* newGFX = new GFXEvent("GFXSpawn", &newObject, &eventQueue);
}
