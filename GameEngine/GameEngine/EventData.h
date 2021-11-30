#pragma once
#include "Model.h"
#include "GameObject.h"
#include "Player.h"

#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>

struct EventData
{
public:
	std::string modPath = "confusion noises";
	std::string texPath = "";
	std::vector<std::string>* texPaths;

	std::string myName = "";
	int modType = NULL;
	std::string RBType = "";
	Model* myModel = NULL;
	GameObject* targetObject = NULL;
	Player* targetPlayer = NULL;

	MyVec3* myForce = NULL;



	IrrlichtDevice* myDevice = NULL;
	video::IVideoDriver* myDriver = NULL;
	ISceneManager* mySmgr = NULL;
	IrrIMGUI::IIMGUIHandle* myHandle = NULL;
	IrrIMGUI::CIMGUIEventReceiver* myEventReceiver = NULL;

	MyVec3* myPos = NULL;
	MyVec3* myRot = NULL;
	MyVec3* myScale = NULL;

	int* myTexID = NULL;
	int* myModID = NULL;

	int myScore = NULL;

	EventData(){}
};