#pragma once
#include "Model.h"
struct EventData
{
public:
	std::string modPath = "confusion noises";
	std::string texPath = "";
	int modType = NULL;
	Model* myModel = NULL;

	EventData(){}
};