#pragma once
#include <iostream>
#include "PhysicsSystem.h"
#include "IGraphicsSystem.h"
#include "DataInputSystem.h"
#include "UserInterfaceSystem.h"
#include "AssetManagerSystem.h"

using namespace std;
class Engine
{
private:
	PhysicsSystem physics;
	IGraphicsSystem graphics;
	DataInputSystem dataInput;
	UserInterfaceSystem UI;
	AssetManagerSystem assets;

	vector<Event*> eventQueue;


public:
	bool finished = false;
	Engine();
	void UseData();
	void ThrowEvent(Event newEvent);
	void Start();
	void Update();
};

