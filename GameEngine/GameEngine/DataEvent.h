#pragma once
#include "Event.h"
class DataEvent :
	public Event
{
public:
	DataEvent(std::string type, std::vector<Event*>* queue);
};

