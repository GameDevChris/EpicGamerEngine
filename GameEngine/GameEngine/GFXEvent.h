#pragma once
#include "Event.h"
class GFXEvent :
	public Event
{
public:
	GFXEvent(std::string type, std::vector<Event*>* queue);
	GFXEvent(std::string type, GameObject* obj, std::vector<Event*>* queue);
};

