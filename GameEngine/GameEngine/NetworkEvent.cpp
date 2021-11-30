#include "NetworkEvent.h"

NetworkEvent::NetworkEvent(std::string type, int newScore, std::vector<Event*>* queue)
{
	myData = new EventData();

	eventSubsystem = NetworkSub;

	if (type == "BotAddScore")
	{
		eventType = BotAddScore;
	}

	else if (type == "BotPrintTop5")
	{
		eventType = BotPrintTop5;
	}

	else
	{
		std::cout << "ERROR, unknown Network event type!" << std::endl;
	}

	myData->myScore = newScore;

	EQueue = queue;

	Throw();
}