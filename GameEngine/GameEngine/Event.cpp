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
		cout << "ERROR, unknown event type!" << endl;
	}
}

Event::Event(std::string type, vector<Event*>* queue)
{
	if (type == "Instantiate")
	{
		eventType = Instantiate;
		eventSubsystem = General;
	}

	else
	{
		cout << "ERROR, unknown event type!" << endl;
	}

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
