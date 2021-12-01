#pragma once
#include "Event.h"

class PhysEvent :
	public Event
{
public:

	PhysEvent(std::string type, std::vector<Event*>* queue, GameObject* object, std::string rbType, std::string cfType);
	PhysEvent(std::string type, std::vector<Event*>* queue, Player* player, MyVec3* force);
};

