#include "IGraphicsSystem.h"

void IGraphicsSystem::StartIrrlicht()
{
	device = createDevice(video::EDT_DIRECT3D9, core::dimension2d<u32>(ScreenW, ScreenH), 32, false, true, true, 0);

	if (device == NULL) 
	{
		cout << "Failed to create Irrlicht device!" << endl;
	}

	device->setWindowCaption(L"Epic Gamer Engine - Extra Gamer Edition");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
}

void IGraphicsSystem::RunIrrlicht()
{
	driver->beginScene(true, true, SColor(255, BGColour.X, BGColour.Y, BGColour.Z));
	smgr->drawAll();
	guienv->drawAll();
	driver->endScene();
}

void IGraphicsSystem::WriteStaticText(const wchar_t* text, int startPosX, int startPosY, int endPosX, int endPosY)
{
	IGUISkin* skin = guienv->getSkin();
	IGUIFont* font = guienv->getFont("./Fonts/myfont.xml");

	skin->setFont(font);
	skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);

	guienv->addStaticText(text, rect<s32>(startPosX, startPosY, endPosX, endPosY), true);
}

void IGraphicsSystem::AddMesh(std::string modelPath, std::string texturePath, vector3df pos, vector3df scale, vector3df rot)
{
	IAnimatedMesh* mesh = smgr->getMesh(modelPath.c_str());
	if (!mesh) 
	{
		device->drop();
		cout << "Failed to load mesh" << endl;
	}

	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

	if (node)
	{
		node->setPosition(pos);
		node->setScale(scale);
		node->setRotation(rot);
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialTexture(0, driver->getTexture(texturePath.c_str()));
	
		nodes.push_back(node);
	}
}

void IGraphicsSystem::AddCamera(float PosX, float PosY, float PosZ, float LookX, float LookY, float LookZ)
{
	cam = smgr->addCameraSceneNode(0, vector3df(PosX, PosY, PosZ), vector3df(LookX, LookY, LookZ));
}

void IGraphicsSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	StartIrrlicht();

	WriteStaticText(L"This is comic sans, lmao", 0, 0, 1000, 100);

	/*
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureRed.png", vector3df(-60, 15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureRed.png", vector3df(-40, 15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureRed.png", vector3df(-20, 15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureRed.png", vector3df(0, 15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureRed.png", vector3df(20, 15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureRed.png", vector3df(40, 15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureRed.png", vector3df(60, 15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureGreen.png", vector3df(-60, 0, 0), vector3df(7, 7, 7), vector3df(0,0,0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureGreen.png", vector3df(-40, 0, 0), vector3df(7, 7, 7), vector3df(0,0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureGreen.png", vector3df(-20, 0, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));

	AddMesh("./Models/Chris/ChrisModel.obj", "./Models/Chris/ChrisTex.png", vector3df(0, 0, 0), vector3df(0.05, 0.05, 0.05), vector3df(0, 0, 0));

	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureGreen.png", vector3df(20, 0, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureGreen.png", vector3df(40, 0, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureGreen.png", vector3df(60, 0, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));

	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTexture.png", vector3df(-60, -15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTexture.png", vector3df(-40, -15, 0), vector3df(7,7,7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTexture.png", vector3df(-20, -15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTexture.png", vector3df(0, -15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTexture.png", vector3df(20, -15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTexture.png", vector3df(40, -15, 0), vector3df(7,7,7), vector3df(0, 0, 0));
	AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTexture.png", vector3df(60, -15, 0), vector3df(7,7,7), vector3df(0, 0, 0));
	
	*/

	AddCamera(0, 10, -50, 0, 5, 0);
}

void IGraphicsSystem::Update()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem== (*engineEventQueue)[i]->GraphicsSub)
			{
				cout << "GFX Event found" << endl;
				cout << (*engineEventQueue)[i]->ReturnEvent() << endl;

				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXDefault)
				{
					cout << "Default GFX event happened" << endl;
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXUp)
				{
					cout << "Up GFX event happened" << endl;
					for (i = 0; i < nodes.size(); i++)
					{
						vector3df originalRot = nodes[i]->getRotation();
						nodes[i]->setRotation(vector3df(originalRot.X - 1, originalRot.Y, originalRot.Z));
					}
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXDown)
				{
					cout << "Down GFX event happened" << endl;
					for (i = 0; i < nodes.size(); i++)
					{
						vector3df originalRot = nodes[i]->getRotation();
						nodes[i]->setRotation(vector3df(originalRot.X + 1, originalRot.Y, originalRot.Z));
					}
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXLeft)
				{
					cout << "Left GFX event happened" << endl;
					for (i = 0; i < nodes.size(); i++)
					{
						vector3df originalRot = nodes[i]->getRotation();
						nodes[i]->setRotation(vector3df(originalRot.X, originalRot.Y, originalRot.Z + 1));
					}
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXRight)
				{
					cout << "Right GFX event happened" << endl;
					for (i = 0; i < nodes.size(); i++)
					{
						vector3df originalRot = nodes[i]->getRotation();
						nodes[i]->setRotation(vector3df(originalRot.X, originalRot.Y, originalRot.Z - 1));
					}
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamUp)
				{
					cout << "Up GFX Camera event happened" << endl;
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X, originalPos.Y + 1, originalPos.Z));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamDown)
				{
					cout << "Down GFX Camera event happened" << endl;
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X, originalPos.Y - 1, originalPos.Z));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamRight)
				{
					cout << "Right GFX Camera event happened" << endl;
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X + 1, originalPos.Y, originalPos.Z));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamLeft)
				{
					cout << "Left GFX Camera event happened" << endl;
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X - 1, originalPos.Y, originalPos.Z));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamForward)
				{
					cout << "Forward GFX Camera event happened" << endl;
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X, originalPos.Y, originalPos.Z + 1));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamBackward)
				{
					cout << "Backward GFX Camera event happened" << endl;
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X, originalPos.Y, originalPos.Z - 1));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXQuit)
				{
					QuitCall = true;
				}

				else
				{
					cout << "ERROR! Unrecognised Graphics event" << endl;
				}
			}
			
		}
	}

	RunIrrlicht();
}

void IGraphicsSystem::Exit()
{
	device->drop();
}


