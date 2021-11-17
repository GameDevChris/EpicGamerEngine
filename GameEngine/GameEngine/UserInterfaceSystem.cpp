#include "UserInterfaceSystem.h"

void UserInterfaceSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	//vector<std::string> textures;
	//textures.clear();
	//textures.push_back("./Models/Dragon/DragonTextureBlue.png");
	//textures.push_back("./Models/Dragon/DragonTextureGreen.png");
	//textures.push_back("./Models/Dragon/DragonTextureRed.png");
	//AssetEvent* dragonAsset = new AssetEvent("ASSETLoad","./Models/Dragon/DragonModel.obj", &textures , 0, engineEventQueue);
	//
	//textures.clear();
	//textures.push_back("./Models/Chris/ChrisTex.png");
	//AssetEvent* chrisAsset = new AssetEvent("ASSETLoad", "./Models/Chris/ChrisModel.obj", &textures, 1, engineEventQueue);

}

void UserInterfaceSystem::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		GFXEvent* upEvent = new GFXEvent("GFXUp", engineEventQueue);
		//upEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		GFXEvent* downEvent = new GFXEvent("GFXDown", engineEventQueue);
		//downEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		GFXEvent* leftEvent = new GFXEvent("GFXLeft", engineEventQueue);
		//leftEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		GFXEvent* rightEvent = new GFXEvent("GFXRight", engineEventQueue);
		//rightEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		GFXEvent* leftCamEvent = new GFXEvent("GFXCamLeft", engineEventQueue);
		//leftCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		GFXEvent* rightCamEvent = new GFXEvent("GFXCamRight", engineEventQueue);
		//rightCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		GFXEvent* forwardCamEvent = new GFXEvent("GFXCamForward", engineEventQueue);
		//forwardCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		GFXEvent* backwardCamEvent = new GFXEvent("GFXCamBackward", engineEventQueue);
		//backwardCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		GFXEvent* upCamEvent = new GFXEvent("GFXCamUp", engineEventQueue);
		//upCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		GFXEvent* downCamEvent = new GFXEvent("GFXCamDown", engineEventQueue);
		//downCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		GFXEvent* quitEvent = new GFXEvent("GFXQuit", engineEventQueue);
		//quitEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (canInstantiate)
		{
			Event* instantiateEvent = new Event("Instantiate", engineEventQueue);
		
			InputCooldown(canInstantiate, 1);
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		if (canInstantiate)
		{
			Event* chrisEvent = new Event("ChrisLegion", engineEventQueue);

			InputCooldown(canInstantiate, 1);
		}
	}


	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->UISub)
			{
				cout << "There is " << (*engineEventQueue).size() << " events!" << endl;

				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->CreateHandler)
				{
					cout << "UI Handler creation started" << endl;

					device = (*engineEventQueue)[i]->myData->myDevice;
					driver = (*engineEventQueue)[i]->myData->myDriver;
					smgr = (*engineEventQueue)[i]->myData->mySmgr;
					handle = createIMGUI(device, (*engineEventQueue)[i]->myData->myEventReceiver);
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->DrawUI)
				{
					cout << "UI drawn, should be workin" << endl;

					// create the GUI elements
					//handle->startGUI();
					//ImGui::Begin("My first Window");
					//ImGui::Text("Hello World!");

					//if (ImGui::Button("Exit", ImVec2(40, 20)))
					//{
					//	device->closeDevice();
					//}
					//ImGui::End();

					// render the GUI
					//handle->drawAll();
				}

				delete((*engineEventQueue)[i]);
				engineEventQueue->erase(engineEventQueue->begin() + i);
			}
		}
	}

}

void UserInterfaceSystem::LateUpdate()
{
	if (!(*lateEngineEventQueue).empty())
	{
		for (int i = 0; i < (*lateEngineEventQueue).size(); i++)
		{
			if ((*lateEngineEventQueue)[i]->eventSubsystem == (*lateEngineEventQueue)[i]->UISub)
			{
				if ((*lateEngineEventQueue)[i]->eventType == (*lateEngineEventQueue)[i]->DrawUI)
				{
					cout << "drawn ui innit" << endl;
				
					DrawGUI();
					driver->endScene();
				}
				
				delete((*lateEngineEventQueue)[i]);
				lateEngineEventQueue->erase(lateEngineEventQueue->begin() + i);
			}
		}
	}
}

void UserInterfaceSystem::DrawGUI()
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

void UserInterfaceSystem::InputCooldown(bool value, int cooldown)
{
	value = false;

	clock_t startTime = clock();
	clock_t cooldownTime = cooldown * CLOCKS_PER_SEC;
	clock_t elapsed = clock() - startTime;;

	while (elapsed < cooldownTime)
	{
		elapsed = clock() - startTime;
	}

	value = true;
	cout << "Can instantiate!" << endl;
}
