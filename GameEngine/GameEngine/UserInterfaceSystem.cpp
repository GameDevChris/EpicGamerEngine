#include "UserInterfaceSystem.h"

void UserInterfaceSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	vector<std::string> textures;
	textures.clear();
	textures.push_back("./Models/Dragon/DragonTextureBlue.png");
	textures.push_back("./Models/Dragon/DragonTextureGreen.png");
	textures.push_back("./Models/Dragon/DragonTextureRed.png");
	AssetEvent* dragonAsset = new AssetEvent("ASSETLoad","./Models/Dragon/DragonModel.obj", &textures , 0, engineEventQueue);

	textures.clear();
	textures.push_back("./Models/Chris/ChrisTex.png");
	AssetEvent* chrisAsset = new AssetEvent("ASSETLoad", "./Models/Chris/ChrisModel.obj", &textures, 1, engineEventQueue);

}

void UserInterfaceSystem::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		GFXEvent* forwardCamEvent = new GFXEvent("GFXCamForward", engineEventQueue);
		//GFXEvent* upEvent = new GFXEvent("GFXUp", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		GFXEvent* backwardCamEvent = new GFXEvent("GFXCamBackward", engineEventQueue);
		//GFXEvent* downEvent = new GFXEvent("GFXDown", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		GFXEvent* leftCamEvent = new GFXEvent("GFXCamLeft", engineEventQueue);
		//GFXEvent* leftEvent = new GFXEvent("GFXLeft", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		GFXEvent* rightCamEvent = new GFXEvent("GFXCamRight", engineEventQueue);
		//GFXEvent* rightEvent = new GFXEvent("GFXRight", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//GFXEvent* leftCamEvent = new GFXEvent("GFXCamLeft", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//GFXEvent* rightCamEvent = new GFXEvent("GFXCamRight", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//GFXEvent* forwardCamEvent = new GFXEvent("GFXCamForward", engineEventQueue);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//GFXEvent* backwardCamEvent = new GFXEvent("GFXCamBackward", engineEventQueue);
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
				cout << "UI Event" << endl;

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
				cout << "Late UI Event" << endl;

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
	cout << "Can instantiate!" << endl;
}
