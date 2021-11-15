#pragma once
#include <iostream>
#include "PhysicsSystem.h"
#include "IGraphicsSystem.h"
#include "DataInputSystem.h"
#include "UserInterfaceSystem.h"
#include "AssetManagerSystem.h"
#include "GameObject.h"

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
	vector<GameObject*> objects;

public:
	bool finished = false;
	Engine();
	void UseData();
	void ThrowEvent(Event newEvent);
	void Start();
	void Update();

	void Instantiate(int ID, Vec3 position, Vec3 scale, Vec3 rotation);
};

