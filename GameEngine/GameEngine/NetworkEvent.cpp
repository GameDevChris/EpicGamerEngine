#include "NetworkEvent.h"

NetworkEvent::NetworkEvent(std::string type, int newScore, vector<Event*>* queue)
{
	myData = new EventData();

	eventSubsystem = NetworkSub;

	if (type == "BotAddScore")
	{
		eventType = BotAddScore;
	}
	else
	{
		cout << "ERROR, unknown Network event type!" << endl;
	}

	myData->myScore = newScore;

	EQueue = queue;

	Throw();
}