#include "UserInterfaceSystem.h"

void UserInterfaceSystem::Start()
{
	cout << "Subsystem " << name << " -started!" << endl;

	AssetEvent* dragonAsset = new AssetEvent("ASSETLoad","./Models/Dragon/DragonModel.obj", "./Models/Dragon/DragonTexture.png" , 0, engineEventQueue);
	//AssetEvent* chrisAsset = new AssetEvent("ASSETLoad", "./Models/Chris/ChrisModel.obj", "./Models/Chris/ChrisTex.obj", 1, engineEventQueue);
	//engineEventQueue->push_back(&chrisAsset);

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
		Event* instantiateEvent = new Event("Instantiate", engineEventQueue);
	}
}
