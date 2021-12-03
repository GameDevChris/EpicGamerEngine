#pragma once
#include "SubSystem.h"

class NetworkSystem :
	public SubSystem
{
public:
	int scoreValue = 0;

	virtual void Start();
	virtual void Update();
	virtual void ProcessEvents();
	virtual void Exit();
};

