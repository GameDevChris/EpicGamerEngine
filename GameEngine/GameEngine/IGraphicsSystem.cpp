#include "IGraphicsSystem.h"

void IGraphicsSystem::StartIrrlicht()
{
	// Irrlicht OpenGL Settings
	SIrrlichtCreationParameters IrrlichtParams;
	IrrlichtParams.DriverType = video::EDT_DIRECT3D9;
	IrrlichtParams.WindowSize = core::dimension2d<u32>(ScreenW, ScreenH);
	IrrlichtParams.Bits = 32;
	IrrlichtParams.Fullscreen = false;
	IrrlichtParams.Stencilbuffer = true;
	IrrlichtParams.AntiAlias = 16;
	IrrlichtParams.Vsync = false;

	// Create standard event receiver for the IrrIMGUI
	IrrlichtParams.EventReceiver = receiver;

	device = createDeviceEx(IrrlichtParams);

	if (device == NULL) 
	{
		cout << "Failed to create Irrlicht device!" << endl;
	}
	
	device->setWindowCaption(L"Epic Gamer Engine - Extra Gamer Edition");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	//guienv = device->getGUIEnvironment();

	handle = createIMGUI(device, receiver);
	//UIEvent* sendData = new UIEvent("CreateHandler", engineEventQueue, device, driver, smgr, receiver);
	
}

void IGraphicsSystem::RunIrrlicht()
{
	if (device->run())
	{
		driver->beginScene(true, true, SColor(255, BGColour.X, BGColour.Y, BGColour.Z));
		smgr->drawAll();
		//guienv->drawAll();
		DrawGUI();
		

		driver->endScene();
	}
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

void IGraphicsSystem::DrawGUI()
{
	handle->startGUI();
	ImGui::Begin("My first Window");
	ImGui::Text("Hello World!");

	if (ImGui::Button("Exit", ImVec2(40, 20)))
	{
		device->closeDevice();
	}
	ImGui::End();

	smgr->drawAll();
	handle->drawAll();
}

void IGraphicsSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	StartIrrlicht();

	//WriteStaticText(L"This is comic sans, lmao", 0, 0, 1000, 100);

	//AddMesh("./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTextureRed.png", vector3df(-60, 15, 0), vector3df(7, 7, 7), vector3df(0, 0, 0));
	

	AddCamera(0, 10, -50, 0, 5, 0);
}
//Le graphics pour baggette
void IGraphicsSystem::Update()
{
	if (!(*engineEventQueue).empty())
	{
		cout << "There are " << (*engineEventQueue).size() << " events" << endl;
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->GraphicsSub)
			{
				cout << endl;
				cout << "GFX Event found" << endl;
				cout << "Event found: "<< (*engineEventQueue)[i]->ReturnEvent() << endl;

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

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXSpawn)
				{

					cout << "Spawning..." << endl;


					//Le code
					IAnimatedMeshSceneNode* newNode = smgr->addAnimatedMeshSceneNode((*engineEventQueue)[i]->myData->targetObject->myModel->mesh);

					//Une function de newNode	
					if (newNode)
					{
						newNode->setPosition(vector3df((*engineEventQueue)[i]->myData->targetObject->Position.x,
							(*engineEventQueue)[i]->myData->targetObject->Position.y,
							(*engineEventQueue)[i]->myData->targetObject->Position.z));
					
						newNode->setScale(vector3df((*engineEventQueue)[i]->myData->targetObject->Scale.x,
							(*engineEventQueue)[i]->myData->targetObject->Scale.y,
							(*engineEventQueue)[i]->myData->targetObject->Scale.z));
					
						newNode->setRotation(vector3df((*engineEventQueue)[i]->myData->targetObject->Rotation.x,
							(*engineEventQueue)[i]->myData->targetObject->Rotation.y,
							(*engineEventQueue)[i]->myData->targetObject->Rotation.z));
					
						newNode->setMaterialFlag(EMF_LIGHTING, false);
						newNode->setMaterialTexture(0, driver->getTexture((*engineEventQueue)[i]->myData->targetObject->myModel->texturePath.c_str()));
					
						nodes.push_back(newNode);
					}			
				}

				else
				{
					cout << "ERROR! Unrecognised Graphics event" << endl;
				}

				delete((*engineEventQueue)[i]);
				engineEventQueue->erase(engineEventQueue->begin() + i);
			}
			
		}
	}

	RunIrrlicht();
}

void IGraphicsSystem::Exit()
{
	device->drop();
}


