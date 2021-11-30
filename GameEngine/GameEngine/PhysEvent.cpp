#include "PhysEvent.h"

PhysEvent::PhysEvent(std::string type, std::vector<Event*>* queue, GameObject* object, std::string rbType)
{
	myData = new EventData();
	eventSubsystem = PhysicsSub;
	eventType = PHYSDefault;

	if (type == "PHYSSpawn")
	{
		eventType = PHYSSpawn;
	}

	else
	{
		std::cout << "ERROR, unknown PHYS event type!" << std::endl;
	}

	myData->targetObject = object;
	myData->RBType = rbType;

	EQueue = queue;

	Throw();
}

PhysEvent::PhysEvent(std::string type, std::vector<Event*>* queue, Player* player, MyVec3* force)
{
	myData = new EventData();
	eventSubsystem = PhysicsSub;
	eventType = PHYSDefault;

	if (type == "PlayerMove")
	{
		eventType = PlayerMove;
	}

	else if (type == "PlayerRotate")
	{
		eventType = PlayerRotate;
	}

	else if (type == "PlayerImpulse")
	{
		eventType = PlayerImpulse;
	}

	else
	{
		std::cout << "ERROR, unknown PHYS event type!" << std::endl;
	}

	myData->targetPlayer = player;
	myData->myForce = force;

	EQueue = queue;

	Throw();

}
