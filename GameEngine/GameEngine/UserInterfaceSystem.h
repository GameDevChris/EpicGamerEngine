#pragma once
#include "SubSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include "time.h"
#include "Player.h"

#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>


class UserInterfaceSystem :
	public SubSystem
{
private:
	bool canInstantiate = true;

public:
	Player* myPlayer = NULL;

	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();

	void InputCooldown(bool value, int cooldown);
};

