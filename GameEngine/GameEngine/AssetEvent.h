#pragma once
#include "Event.h"
class AssetEvent :
	public Event
{
public:
	AssetEvent(std::string type, std::string modelPath, std::string texturePath, int modelType, vector<Event*>* queue);
	AssetEvent(std::string type);
};

