#include "AssetEvent.h"

AssetEvent::AssetEvent(std::string type, std::string modelPath, std::string texturePath, int modelType, vector<Event*>* queue)
{
	myData = new EventData();

	eventSubsystem = AssetSub;

	if (type == "ASSETLoad")
	{
		eventType = ASSETLoad;
	}

	else if (type == "ASSETAssign")
	{
		eventType = ASSETAssign;
	}

	else
	{
		cout << "ERROR, unknown Asset event type!" << endl;
	}

	myData->modPath = modelPath;
	myData->texPath = texturePath;
	myData->modType = modelType;

	EQueue = queue;
}

AssetEvent::AssetEvent(std::string type)
{
	myData = new EventData();
	eventSubsystem = AssetSub;

	if (type == "ASSETLoad")
	{
		eventType = ASSETLoad;
	}

	else if (type == "ASSETAssign")
	{
		eventType = ASSETAssign;
	}

	else
	{
		cout << "ERROR, unknown Asset event type!" << endl;
	}
}
