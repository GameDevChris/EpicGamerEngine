#pragma once
#include <iostream>
#include "PhysicsSystem.h"
#include "IGraphicsSystem.h"
#include "DataInputSystem.h"
#include "UserInterfaceSystem.h"
#include "AssetManagerSystem.h"
#include "NetworkSystem.h"
#include "GameObject.h"
#include "PhysEvent.h"
#include "EpicGameManager.h"
#include "time.h"
#include <random>

//using namespace std;
class Engine
{
private:
	PhysicsSystem physics;
	IGraphicsSystem graphics;
	DataInputSystem dataInput;
	UserInterfaceSystem UI;
	AssetManagerSystem assets;
	NetworkSystem network;

	std::vector<Event*> eventQueue;
	std::vector<Event*> lateEventQueue;
	std::vector<GameObject*> objects;

	void InstantiateTimer(int cooldown, std::vector<SpawnData*> spawnData, int index);
	void ProcessEngineEvent();
	void ProcessSubsystemEvents();

public:
	EpicGameManager* mainManager = NULL;
	bool finished = false;
	Engine();
	void UseData();
	void ThrowEvent(Event newEvent);
	void Start();
	void Update();

	void InstantiateRandom();
	void Instantiate(int modelID, int textureID, MyVec3 position, MyVec3 scale, MyVec3 rotation, std::string rbType, std::string cfType);

	void InstantiatePlayer(int modelID, int textureID, MyVec3 position, MyVec3 scale, MyVec3 rotation);

	void InstantiateRequest();

	void LoadLevel(int number);
};

