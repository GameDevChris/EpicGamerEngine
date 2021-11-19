#pragma once
#include "EventData.h"
using namespace std;

class Event
{
public:
	enum SubsystemType
	{
		GraphicsSub,
		PhysicsSub,
		AssetSub,
		UISub,
		General
	};

	enum EventType
	{
		//GFX
		GFXDefault,
		GFXQuit,
		GFXUp,
		GFXDown,
		GFXLeft,
		GFXRight,
		GFXSpawn,

		GFXCamUp,
		GFXCamDown,
		GFXCamLeft,
		GFXCamRight,
		GFXCamForward,
		GFXCamBackward,

		//PHYS
		PHYSDefault,
		PHYSSpawn,

		//ASSET
		ASSETLoad,
		ASSETAssign,

		//GENERAL
		Instantiate,
		InstantiateCustom,
		ChrisLegion,

		//UI
		CreateHandler,
		DrawUI
	};

	EventData* myData;
	vector<Event*>* EQueue;

	std::string ReturnSubsystem();
	std::string ReturnEvent();

	Event(std::string type);
	Event(std::string type, vector<Event*>* queue);

	Event(std::string type, vector<Event*>* queue, int* modelID, int* textureID, MyVec3* position, MyVec3* scale, MyVec3* rotation);
	Event();

	void Throw();
	void Throw(EventType myType, Event* myEvent);

	SubsystemType eventSubsystem;
	EventType eventType;
};

