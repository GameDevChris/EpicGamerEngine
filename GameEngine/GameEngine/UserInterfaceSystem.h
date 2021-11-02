#pragma once
#include "SubSystem.h"
#include <SFML/Window/Keyboard.hpp>
class UserInterfaceSystem :
	public SubSystem
{
public:
	virtual void Start();
	virtual void Update();
};

