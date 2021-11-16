#pragma once
#include "Model.h"
#include "GameObject.h"

struct EventData
{
public:
	std::string modPath = "confusion noises";
	std::string texPath = "";
	vector<std::string>* texPaths;

	int modType = NULL;
	Model* myModel = NULL;
	GameObject* targetObject = NULL;

	EventData(){}
};