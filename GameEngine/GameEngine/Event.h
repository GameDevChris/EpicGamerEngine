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
	};

	enum EventType
	{
		GFXDefault,
		GFXQuit,
		GFXUp,
		GFXDown,
		GFXLeft,
		GFXRight,
		GFXUseModel,

		GFXCamUp,
		GFXCamDown,
		GFXCamLeft,
		GFXCamRight,
		GFXCamForward,
		GFXCamBackward,

		PHYSDefault,

		ASSETLoad,
		ASSETAssign
	};

	EventData* myData;
	vector<Event*>* EQueue;

	std::string ReturnSubsystem();

	Event(std::string type);
	Event();
	void Throw();

	SubsystemType eventSubsystem;
	EventType eventType;
};

