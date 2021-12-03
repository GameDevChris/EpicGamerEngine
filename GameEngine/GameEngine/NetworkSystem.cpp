#include "NetworkSystem.h"

void NetworkSystem::Start()
{

}

void NetworkSystem::Update()
{
	
}

void NetworkSystem::ProcessEvents()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->NetworkSub)
			{
				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->BotAddScore)
				{
					std::ofstream score_file(subManager->botScoreTextPath);

					int score = (*engineEventQueue)[i]->myData->myScore;
					score_file << score;
					score_file.close();

					std::ofstream job_file(subManager->botJobTextPath);
					job_file << "printNewScore";
					job_file.close();

					ShellExecute(NULL, "open", "..\\..\\EngineBot.exe", NULL, NULL, SW_SHOWDEFAULT);
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->BotPrintTop5)
				{
					std::ofstream job_file(subManager->botJobTextPath);
					job_file << "printTop5";
					job_file.close();

					ShellExecute(NULL, "open", "..\\..\\EngineBot.exe", NULL, NULL, SW_SHOWDEFAULT);
				}


				delete((*engineEventQueue)[i]);
				engineEventQueue->erase(engineEventQueue->begin() + i);
			}
		}
	}
}

void NetworkSystem::Exit()
{
}
