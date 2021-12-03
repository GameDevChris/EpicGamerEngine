#include "SoundSystem.h"

void SoundSystem::Start()
{
	engine = irrklang::createIrrKlangDevice();
}

void SoundSystem::Update()
{
}

void SoundSystem::ProcessEvents()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->SoundSub)
			{
				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->PlayBGMusic)
				{
					engine->play2D(subManager->backgroundMusic.c_str(), true);
				}
					
				delete((*engineEventQueue)[i]);
				engineEventQueue->erase(engineEventQueue->begin() + i);
			}
		}
	}
}

void SoundSystem::Exit()
{
	engine->drop();
}



















































