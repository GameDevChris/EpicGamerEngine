#include "PhysEvent.h"

PhysEvent::PhysEvent(std::string type, vector<Event*>* queue, GameObject* object, std::string rbType)
{
	myData = new EventData();
	eventSubsystem = PhysicsSub;
	eventType = PHYSDefault;

	if (type == "PHYSSpawn")
	{
		eventType = PHYSSpawn;
		cout << "New phys spawn event executed" << endl;
	}

	else
	{
		cout << "ERROR, unknown PHYS event type!" << endl;
	}

	myData->targetObject = object;
	myData->RBType = rbType;

	EQueue = queue;

	Throw();
}
