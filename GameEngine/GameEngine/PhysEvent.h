#pragma once
#include "Event.h"
class PhysEvent :
	public Event
{
public:

	PhysEvent(std::string type, vector<Event*>* queue, GameObject* object, std::string rbType);
};

