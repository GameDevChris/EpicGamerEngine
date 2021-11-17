#pragma once
#include "SubSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include "time.h"

#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>

using namespace IrrIMGUI;

class UserInterfaceSystem :
	public SubSystem
{
private:
	bool canInstantiate = true;

public:

	IIMGUIHandle* handle;

	virtual void Start();
	virtual void Update();

	void InputCooldown(bool value, int cooldown);
};

