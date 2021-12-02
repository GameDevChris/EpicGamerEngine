#include "UserInterfaceSystem.h"

void UserInterfaceSystem::Start()
{
	std::cout << "Subsystem " << name << " -started!" << std::endl;

	//std::vector<std::string> textures;
	//textures.clear();
	//textures.push_back("./Models/Dragon/DragonTextureBlue.png");
	//textures.push_back("./Models/Dragon/DragonTextureGreen.png");
	//textures.push_back("./Models/Dragon/DragonTextureRed.png");
	//AssetEvent* newAsset0 = new AssetEvent("ASSETLoad","./Models/Dragon/DragonModel.obj", &textures , 0, "Dragon", engineEventQueue);
	//
	//textures.clear();
	//textures.push_back("./Models/Chris/ChrisTex.png");
	//AssetEvent* newAsset1 = new AssetEvent("ASSETLoad", "./Models/Chris/ChrisModel.obj", &textures, 1, "Chris", engineEventQueue);
	//
	//textures.clear();
	//textures.push_back("./Models/Kermit/KermitTex.png");
	//AssetEvent* newAsset2 = new AssetEvent("ASSETLoad", "./Models/Kermit/KermitModel.obj", &textures, 2, "Kermit", engineEventQueue);
	//
	//textures.clear();
	//textures.push_back("./Models/Trump/TrumpTex.jpeg");
	//AssetEvent* newAsset3 = new AssetEvent("ASSETLoad", "./Models/Trump/TrumpModel.obj", &textures, 3, "Trump", engineEventQueue);
	//
	//textures.clear();
	//textures.push_back("./Models/Sword/SwordTex.png");
	//AssetEvent* newAsset4 = new AssetEvent("ASSETLoad", "./Models/Sword/SwordModel.obj", &textures, 4, "Sword", engineEventQueue);
	//
	//textures.clear();
	//textures.push_back("./Models/Floor/FloorTex.jpg");
	//AssetEvent* newAsset5 = new AssetEvent("ASSETLoad", "./Models/Floor/FloorModel.obj", &textures, 5, "Floor", engineEventQueue);
	//
	//textures.clear();
	//textures.push_back("./Models/Platform/PlatformTex.png");
	//AssetEvent* newAsset6 = new AssetEvent("ASSETLoad", "./Models/Platform/PlatformModel.obj", &textures, 6, "Platform", engineEventQueue);
	//
	//textures.clear();
	//textures.push_back("./Models/Hat/HatTex.png");
	//AssetEvent* newAsset7 = new AssetEvent("ASSETLoad", "./Models/Hat/HatModel.obj", &textures, 7, "Hat", engineEventQueue);
	//
	//textures.clear();
	//textures.push_back("./Models/Doge/dogeTex.jpg");
	//AssetEvent* newAsset8 = new AssetEvent("ASSETLoad", "./Models/Doge/dogeModel.obj", &textures, 8, "Doge", engineEventQueue);
}

void UserInterfaceSystem::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		GFXEvent* forwardCamEvent = new GFXEvent("GFXCamForward", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		GFXEvent* backwardCamEvent = new GFXEvent("GFXCamBackward", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		GFXEvent* leftCamEvent = new GFXEvent("GFXCamLeft", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		GFXEvent* rightCamEvent = new GFXEvent("GFXCamRight", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (myPlayer != NULL)
		{
			MyVec3* force = new MyVec3(-myPlayer->linearSpeed, 0, 0);
			PhysEvent* playerBackwardEvent = new PhysEvent("PlayerMove", engineEventQueue, myPlayer, force);
		}

		else
		{
			std::cout << "No Player Set!" << std::endl;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (myPlayer != NULL)
		{
			MyVec3* force = new MyVec3(myPlayer->linearSpeed, 0, 0);
			PhysEvent* playerBackwardEvent = new PhysEvent("PlayerMove", engineEventQueue, myPlayer, force);
		}

		else 
		{
			std::cout << "No Player Set!" << std::endl;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (myPlayer != NULL)
		{
			MyVec3* force = new MyVec3(0, 0, myPlayer->linearSpeed);
			PhysEvent* playerForwardEvent = new PhysEvent("PlayerMove", engineEventQueue, myPlayer, force);
		}

		else
		{
			std::cout << "No Player Set!" << std::endl;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (myPlayer != NULL)
		{
			MyVec3* force = new MyVec3(0, 0, -myPlayer->linearSpeed);
			PhysEvent* playerBackwardEvent = new PhysEvent("PlayerMove", engineEventQueue, myPlayer, force);
		}

		else
		{
			std::cout << "No Player Set!" << std::endl;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (myPlayer != NULL)
		{
			if (myPlayer->isGrounded)
			{
				MyVec3* force = new MyVec3(0, myPlayer->jumpHeight, 0);
				PhysEvent* playerBackwardEvent = new PhysEvent("PlayerImpulse", engineEventQueue, myPlayer, force);

				myPlayer->isGrounded = false;
			}
			
			else
			{
				std::cout << "Player isn't grounded!" << std::endl;
			}
		}

		else
		{
			std::cout << "No Player Set!" << std::endl;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		GFXEvent* upCamEvent = new GFXEvent("GFXCamUp", engineEventQueue);

	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		GFXEvent* downCamEvent = new GFXEvent("GFXCamDown", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		GFXEvent* quitEvent = new GFXEvent("GFXQuit", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
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
}

void UserInterfaceSystem::ProcessEvents()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->UISub)
			{
				delete((*engineEventQueue)[i]);
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
				delete((*lateEngineEventQueue)[i]);
				lateEngineEventQueue->erase(lateEngineEventQueue->begin() + i);
			}
		}
	}
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
	std::cout << "Can instantiate!" << std::endl;
}
