#pragma once
#include "SubSystem.h"
#include <SFML/Window/Keyboard.hpp>
#include "time.h"

#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>

using namespace IrrIMGUI;
using namespace scene;
using namespace video;

class UserInterfaceSystem :
	public SubSystem
{
private:
	bool canInstantiate = true;

public:

	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IIMGUIHandle* handle;

	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	void DrawGUI();

	void InputCooldown(bool value, int cooldown);
};

