#include "GFXEvent.h"

GFXEvent::GFXEvent(std::string type, std::vector<Event*>* queue)
{
	eventSubsystem = GraphicsSub;
	
	eventType = GFXDefault;

	if (type == "GFXQuit")
	{
		eventType = GFXQuit;
	}

	else if (type == "GFXUp")
	{
		eventType = GFXUp;
	}

	else if (type == "GFXDown")
	{
		eventType = GFXDown;
	}

	else if (type == "GFXLeft")
	{
		eventType = GFXLeft;
	}

	else if (type == "GFXRight")
	{
		eventType = GFXRight;
	}

	else if (type == "GFXCamUp")
	{
		eventType = GFXCamUp;
	}

	else if (type == "GFXCamDown")
	{
		eventType = GFXCamDown;
	}

	else if (type == "GFXCamLeft")
	{
		eventType = GFXCamLeft;
	}

	else if (type == "GFXCamRight")
	{
		eventType = GFXCamRight;
	}

	else if (type == "GFXCamForward")
	{
		eventType = GFXCamForward;
	}

	else if (type == "GFXCamBackward")
	{
		eventType = GFXCamBackward;
	}

	else if (type == "GFXSpawn")
	{
		eventType = GFXSpawn;
	}

	else
	{
		std::cout << "ERROR, unknown GFX event type!" << std::endl;
	}

	EQueue = queue;

	Throw();
}

GFXEvent::GFXEvent(std::string type, GameObject* obj, std::vector<Event*>* queue)
{
	myData = new EventData();
	eventSubsystem = GraphicsSub;
	eventType = GFXDefault;
	
	if (type == "GFXSpawn")
	{
		eventType = GFXSpawn;
		std::cout << "New spawn event executed" << std::endl;
	}
	
	else
	{
		std::cout << "ERROR, unknown GFX event type!" << std::endl;
	}
	
	myData->targetObject = obj;
	
	EQueue = queue;
	
	Throw();
}
