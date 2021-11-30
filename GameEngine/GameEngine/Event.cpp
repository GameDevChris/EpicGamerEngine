#include "Event.h"

std::string Event::ReturnSubsystem()
{
	switch (eventSubsystem)
	{
		case PhysicsSub:
			return "Physics";
			break;

		case GraphicsSub:
			return "Graphics";
			break;
		
		case AssetSub:
			return "Asset";
			break;

	}

	return "Unknown";
}

std::string Event::ReturnEvent()
{
	switch (eventType)
	{
	case GFXDefault:
		return "GFXDefault";
		break;

	case GFXQuit:
		return "GFXQuit";
		break;
		
	case GFXUp:
		return "GFXUp";
		break;

	case GFXDown:
		return "GFXDown";
		break;

	case GFXLeft:
		return "GFXLeft";
		break;
	
	case GFXRight:
		return "GFXRight";
		break;

	case GFXSpawn:
		return "GFXSpawn";
		break;
			
	case GFXCamUp:
		return "GFXCamUp";
		break;

	case GFXCamDown:
		return "GFXCamDown";
		break;

	case GFXCamLeft:
		return "GFXCamLeft";
		break;

	case GFXCamRight:
		return "GFXCamRight";
		break;

	case GFXCamForward:
		return "GFXCamForward";
		break;

	case GFXCamBackward:
		return "GFXCamBackward";
		break;
	
	case PHYSDefault:
		return "PHYSDefault";
		break;
	
	case ASSETLoad:
		return "ASSETLoad";
		break;
	
	case ASSETAssign:
		return "ASSETAssign";
		break;

	case Instantiate:
		return "Instantiate";
		break;

	case ChrisLegion:
		return "ChrisLegion";
		break;
	}

	return "Unknown Event";
}

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

	else
	{
		std::cout << "ERROR, unknown event type!" << std::endl;
	}

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

Event::Event(std::string type, std::vector<Event*>* queue, int* modelID, int* textureID, std::string* rbType, MyVec3* position, MyVec3* scale, MyVec3* rotation)
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
