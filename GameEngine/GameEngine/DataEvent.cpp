#include "DataEvent.h"

DataEvent::DataEvent(std::string type, std::vector<Event*>* queue)
{
	eventSubsystem = DataSub;

	if (type == "DataLoadLevel")
	{
		eventType = DataLoadLevel;
	}
	else
	{
		std::cout << "ERROR, unknown Data event type!" << std::endl;
	}

	EQueue = queue;

	Throw();
}
