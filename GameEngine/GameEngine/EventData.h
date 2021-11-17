#pragma once
#include "Model.h"
#include "GameObject.h"

#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>

struct EventData
{
public:
	std::string modPath = "confusion noises";
	std::string texPath = "";
	vector<std::string>* texPaths;

	int modType = NULL;
	Model* myModel = NULL;
	GameObject* targetObject = NULL;

	IrrlichtDevice* myDevice = NULL;
	video::IVideoDriver* myDriver = NULL;
	ISceneManager* mySmgr = NULL;
	IrrIMGUI::IIMGUIHandle* myHandle = NULL;
	IrrIMGUI::CIMGUIEventReceiver* myEventReceiver = NULL;


	EventData(){}
};