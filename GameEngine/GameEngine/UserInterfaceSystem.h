#pragma once
#include "SubSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include "time.h"

class UserInterfaceSystem :
	public SubSystem
{
private:
	bool canInstantiate = true;

public:
	virtual void Start();
	virtual void Update();

	void InputCooldown(bool value, int cooldown);
};

