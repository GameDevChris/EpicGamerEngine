#pragma once
//#include "irrlicht.h"
#include "SubSystem.h"
#include "UIEvent.h"

#include <IrrIMGUI/IncludeIrrlicht.h>
#include <IrrIMGUI/IrrIMGUI.h>
#include <IrrIMGUI/IncludeIMGUI.h>
#include <IrrIMGUI/IrrIMGUIDebug.h>

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
	const int ScreenW = 1280;
	const int ScreenH = 720;

	IGUIEnvironment* guienv = NULL;
	vector3df BGColour = vector3df(46, 109, 114);

	vector<IAnimatedMeshSceneNode*> nodes;
	ICameraSceneNode* cam;

	void StartIrrlicht();
	
	void WriteStaticText(const wchar_t* text, int startPosX, int startPosY, int endPosX, int endPosY);
	void AddCamera(float PosX, float PosY, float PosZ, float LookX, float LookY, float LookZ);
	void DrawGUI();

public:
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


