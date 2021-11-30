#pragma once
#include <vector>
#include <fstream>
#include <windows.h>
//#include <dpp/dpp.h>

#include <thread>
#include "Event.h"
#include "GFXEvent.h"
#include "AssetEvent.h"
#include "PhysEvent.h"
#include "NetworkEvent.h"
#include "GameObject.h"
#include <sstream>  

//using namespace std;
class SubSystem
{
public:
	std::string name;
	void* data;

	SubSystem();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Exit();
	std::vector<Event*>* engineEventQueue;
	std::vector<Event*>* lateEngineEventQueue;
};

