#pragma once
#include <vector>
#include <fstream>
#include <thread>
#include "Event.h"
#include "GFXEvent.h"
#include "AssetEvent.h"

using namespace std;
class SubSystem
{
public:
	thread startThread()
	{
		return thread([=] {Start(); });
	};

	thread updateThread()
	{
		return thread([=] {Update(); });
	};

	std::string name;
	void* data;

	SubSystem();
	virtual void Start();
	virtual void Update();
	virtual void Exit();
	vector<Event*>* engineEventQueue;
};

