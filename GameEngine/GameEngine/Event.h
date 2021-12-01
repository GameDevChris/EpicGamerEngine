#pragma once
#include "EventData.h"
//using namespace std;

class Event
{
public:
	enum SubsystemType
	{
		GraphicsSub,
		PhysicsSub,
		AssetSub,
		NetworkSub,
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
		PlayerMove,
		PlayerRotate,
		PlayerImpulse,

		//ASSET
		ASSETLoad,
		ASSETAssign,

		//GENERAL
		Instantiate,
		InstantiateCustom,
		InstantiatePlayer,
		ChrisLegion,

		//UI
		CreateHandler,
		DrawUI,

		//Network
		BotAddScore,
		BotPrintTop5
	};

	EventData* myData;
	std::vector<Event*>* EQueue;

	std::string ReturnSubsystem();
	std::string ReturnEvent();

	Event(std::string type);
	Event(std::string type, std::vector<Event*>* queue);

	Event(std::string type, std::vector<Event*>* queue, int* modelID, int* textureID,  MyVec3* position, MyVec3* scale, MyVec3* rotation);
	Event(std::string type, std::vector<Event*>* queue, int* modelID, int* textureID, std::string* rbType, std::string* colFilterType, MyVec3* position, MyVec3* scale, MyVec3* rotation);
	Event();

	void Throw();
	void Throw(EventType myType, Event* myEvent);

	SubsystemType eventSubsystem;
	EventType eventType;
};

