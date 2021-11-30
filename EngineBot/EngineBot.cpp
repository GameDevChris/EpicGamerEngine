#include <dpp/dpp.h>
#include <iostream>  
#include <sstream>  
#include <vector>
#include <stdlib.h>

using namespace std;

dpp::snowflake* leaderboardChannel = new dpp::snowflake(uint64_t(912656966487269406));
dpp::snowflake* newScoreChannel = new dpp::snowflake(uint64_t(912657008027648020));

void GetScores(dpp::cluster* bot)
{
	dpp::snowflake after = 0;
	dpp::snowflake channel = *newScoreChannel;
	std::function<void(dpp::confirmation_callback_t)> f = [channel, after, &bot](const dpp::confirmation_callback_t& cc)
	{
		string filename("./scoreData.txt");
		ofstream score_file(filename);

		if (!cc.is_error())
		{
			dpp::message_map um = std::get<dpp::message_map>(cc.value);

			for (auto& m : um)
			{
				std::cout << "MESSAGE FOUND: " << m.second.id << ", " << m.second.content << std::endl;
				
				stringstream ss;
				ss << m.second.content;
				std::string messageText;
				ss >> messageText;

				score_file << messageText << " ";
			}
		}

		score_file.close();
		exit(0);
	};

	bot->messages_get(channel, 0, 0, after, 100, f);

}

void Print5Scores(dpp::cluster* bot)
{
	vector<int>* dataVector = new vector<int>;
	dataVector->clear();

	string filename("./scoreData.txt");
	int number;
	ifstream input_file(filename);

	while (input_file >> number) {
		dataVector->push_back(number);
	}

	cout << endl;
	input_file.close();

	sort(dataVector->begin(), dataVector->end(), greater<int>());

	bot->message_create(dpp::message(*leaderboardChannel, "-----"));
	bot->message_create(dpp::message(*leaderboardChannel, "Top 5 Scores:"));
	bot->message_create(dpp::message(*leaderboardChannel, "-----"));

	for (int i = 0; i < 5; i++)
	{
		int val = (*dataVector)[i];
		stringstream ss;

		ss << val;
		std::string scoreText;
		ss >> scoreText;


		bot->message_create(dpp::message(*leaderboardChannel, scoreText));
	}

	GetScores(bot);
}

void PrintNewScore(dpp::cluster* bot)
{
	vector<int>* dataVector = new vector<int>;
	dataVector->clear();

	string filename("./scoreData.txt");
	int number;
	ifstream input_file(filename);

	while (input_file >> number) {
		dataVector->push_back(number);
	}

	cout << endl;
	input_file.close();

	int val = (*dataVector)[dataVector->size()-1];
	stringstream ss;

	ss << val;
	std::string scoreText;
	ss >> scoreText;

	bot->message_create(dpp::message(*newScoreChannel, scoreText));

	GetScores(bot);
}


std::string GetJob()
{
	std::string job = "";

	string filename("./jobData.txt");

	ifstream input_file(filename);

	if (input_file >> job)
	{
		return job;
		input_file.close();
	}

	else
	{
		return "";
		input_file.close();
	}
}

void doJob(dpp::cluster* bot)
{
	std::string myJob = GetJob();

	if (myJob == "printNewScore")
	{
		cout << "Printing new score" << endl;
		PrintNewScore(bot);
	}

	else if (myJob == "printTop5")
	{
		cout << "Printing top 5 scores" << endl;
		Print5Scores(bot);
	}

	else
	{
		cout << "No job for me" << endl;
	}
}

int main()
{
	dpp::cluster bot("OTExNDEzMzQwOTI3MDQ1NzI2.YZhB0Q.Ug6ghF6e1bf62D7W4c3g7kTVUBI");

	bot.on_ready([&bot](const dpp::ready_t& event)
		{
			std::cout << "Logged in as " << bot.me.username << "!\n";

			doJob(&bot);


		});


	bot.start(false);
	return 0;
}