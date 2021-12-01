#pragma once
//#include "irrlicht.h"
#include "SubSystem.h"
#include "UIEvent.h"
#include "MyVec3.h"

#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>

#include <iostream>  

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace IrrIMGUI;

class IGraphicsSystem :
	public SubSystem
{
private:
	bool IsFirstLoop1 = true;

	bool IsFirstLoop2 = true;

	int ScreenW = 1280;
	int ScreenH = 720;

	IGUIEnvironment* guienv = NULL;
	vector3df BGColour = vector3df(46, 109, 114);

	std::vector<IAnimatedMeshSceneNode*> nodes;
	ICameraSceneNode* cam;

	void StartIrrlicht();
	
	void WriteStaticText(const wchar_t* text, int startPosX, int startPosY, int endPosX, int endPosY);
	void AddCamera(float PosX, float PosY, float PosZ, float LookX, float LookY, float LookZ);
	void DrawGUI();

	int UIScore = 0;

	int UIState = 0;

	int UIIDTexHolder;
	int UIIDModelHolder;
	int UIRBTypeHolder = 0;
	int UICollisionTypeHolder = 0;

	float UIGeneralScale = 0;
	MyVec3 UIPosHolder;
	MyVec3 UIRotHolder;
	MyVec3 UIScaleHolder;

public:

	std::vector<Model*> loadedModels;



	IrrlichtDevice* device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IIMGUIHandle* handle;
	CIMGUIEventReceiver receiver;

	void RunIrrlicht();
	bool QuitCall = false;
	virtual void Start();
	virtual void Update();
	virtual void Exit();
};


