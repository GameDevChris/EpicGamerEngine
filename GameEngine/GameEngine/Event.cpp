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

Event::Event()
{
}

void Event::Throw()
{
	EQueue->push_back(this);
}
