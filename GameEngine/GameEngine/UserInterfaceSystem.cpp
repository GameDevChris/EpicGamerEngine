#include "UserInterfaceSystem.h"

void UserInterfaceSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	//AssetEvent dragonAsset("ASSETLoad","./Models/Dragon/DragonModel.obj", "./ Models/ Dragon/DragonTexture.png" , 0, engineEventQueue);
	

	//AssetEvent chrisAsset("ASSETLoad", "./Models/Chris/ChrisModel.obj", "./Models/Chris/ChrisTex.obj", 1);
	//engineEventQueue->push_back(&chrisAsset);

}

void UserInterfaceSystem::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		GFXEvent upEvent("GFXUp", engineEventQueue);
		//upEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		GFXEvent downEvent("GFXDown", engineEventQueue);
		//downEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		GFXEvent leftEvent("GFXLeft", engineEventQueue);
		//leftEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		GFXEvent rightEvent("GFXRight", engineEventQueue);
		//rightEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		GFXEvent leftCamEvent("GFXCamLeft", engineEventQueue);
		//leftCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		GFXEvent rightCamEvent("GFXCamRight", engineEventQueue);
		//rightCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		GFXEvent forwardCamEvent("GFXCamForward", engineEventQueue);
		//forwardCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		GFXEvent backwardCamEvent("GFXCamBackward", engineEventQueue);
		//backwardCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		GFXEvent upCamEvent("GFXCamUp", engineEventQueue);
		//upCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		GFXEvent downCamEvent("GFXCamDown", engineEventQueue);
		//downCamEvent.Throw();
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		GFXEvent quitEvent("GFXQuit", engineEventQueue);
		//quitEvent.Throw();
	}
}
