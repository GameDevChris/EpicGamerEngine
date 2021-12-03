#pragma once
#include "Event.h"
class SoundEvent :
	public Event
{
public:
	SoundEvent(std::string type, std::vector<Event*>* queue);
};

