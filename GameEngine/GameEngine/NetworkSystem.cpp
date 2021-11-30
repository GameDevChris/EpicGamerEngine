#include "NetworkSystem.h"

void NetworkSystem::Start()
{
	//cout << "Subsystem " << name << " -started!" << endl;
	//
	//dpp::cluster epicGamerBot(botToken);
	//epicGamerBotPointer = &epicGamerBot;
	//
	//epicGamerBot.on_ready([&epicGamerBot](const dpp::ready_t& event) 
	//{
	//	cout << "Logged in as " << epicGamerBot.me.username << endl;
	//});
	//
	//epicGamerBot.on_message_create([&epicGamerBot](const dpp::message_create_t& event) 
	//{
	//	if (event.msg->content == "!ping") 
	//	{
	//		epicGamerBot.message_create(dpp::message(event.msg->channel_id, "Pong!"));
	//	}
	//});
	//
	//epicGamerBot.start(false);
}

void NetworkSystem::Update()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->NetworkSub)
			{
				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->BotAddScore)
				{
					std::ofstream score_file(scoreFilePath);
					
					int score = (*engineEventQueue)[i]->myData->myScore;
					score_file << score;
					score_file.close();
					
					std::ofstream job_file(jobFilePath);
					job_file << "printNewScore";
					job_file.close();

					ShellExecute(NULL, "open", "..\\..\\EngineBot.exe", NULL, NULL, SW_SHOWDEFAULT);
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->BotPrintTop5)
				{
					std::ofstream job_file(jobFilePath);
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
