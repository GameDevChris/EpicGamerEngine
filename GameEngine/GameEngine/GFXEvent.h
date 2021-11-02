#pragma once
#include "Event.h"
class GFXEvent :
	public Event
{
public:
	GFXEvent(std::string type, int modelType, vector<Event*>* queue);
	GFXEvent(std::string type, vector<Event*>* queue);
};

