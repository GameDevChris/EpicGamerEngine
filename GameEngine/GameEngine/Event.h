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
		General
	};

	enum EventType
	{
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

		PHYSDefault,

		ASSETLoad,
		ASSETAssign,

		Instantiate,
		ChrisLegion
	};

	EventData* myData;
	vector<Event*>* EQueue;

	std::string ReturnSubsystem();
	std::string ReturnEvent();

	Event(std::string type);
	Event(std::string type, vector<Event*>* queue);
	Event();

	void Throw();
	void Throw(EventType myType, Event* myEvent);

	SubsystemType eventSubsystem;
	EventType eventType;
};

