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
					ofstream score_file(scoreFilePath);

					//stringstream ss;
					//ss << *((*engineEventQueue)[i]->myData->myScore);
					//std::string scoreText;
					//ss >> scoreText;

					int score = (*engineEventQueue)[i]->myData->myScore;

					cout << score;
					score_file << score;
					
					score_file.close();



					ofstream job_file(jobFilePath);
					job_file << "newScore";
					job_file.close();

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
