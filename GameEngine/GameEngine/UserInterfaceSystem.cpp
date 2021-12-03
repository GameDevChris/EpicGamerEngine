#include "UserInterfaceSystem.h"

void UserInterfaceSystem::Start()
{
	std::cout << "Subsystem " << name << " -started!" << std::endl;
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
			MyVec3* force = new MyVec3(-(subManager->PlayerLinearSpeed), 0, 0);
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
			MyVec3* force = new MyVec3(subManager->PlayerLinearSpeed, 0, 0);
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
			MyVec3* force = new MyVec3(0, 0, subManager->PlayerLinearSpeed);
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
			MyVec3* force = new MyVec3(0, 0, -(subManager->PlayerLinearSpeed));
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
				MyVec3* force = new MyVec3(0, subManager->PlayerJumpHeight, 0);
				PhysEvent* playerBackwardEvent = new PhysEvent("PlayerImpulse", engineEventQueue, myPlayer, force);

				myPlayer->isGrounded = false;
			}
			
			else
			{
				//std::cout << "Player isn't grounded!" << std::endl;
			}
		}

		else
		{
			//std::cout << "No Player Set!" << std::endl;
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
