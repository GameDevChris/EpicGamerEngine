#pragma once
#include "Event.h"
class GFXEvent :
	public Event
{
public:
	GFXEvent(std::string type, vector<Event*>* queue);
	GFXEvent(std::string type, GameObject* obj, vector<Event*>* queue);
};

