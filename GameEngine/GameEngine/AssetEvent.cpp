#include "AssetEvent.h"

AssetEvent::AssetEvent(std::string type, std::string modelPath, vector<std::string>* texturePaths, int modelType, std::string myName, vector<Event*>* queue)
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
	myData->myName = myName;
	myData->texPaths = new vector<std::string>;
	myData->texPaths->clear();

	for (int i = 0; i < texturePaths->size(); i++)
	{
		myData->texPaths->push_back((*texturePaths)[i]);
	}

	myData->modType = modelType;

	EQueue = queue;

	Throw();
}
