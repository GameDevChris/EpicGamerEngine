#include "Event.h"

Event::Event(std::string type)
{
	if (type == "PHYSDefault")
	{
		eventType = PHYSDefault;
		eventSubsystem = PhysicsSub;
	}

	else 
	{
		std::cout << "ERROR, unknown event type!" << std::endl;
	}
}

Event::Event(std::string type, std::vector<Event*>* queue)
{
	if (type == "Instantiate")
	{
		eventType = Instantiate;
		eventSubsystem = General;
	}

	else if (type == "ChrisLegion")
	{
		eventType = ChrisLegion;
		eventSubsystem = General;
	}

	else if (type == "DeleteAll")
	{
		eventType = DeleteAll;
		eventSubsystem = General;
	}

	else if (type == "PlayerLost")
	{
		eventType = PlayerLost;
		eventSubsystem = General;
	}

	else if (type == "GameStart")
	{
		eventType = GameStart;
		eventSubsystem = General;
	}

	else if (type == "ButtonCheck")
	{
		eventType = ButtonCheck;
		eventSubsystem = General;
	}

	else if (type == "OpenLuaFile")
	{
		eventType = OpenLuaFile;
		eventSubsystem = General;
	}
	
	else if (type == "OpenModelFile")
	{
		eventType = OpenModelFile;
		eventSubsystem = General;
	}

	else if (type == "OpenLayoutFile")
	{
		eventType = OpenLayoutFile;
		eventSubsystem = General;
	}
	
	else if (type == "OpenMusicFile")
	{
		eventType = OpenMusicFile;
		eventSubsystem = General;
	}

	else
	{
		std::cout << "ERROR, unknown event type!" << std::endl;
	}

	EQueue = queue;

	Throw();
}

Event::Event(std::string type, std::vector<Event*>* queue, int levelNumber)
{
	myData = new EventData();
	eventSubsystem = General;

	if (type == "LoadLevel")
	{
		eventType = LoadLevel;
	}

	else
	{
		std::cout << "ERROR, unknown event type!" << std::endl;
	}

	myData->levelNumber = &levelNumber;

	EQueue = queue;

	Throw();
}

Event::Event(std::string type, std::vector<Event*>* queue, int* modelID, int* textureID, MyVec3* position, MyVec3* scale, MyVec3* rotation)
{
	myData = new EventData();

	if (type == "InstantiatePlayer")
	{
		eventType = InstantiatePlayer;
		eventSubsystem = General;
	}

	else
	{
		std::cout << "ERROR, unknown event type!" << std::endl;
	}

	myData->myModID = modelID;
	myData->myTexID = textureID;
	myData->myPos = position;
	myData->myScale = scale;
	myData->myRot = rotation;
	EQueue = queue;

	Throw();
}

Event::Event(std::string type, std::vector<Event*>* queue, int* modelID, int* textureID, std::string* rbType, std::string* colFilterType,MyVec3* position, MyVec3* scale, MyVec3* rotation)
{
	myData = new EventData();

	if (type == "InstantiateCustom")
	{
		eventType = InstantiateCustom;
		eventSubsystem = General;
	}

	else
	{
		std::cout << "ERROR, unknown event type!" << std::endl;
	}

	myData->myModID = modelID;
	myData->myTexID = textureID;
	myData->myPos = position;
	myData->myScale = scale;
	myData->myRot = rotation;
	myData->RBType = *rbType;
	myData->CFType = *colFilterType;


	EQueue = queue;

	Throw();
}

Event::Event()
{
}

void Event::Throw()
{
	EQueue->push_back(this);
}
