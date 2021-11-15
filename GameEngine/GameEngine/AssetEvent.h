#pragma once
#include "Event.h"
#include "GameObject.h"

class AssetEvent :
	public Event
{
public:
	AssetEvent(std::string type, std::string modelPath, std::string texturePath, int modelType, vector<Event*>* queue);
	AssetEvent(std::string type, GameObject* obj, int modelType, vector<Event*>* queue);
};

