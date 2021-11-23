#pragma once
#include "Event.h"
class NetworkEvent :
	public Event
{
public:
	NetworkEvent(std::string type, int newScore, vector<Event*>* queue);
};

