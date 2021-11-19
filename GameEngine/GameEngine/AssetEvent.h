#pragma once
#include "Event.h"
#include "GameObject.h"

class AssetEvent :
	public Event
{
public:
	AssetEvent(std::string type, std::string modelPath, vector<std::string>* texturePaths, int modelType, std::string myName, vector<Event*>* queue);
};

