#include "IGraphicsSystem.h"

void IGraphicsSystem::StartIrrlicht()
{	
	//Grab all settings from game manager
	ScreenW = subManager->EngineWidth;
	ScreenH = subManager->EngineHeight;

	SIrrlichtCreationParameters IrrlichtParams;
	IrrlichtParams.DriverType = video::EDT_DIRECT3D9;
	IrrlichtParams.WindowSize = core::dimension2d<u32>(ScreenW, ScreenH);
	IrrlichtParams.Bits = subManager->BitPerPixel;
	IrrlichtParams.Fullscreen = subManager->Fullscreen;
	IrrlichtParams.Stencilbuffer = subManager->StencilBuffer;
	IrrlichtParams.AntiAlias = subManager->AntiAlias;
	IrrlichtParams.Vsync = subManager->VSync;

	IrrlichtParams.EventReceiver = &receiver;

	device = createDeviceEx(IrrlichtParams);

	if (device == NULL) 
	{
		std::cout << "Failed to create Irrlicht device!" << std::endl;
	}
	

	std::wstring widestr = std::wstring(subManager->EngineTitle.begin(), subManager->EngineTitle.end());
	const wchar_t* gameTitle = widestr.c_str();
	device->setWindowCaption(gameTitle);

	handle = createIMGUI(device, &receiver);

	smgr = device->getSceneManager();

	driver = device->getVideoDriver();

	guienv = device->getGUIEnvironment();


	WriteStaticText(gameTitle, 0, 0, 100, 100);

}

void IGraphicsSystem::SetColor(IAnimatedMeshSceneNode* target, MyVec3 targetColor)
{
	//Create a new texture with specific colour and apply
	video::ITexture* newTexture = driver->addTexture(dimension2du(1, 1), "customTexture", ECF_A8R8G8B8);
	s32* point = (s32*)newTexture->lock();

	point[0] = video::SColor(255, targetColor.x, targetColor.y, targetColor.z).color;

	newTexture->unlock();

	target->setMaterialTexture(0, driver->getTexture("customTexture"));
}

void IGraphicsSystem::RunIrrlicht()
{
	if (device->run())
	{
		irr::u32 r = subManager->BGColour.x;
		irr::u32 g = subManager->BGColour.y;
		irr::u32 b = subManager->BGColour.z;

		driver->beginScene(true, true, irr::video::SColor(255, r, g, b));

		//Draw square of target colour
		if (subManager->currentScene == subManager->Game)
		{
			driver->draw2DRectangle(irr::video::SColor(255, subManager->targetColor.x, subManager->targetColor.y, subManager->targetColor.z), irr::core::recti(vector2di(10, ScreenH / 4), vector2di(110, ScreenH / 4 + 100)), NULL);
		}
		
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
	//Write text using irrlicht GUI (deprecated)
	IGUISkin* skin = guienv->getSkin();
	IGUIFont* font = guienv->getFont("./Fonts/myfont.xml");

	skin->setFont(font);
	skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);

	guienv->addStaticText(text, rect<s32>(startPosX, startPosY, endPosX, endPosY), true);
}

void IGraphicsSystem::WriteTextCentered(std::string content)
{
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(content.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(content.c_str());
}

void IGraphicsSystem::AddCamera(float PosX, float PosY, float PosZ, float LookX, float LookY, float LookZ)
{
	cam = smgr->addCameraSceneNode(0, vector3df(PosX, PosY, PosZ), vector3df(LookX, LookY, LookZ));
}

void IGraphicsSystem::DrawGUI()
{
	handle->startGUI();

	//Change UI Based on current scene

	if (subManager->currentScene == subManager->Start)
	{
		if (StartFirstLoop)
		{
			ImGui::SetNextWindowPos(ImVec2(ScreenW/2 - 200, ScreenH / 2 - 200));
			ImGui::SetNextWindowSize(ImVec2(400.0f, 400.0f));
			StartFirstLoop = false;
		}

		ImGui::Begin("Start Screen", NULL, ImGuiWindowFlags_ShowBorders);

		ImGui::BeginGroup();

		WriteTextCentered("Welcome to the Epic Gamer Engine!");
		WriteTextCentered("-----");

		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = 100;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Editor", ImVec2(100, 50)))
		{
			subManager->currentScene = subManager->Editor;
		}

		windowWidth = ImGui::GetWindowSize().x;
		textWidth = 100;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Play", ImVec2(100, 50)))
		{
			subManager->levelStarted = false;
			subManager->currentScene = subManager->Game;
			Event* loadLevelEvent = new Event("LoadLevel", engineEventQueue, 1);
		}

		windowWidth = ImGui::GetWindowSize().x;
		textWidth = 100;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Join Discord", ImVec2(100, 20)))
		{
			NetworkEvent* inviteEvent = new NetworkEvent("DiscordInvite", 0, engineEventQueue);
		}

		windowWidth = ImGui::GetWindowSize().x;
		textWidth = 100;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Settings", ImVec2(100, 20)))
		{
			Event* openLuaEvent = new Event("OpenLuaFile", engineEventQueue);
		}

		windowWidth = ImGui::GetWindowSize().x;
		textWidth = 100;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Model File", ImVec2(100, 20)))
		{
			Event* openLuaEvent = new Event("OpenModelFile", engineEventQueue);
		}

		windowWidth = ImGui::GetWindowSize().x;
		textWidth = 100;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Layout File", ImVec2(100, 20)))
		{
			Event* openLuaEvent = new Event("OpenLayoutFile", engineEventQueue);
		}

		windowWidth = ImGui::GetWindowSize().x;
		textWidth = 100;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Sound File", ImVec2(100, 20)))
		{
			Event* openLuaEvent = new Event("OpenMusicFile", engineEventQueue);
		}

		windowWidth = ImGui::GetWindowSize().x;
		textWidth = 100;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Exit", ImVec2(100, 20)))
		{
			Exit();
		}

		ImGui::EndGroup();
		ImGui::End();
	}

	else if (subManager->currentScene == subManager->Editor)
	{
		if (UIState == 0)
		{
			if (IsFirstLoop1)
			{
				ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f));
				ImGui::SetNextWindowSize(ImVec2(400.0f, 100.0f));
				IsFirstLoop1 = false;
			}

			ImGui::Begin("Settings", NULL, ImGuiWindowFlags_ShowBorders);

			ImGui::BeginGroup();

			ImGui::Text("Model Instantiation");
			ImGui::Text("-----");

			if (!loadedModels.empty())
			{
				//Name
				ImGui::Text("Which model?");
				for (int i = 0; i < loadedModels.size(); i++)
				{
					ImGui::RadioButton(loadedModels[i]->modelName.c_str(), &UIIDModelHolder, i);
				}

				ImGui::Text("-----");

				//Texture

				ImGui::Text("Which texture?");

				for (int i = 0; i < loadedModels[UIIDModelHolder]->texturePaths->size(); i++)
				{
					std::string val = (*loadedModels[UIIDModelHolder]->texturePaths)[i];
					ImGui::RadioButton(val.c_str(), &UIIDTexHolder, i);
				}

				ImGui::Text("-----");

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

				ImGui::Text("Rigidbody type:");

				ImGui::RadioButton("Static", &UIRBTypeHolder, 0);
				ImGui::RadioButton("Dynamic", &UIRBTypeHolder, 1);

				ImGui::Text("-----");

				ImGui::Text("Colision Filter type:");

				ImGui::RadioButton("Ground", &UICollisionTypeHolder, 0);
				ImGui::RadioButton("Button", &UICollisionTypeHolder, 1);
				ImGui::RadioButton("Enemy", &UICollisionTypeHolder, 2);

				ImGui::Text("-----");

				if (ImGui::Button("Instantiate", ImVec2(100, 20)))
				{
					std::string rbVal = "";
					std::string colVal = "";

					//rbType
					if (UIRBTypeHolder == 0)
					{
						rbVal = "static";
					}

					else if (UIRBTypeHolder == 1)
					{
						rbVal = "dynamic";
					}

					//ColFilterType
					if (UICollisionTypeHolder == 0)
					{
						colVal = "Ground";
					}

					else if (UICollisionTypeHolder == 1)
					{
						colVal = "Button";
					}

					else if (UICollisionTypeHolder == 2)
					{
						colVal = "Enemy";
					}

					Event* instantiateEvent = new Event("InstantiateCustom", engineEventQueue, &UIIDModelHolder, &UIIDTexHolder, &rbVal, &colVal, &UIPosHolder, &UIScaleHolder, &UIRotHolder);
				}
			}

			else
			{
				ImGui::Text("No models loaded in memory");
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
		}

		else if (UIState == 1)
		{
			if (IsFirstLoop1)
			{
				ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f));
				ImGui::SetNextWindowSize(ImVec2(400.0f, 100.0f));
				IsFirstLoop1 = false;
			}

			ImGui::Begin("Settings", NULL, ImGuiWindowFlags_ShowBorders);

			ImGui::BeginGroup();

			ImGui::Text("Player Instantiation");
			ImGui::Text("-----");

			if (!loadedModels.empty())
			{
				//Name
				ImGui::Text("Which model?");
				for (int i = 0; i < loadedModels.size(); i++)
				{
					ImGui::RadioButton(loadedModels[i]->modelName.c_str(), &UIIDModelHolder, i);
				}

				ImGui::Text("-----");

				//Texture

				ImGui::Text("Which texture?");

				for (int i = 0; i < loadedModels[UIIDModelHolder]->texturePaths->size(); i++)
				{
					std::string val = (*loadedModels[UIIDModelHolder]->texturePaths)[i];
					ImGui::RadioButton(val.c_str(), &UIIDTexHolder, i);
				}

				ImGui::Text("-----");

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
					Event* instantiatePlayerEvent = new Event("InstantiatePlayer", engineEventQueue, &UIIDModelHolder, &UIIDTexHolder, &UIPosHolder, &UIScaleHolder, &UIRotHolder);
				}
			}

			else
			{
				ImGui::Text("No models loaded in memory");
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
		}

		if (IsFirstLoop2)
		{
			ImGui::SetNextWindowPos(ImVec2(1000.0f, 20.0f));
			ImGui::SetNextWindowSize(ImVec2(200.0f, 400.0f));
			IsFirstLoop2 = false;
		}
		ImGui::Begin("Info", NULL, ImGuiWindowFlags_ShowBorders);
		ImGui::BeginGroup();
		ImGui::Text("Amount of OBJs");
		ImGui::Text("-----");

		int amountInt = nodes.size();

		std::stringstream ss;
		ss << amountInt;
		std::string amountText;
		ss >> amountText;

		ImGui::Text(amountText.c_str());

		ImGui::Text("Menu option");
		ImGui::Text("-----");

		ImGui::RadioButton("Model Instantiation", &UIState, 0);
		ImGui::RadioButton("Player Instantiation", &UIState, 1);

		ImGui::Text("-----");

		ImGui::Text("Score");

		std::stringstream ss2;
		ss2 << UIScore;
		std::string scoreText;
		ss2 >> scoreText;

		ImGui::Text(scoreText.c_str());

		if (ImGui::Button("+", ImVec2(40, 20)))
		{
			UIScore++;
		}

		if (ImGui::Button("-", ImVec2(40, 20)))
		{
			UIScore--;
		}

		if (ImGui::Button("Add Score", ImVec2(60, 20)))
		{
			NetworkEvent* addScoreEvent = new NetworkEvent("BotAddScore", UIScore, engineEventQueue);
		}

		if (ImGui::Button("Print Top 5", ImVec2(60, 20)))
		{
			NetworkEvent* printScoreEvent = new NetworkEvent("BotPrintTop5", UIScore, engineEventQueue);
		}

		ImGui::Text("-----");

		ImGui::Text("CameraType:");

		ImGui::RadioButton("Free Cam", &UICamTypeHolder, 1);
		ImGui::RadioButton("3rd Person", &UICamTypeHolder, 0);

		subManager->FreeCamEnable = UICamTypeHolder;

		ImGui::Text("-----");

		if (ImGui::Button("Load Level", ImVec2(60, 20)))
		{
			subManager->levelStarted = false;
			subManager->currentScene = subManager->Game;
			Event* loadLevelEvent = new Event("LoadLevel", engineEventQueue, 1);
		}

		ImGui::Text("-----");
		ImGui::Text("Clear Scene");
		if (ImGui::Button("Reset", ImVec2(40, 20)))
		{
			Event* deleteEvent = new Event("DeleteAll", engineEventQueue);
		}


		ImGui::Text("-----");
		ImGui::Text("Quit");
		if (ImGui::Button("Exit", ImVec2(40, 20)))
		{
			Exit();
		}

		ImGui::EndGroup();
		ImGui::SameLine(0.0f, 20.0f);
		ImGui::End();
	}

	else if (subManager->currentScene == subManager->Game)
	{
		if (GameFirstLoop)
		{
			ImGui::SetNextWindowPos(ImVec2(1000.0f, 20.0f));
			ImGui::SetNextWindowSize(ImVec2(200.0f, 400.0f));
			GameFirstLoop = false;
		}
		ImGui::Begin("Info", NULL, ImGuiWindowFlags_ShowBorders);
		ImGui::BeginGroup();
		ImGui::Text("Amount of OBJs");
		ImGui::Text("-----");

		int amountInt = nodes.size();

		std::stringstream ss;
		ss << amountInt;
		std::string amountText;
		ss >> amountText;

		ImGui::Text(amountText.c_str());

		ImGui::Text("-----");

		ImGui::Text("FPS");

		int fps = driver->getFPS();
		std::stringstream fpsss;
		fpsss << fps;
		std::string fpsText;
		fpsss >> fpsText;

		ImGui::Text(fpsText.c_str());

		ImGui::Text("-----");

		ImGui::Text("Score");

		UIScore = subManager->score;

		std::stringstream ss2;
		ss2 << UIScore;
		std::string scoreText;
		ss2 >> scoreText;

		ImGui::Text(scoreText.c_str());

		ImGui::Text("-----");

		ImGui::Text("Share to discord:");

		if (ImGui::Button("Post Score", ImVec2(100, 20)))
		{
			NetworkEvent* addScoreEvent = new NetworkEvent("BotAddScore", UIScore, engineEventQueue);
		}

		if (ImGui::Button("Print Top 5", ImVec2(100, 20)))
		{
			NetworkEvent* printScoreEvent = new NetworkEvent("BotPrintTop5", UIScore, engineEventQueue);
		}

		ImGui::Text("-----");

		ImGui::Text("CameraType:");

		ImGui::RadioButton("Free Cam", &UICamTypeHolder, 1);
		ImGui::RadioButton("3rd Person", &UICamTypeHolder, 0);

		subManager->FreeCamEnable = UICamTypeHolder;

		ImGui::Text("-----");

		ImGui::Text("Clear Scene");
		if (ImGui::Button("Reset", ImVec2(40, 20)))
		{
			Event* deleteEvent = new Event("DeleteAll", engineEventQueue);
			subManager->currentScene = subManager->Start;
		}


		ImGui::Text("-----");
		ImGui::Text("Quit");
		if (ImGui::Button("Exit", ImVec2(40, 20)))
		{
			Exit();
		}

		ImGui::EndGroup();
		ImGui::SameLine(0.0f, 20.0f);
		ImGui::End();

	}

	else if (subManager->currentScene == subManager->End)
	{
		if (EndFirstLoop)
		{
			ImGui::SetNextWindowPos(ImVec2(ScreenW/2 - 200, ScreenH / 2 - 200));
			ImGui::SetNextWindowSize(ImVec2(400.0f, 400.0f));
			EndFirstLoop = false;
		}

		ImGui::Begin("End Screen", NULL, ImGuiWindowFlags_ShowBorders);

		ImGui::BeginGroup();

		WriteTextCentered("Game Over! Well done!");
		WriteTextCentered("-----");

		WriteTextCentered("Final Score");

		std::stringstream ss2;
		ss2 << UIScore;
		std::string scoreText;
		ss2 >> scoreText;

		WriteTextCentered(scoreText);

		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = 200;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Share to discord", ImVec2(200, 50)))
		{
			NetworkEvent* addScoreEvent = new NetworkEvent("BotAddScore", UIScore, engineEventQueue);
		}

		windowWidth = ImGui::GetWindowSize().x;
		textWidth = 200;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Return to Start", ImVec2(200, 50)))
		{
			subManager->currentScene = subManager->Start;
		}

		windowWidth = ImGui::GetWindowSize().x;
		textWidth = 200;
		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

		if (ImGui::Button("Quit", ImVec2(200, 50)))
		{
			Exit();
		}

		ImGui::EndGroup();
		ImGui::End();
	}

	handle->drawAll();
}

void IGraphicsSystem::Start()
{
	loadedModels.clear();
	std::cout << "Subsystem " << name << " -started!" << std::endl;

	StartIrrlicht();

	AddCamera(0, 200, -200, 0, 0, 0);
}

void IGraphicsSystem::Update()
{
	if (myPlayer != NULL && !subManager->FreeCamEnable) 
	{
		vector3df offset(0, 200, -200);
		cam->setPosition(myPlayer->myModel->myNode->getAbsolutePosition() + offset);
		cam->setTarget(myPlayer->myModel->myNode->getAbsolutePosition());
	}
	
	if (subManager->currentScene == subManager->Game)
	{
		UIScore = subManager->score;
	}

	RunIrrlicht();
}

void IGraphicsSystem::ProcessEvents()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->GraphicsSub)
			{
				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXDefault)
				{
					std::cout << "Default GFX event happened" << std::endl;
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXUp)
				{
					for (i = 0; i < nodes.size(); i++)
					{
						vector3df originalRot = nodes[i]->getRotation();
						nodes[i]->setRotation(vector3df(originalRot.X - 1, originalRot.Y, originalRot.Z));
					}
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXDown)
				{
					for (i = 0; i < nodes.size(); i++)
					{
						vector3df originalRot = nodes[i]->getRotation();
						nodes[i]->setRotation(vector3df(originalRot.X + 1, originalRot.Y, originalRot.Z));
					}
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXLeft)
				{
					for (i = 0; i < nodes.size(); i++)
					{
						vector3df originalRot = nodes[i]->getRotation();
						nodes[i]->setRotation(vector3df(originalRot.X, originalRot.Y, originalRot.Z + 1));
					}
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXRight)
				{
					for (i = 0; i < nodes.size(); i++)
					{
						vector3df originalRot = nodes[i]->getRotation();
						nodes[i]->setRotation(vector3df(originalRot.X, originalRot.Y, originalRot.Z - 1));
					}
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamUp)
				{
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X, originalPos.Y + 1, originalPos.Z));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamDown)
				{
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X, originalPos.Y - 1, originalPos.Z));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamRight)
				{
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X + 1, originalPos.Y, originalPos.Z));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamLeft)
				{
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X - 1, originalPos.Y, originalPos.Z));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamForward)
				{
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X, originalPos.Y, originalPos.Z + 1));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXCamBackward)
				{
					vector3df originalPos = cam->getPosition();
					cam->setPosition(vector3df(originalPos.X, originalPos.Y, originalPos.Z - 1));
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXQuit)
				{
					QuitCall = true;
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->GFXSpawn)
				{

					std::cout << "Spawning..." << std::endl;


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

						if ((*engineEventQueue)[i]->myData->targetObject->myModel->type == subManager->buttonID)
						{
							(*engineEventQueue)[i]->myData->targetObject->myModel->myColour = subManager->AssignColour();
							SetColor(newNode, (*engineEventQueue)[i]->myData->targetObject->myModel->myColour);
						}
						

						vector3d<f32>* edges = new core::vector3d<f32>[8];
						aabbox3d<f32> boundingbox = newNode->getTransformedBoundingBox();
						boundingbox.getEdges(edges);

						(*engineEventQueue)[i]->myData->targetObject->myModel->sizeX = (edges[5].X - edges[1].X) * (*engineEventQueue)[i]->myData->targetObject->Scale.x;

						(*engineEventQueue)[i]->myData->targetObject->myModel->sizeX /= 3;

						(*engineEventQueue)[i]->myData->targetObject->myModel->sizeY = (edges[1].Y - edges[0].Y) * (*engineEventQueue)[i]->myData->targetObject->Scale.y;

						(*engineEventQueue)[i]->myData->targetObject->myModel->sizeY /= 4;

						(*engineEventQueue)[i]->myData->targetObject->myModel->sizeZ = (edges[2].Z - edges[0].Z) * (*engineEventQueue)[i]->myData->targetObject->Scale.z;

						(*engineEventQueue)[i]->myData->targetObject->myModel->sizeZ /= 3;


						(*engineEventQueue)[i]->myData->targetObject->myModel->myNode = newNode;
						nodes.push_back(newNode);
					}
				}

				else
				{
					std::cout << "ERROR! Unrecognised Graphics event" << std::endl;
				}

				delete((*engineEventQueue)[i]);
				engineEventQueue->erase(engineEventQueue->begin() + i);
			}

		}
	}
}

void IGraphicsSystem::Exit()
{
	device->closeDevice();

	handle->drop();
	device->drop();
	
	QuitCall = true;
}


