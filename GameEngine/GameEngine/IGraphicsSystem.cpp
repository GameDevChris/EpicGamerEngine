#include "IGraphicsSystem.h"

void IGraphicsSystem::StartIrrlicht()
{
	SIrrlichtCreationParameters IrrlichtParams;
	IrrlichtParams.DriverType = video::EDT_DIRECT3D9;
	IrrlichtParams.WindowSize = core::dimension2d<u32>(ScreenW, ScreenH);
	IrrlichtParams.Bits = 32;
	IrrlichtParams.Fullscreen = false;
	IrrlichtParams.Stencilbuffer = true;
	IrrlichtParams.AntiAlias = 16;
	IrrlichtParams.Vsync = false;

	IrrlichtParams.EventReceiver = &receiver;

	device = createDeviceEx(IrrlichtParams);

	if (device == NULL) 
	{
		cout << "Failed to create Irrlicht device!" << endl;
	}
	
	device->setWindowCaption(L"Epic Gamer Engine - Extra Gamer Edition");

	handle = createIMGUI(device, &receiver);

	smgr = device->getSceneManager();

	driver = device->getVideoDriver();

	guienv = device->getGUIEnvironment();


	const IGeometryCreator* geoCreator = smgr->getGeometryCreator();

	SMaterial* floorMat = new SMaterial();
	floorMat->DiffuseColor = SColor(u32(1), u32(0), u32(100), u32(0));
	IMesh* plane = geoCreator->createHillPlaneMesh(dimension2d<f32>(10, 10), dimension2d<u32>(100, 100), floorMat, 0, dimension2d<f32>(2, 2), dimension2d<f32>(1, 1));
	ISceneNode* ground = smgr->addMeshSceneNode(plane);
	//plane->setMaterialFlag(irr::video::EMF_LIGHTING, false);

}

void IGraphicsSystem::RunIrrlicht()
{
	if (device->run())
	{
		driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

		

		smgr->drawAll();

		DrawGUI();

		driver->endScene();
	}

	else 
	{
		Exit();
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

void IGraphicsSystem::AddCamera(float PosX, float PosY, float PosZ, float LookX, float LookY, float LookZ)
{
	cam = smgr->addCameraSceneNode(0, vector3df(PosX, PosY, PosZ), vector3df(LookX, LookY, LookZ));
}

void IGraphicsSystem::DrawGUI()
{
	handle->startGUI();

	if (IsFirstLoop1)
	{
		ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f));
		ImGui::SetNextWindowSize(ImVec2(400.0f, 100.0f));
		IsFirstLoop1 = false;
	}

	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_ShowBorders);

	ImGui::BeginGroup();

		ImGui::Text("Instantiation");
		ImGui::Text("-----");

		ImGui::Text("Which model?");
		ImGui::RadioButton("Dragon", &UIIDModelHolder, 0);
		ImGui::RadioButton("Chris", &UIIDModelHolder, 1);
		ImGui::Text("-----");

		if (UIIDModelHolder == 0)
		{
			ImGui::Text("Which texture?");
			ImGui::RadioButton("Blue", &UIIDTexHolder, 0);
			ImGui::RadioButton("Green", &UIIDTexHolder, 1);
			ImGui::RadioButton("Red", &UIIDTexHolder, 2);
			ImGui::Text("-----");
		}

		else
		{
			UIIDTexHolder = 0;
		}

		ImGui::Text("Position");

		ImGui::SliderFloat("X:##Pos", &UIPosHolder.x, -100, 100.0f);
		ImGui::SliderFloat("Y:##Pos", &UIPosHolder.y, -100, 100.0f);
		ImGui::SliderFloat("Z:##Pos", &UIPosHolder.z, -100, 100.0f);
		ImGui::Text("-----");

		ImGui::Text("Scale");

		ImGui::SliderFloat("GeneralScale", &UIGeneralScale, 0.1f, 10.0f);

		ImGui::SliderFloat("X:##Scale", &UIScaleHolder.x, 0.1f, 10.0f);
		ImGui::SliderFloat("Y:##Scale", &UIScaleHolder.y, 0.1f, 10.0f);
		ImGui::SliderFloat("Z:##Scale", &UIScaleHolder.z, 0.1f, 10.0f);

		UIScaleHolder.x = UIGeneralScale;
		UIScaleHolder.y = UIGeneralScale;
		UIScaleHolder.z = UIGeneralScale;

		ImGui::Text("-----");

		ImGui::Text("Rotation");

		ImGui::SliderFloat("X:##Rot", &UIRotHolder.x, -100, 100.0f);
		ImGui::SliderFloat("Y:##Rot", &UIRotHolder.y, -100, 100.0f);
		ImGui::SliderFloat("Z:##Rot", &UIRotHolder.z, -100, 100.0f);
		ImGui::Text("-----");


		if (ImGui::Button("Instantiate", ImVec2(100, 20)))
		{
			Event* instantiateEvent = new Event("InstantiateCustom", engineEventQueue, &UIIDModelHolder, &UIIDTexHolder, &UIPosHolder, &UIScaleHolder, &UIRotHolder);
		}

	ImGui::EndGroup();

	ImGui::SameLine(0.0f, 20.0f);

	ImGui::BeginGroup();
		ImGui::Text("Quit");
		if (ImGui::Button("Exit", ImVec2(40, 20)))
		{
			Exit();
		}
	ImGui::EndGroup();
	ImGui::End();


	if (IsFirstLoop2)
	{
		ImGui::SetNextWindowPos(ImVec2(1100.0f, 20.0f));
		ImGui::SetNextWindowSize(ImVec2(150.0f, 100.0f));
		IsFirstLoop2 = false;
	}
	ImGui::Begin("Info", NULL, ImGuiWindowFlags_ShowBorders);
	ImGui::BeginGroup();
	ImGui::Text("Amount of OBJs");
	ImGui::Text("-----");

	int amountInt = nodes.size();
	
	stringstream ss;
	ss << amountInt;
	std::string amountText;
	ss >> amountText;

	ImGui::Text(amountText.c_str());

	ImGui::Text("Quit");
	if (ImGui::Button("Exit", ImVec2(40, 20)))
	{
		Exit();
	}

	ImGui::EndGroup();
	ImGui::SameLine(0.0f, 20.0f);
	ImGui::End();

	handle->drawAll();
}

void IGraphicsSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	StartIrrlicht();

	WriteStaticText(L"This is comic sans, lmao", 0, 0, 1000, 100);

	AddCamera(0, 200, -200, 0, 0, 0);
}

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
					

						vector3d<f32>* edges = new core::vector3d<f32>[8];
						aabbox3d<f32> boundingbox = newNode->getTransformedBoundingBox();
						boundingbox.getEdges(edges);

						(*engineEventQueue)[i]->myData->targetObject->myModel->sizeX = (edges[5].X - edges[1].X) * (*engineEventQueue)[i]->myData->targetObject->Scale.x;
						std::cout << "width: " << (*engineEventQueue)[i]->myData->targetObject->myModel->sizeX << std::endl;

						(*engineEventQueue)[i]->myData->targetObject->myModel->sizeY = (edges[1].Y - edges[0].Y) * (*engineEventQueue)[i]->myData->targetObject->Scale.y;
						std::cout << "height: " << (*engineEventQueue)[i]->myData->targetObject->myModel->sizeY << std::endl;

						(*engineEventQueue)[i]->myData->targetObject->myModel->sizeZ = (edges[2].Z - edges[0].Z) * (*engineEventQueue)[i]->myData->targetObject->Scale.z;
						std::cout << "depth: " << (*engineEventQueue)[i]->myData->targetObject->myModel->sizeZ << std::endl;

						//vector3df extents =newNode->getTransformedBoundingBox().getExtent();
						//(*engineEventQueue)[i]->myData->targetObject->myModel->sizeX = extents.X;
						//std::cout << "sizeX: " << (*engineEventQueue)[i]->myData->targetObject->myModel->sizeX << std::endl;
						//
						//(*engineEventQueue)[i]->myData->targetObject->myModel->sizeX = extents.Y;
						//std::cout << "sizeY: " << (*engineEventQueue)[i]->myData->targetObject->myModel->sizeY << std::endl;
						//
						//(*engineEventQueue)[i]->myData->targetObject->myModel->sizeZ = extents.Z;
						//std::cout << "sizeZ: " << (*engineEventQueue)[i]->myData->targetObject->myModel->sizeZ << std::endl;

						(*engineEventQueue)[i]->myData->targetObject->myModel->myNode = newNode;
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
	device->closeDevice();

	handle->drop();
	device->drop();
	
	QuitCall = true;
}


