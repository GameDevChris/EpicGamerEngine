#include <dpp/dpp.h>
#include <iostream>  
#include <sstream>  
#include <vector>


using namespace std;

dpp::snowflake* leaderboardChannel = new dpp::snowflake(uint64_t(912656966487269406));
dpp::snowflake* newScoreChannel = new dpp::snowflake(uint64_t(912657008027648020));

void PrintAllScores(dpp::cluster* bot)
{

	vector<int>* dataVector = new vector<int>;
	dataVector->clear();

	string filename("../scoreData.txt");
	int number;
	ifstream input_file(filename);

	while (input_file >> number) {
		dataVector->push_back(number);
	}

	cout << endl;
	input_file.close();

	sort(dataVector->begin(), dataVector->end(), greater<int>());

	bot->message_create(dpp::message(*newScoreChannel, "-----"));
	bot->message_create(dpp::message(*newScoreChannel, "Scores:"));
	bot->message_create(dpp::message(*newScoreChannel, "-----"));

	for (int i = 0; i < dataVector->size(); i++)
	{
		int val = (*dataVector)[i];
		stringstream ss;

		ss << val;
		std::string scoreText;
		ss >> scoreText;


		bot->message_create(dpp::message(*newScoreChannel, scoreText));
	}
}

void PrintHighScores(dpp::cluster* bot)
{
	vector<int>* dataVector = new vector<int>;
	dataVector->clear();

	string filename("../scoreData.txt");
	int number;
	ifstream input_file(filename);

	while (input_file >> number) {
		dataVector->push_back(number);
	}

	cout << endl;
	input_file.close();

	sort(dataVector->begin(), dataVector->end(), greater<int>());

	bot->message_create(dpp::message(*leaderboardChannel, "Highscore:"));
	bot->message_create(dpp::message(*leaderboardChannel, "-----"));

	int val = (*dataVector)[0];
	stringstream ss;

	ss << val;
	std::string scoreText;
	ss >> scoreText;

	bot->message_create(dpp::message(*leaderboardChannel, scoreText));
}


std::string GetJob()
{
	std::string job = "";

	string filename("../jobData.txt");

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
		PrintAllScores(bot);
	}

	else if (myJob == "printTop5")
	{
		PrintHighScores(bot);
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