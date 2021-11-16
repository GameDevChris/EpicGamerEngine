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
