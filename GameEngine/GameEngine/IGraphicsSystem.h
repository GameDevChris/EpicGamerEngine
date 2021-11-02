#pragma once
#include "irrlicht.h"
#include "SubSystem.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class IGraphicsSystem :
	public SubSystem
{
private:
	const int ScreenW = 1270;
	const int ScreenH = 720;

	IGUIEnvironment* guienv = NULL;
	vector3df BGColour = vector3df(46, 109, 114);

	vector<IAnimatedMeshSceneNode*> nodes;
	ICameraSceneNode* cam;

	void StartIrrlicht();
	
	void WriteStaticText(const wchar_t* text, int startPosX, int startPosY, int endPosX, int endPosY);
	void AddMesh(std::string modelPath, std::string texturePath, vector3df pos, vector3df scale, vector3df rot);
	void AddCamera(float PosX, float PosY, float PosZ, float LookX, float LookY, float LookZ);

public:
	IrrlichtDevice* device = NULL;
	IVideoDriver* driver = NULL;
	ISceneManager* smgr = NULL;

	void RunIrrlicht();
	bool QuitCall = false;
	virtual void Start();
	virtual void Update();
	virtual void Exit();
};


