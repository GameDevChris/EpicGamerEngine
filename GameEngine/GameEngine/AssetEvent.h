#pragma once
#include "Event.h"
#include "GameObject.h"

class AssetEvent :
	public Event
{
public:
	AssetEvent(std::string type, std::string modelPath, std::vector<std::string>* texturePaths, int modelType, std::string myName, std::vector<Event*>* queue);
};

