#include "SoundEvent.h"

SoundEvent::SoundEvent(std::string type, std::vector<Event*>* queue)
{
	myData = new EventData();

	eventSubsystem = SoundSub;

	if (type == "PlayBGMusic")
	{
		eventType = PlayBGMusic;
	}

	else
	{
		std::cout << "ERROR, unknown Sound event type!" << std::endl;
	}

	EQueue = queue;

	Throw();
}
