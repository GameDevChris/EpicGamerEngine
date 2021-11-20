#include <dpp/dpp.h>
#include <iostream>  
#include <sstream>  
#include <vector>


using namespace std;
dpp::snowflake* globalChannel;


void PrintAllScores(dpp::cluster* bot, dpp::snowflake* channel)
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

	bot->message_create(dpp::message(*channel, "All Scores:"));
	bot->message_create(dpp::message(*channel, "-----"));

	for (int i = 0; i < dataVector->size(); i++)
	{
		int val = (*dataVector)[i];
		stringstream ss;

		ss << val;
		std::string scoreText;
		ss >> scoreText;


		bot->message_create(dpp::message(*channel, scoreText));
	}
}

void Print5Scores(dpp::cluster* bot, dpp::snowflake* channel)
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

	bot->message_create(dpp::message(*channel, "Top 5 Scores:"));
	bot->message_create(dpp::message(*channel, "-----"));

	for (int i = 0; i < 5; i++)
	{
		int val = (*dataVector)[i];
		stringstream ss;

		ss << val;
		std::string scoreText;
		ss >> scoreText;


		bot->message_create(dpp::message(*channel, scoreText));
	}
}

void PrintHighScores(dpp::cluster* bot, dpp::snowflake* channel)
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

	bot->message_create(dpp::message(*channel, "Highscore:"));
	bot->message_create(dpp::message(*channel, "-----"));

	int val = (*dataVector)[0];
	stringstream ss;

	ss << val;
	std::string scoreText;
	ss >> scoreText;

	bot->message_create(dpp::message(*channel, scoreText));
}

void PrintNewestScore(dpp::cluster* bot, dpp::snowflake* channel)
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

	bot->message_create(dpp::message(*channel, "New score:"));
	bot->message_create(dpp::message(*channel, "-----"));

	int val = (*dataVector)[dataVector->size()];
	stringstream ss;

	ss << val;
	std::string scoreText;
	ss >> scoreText;

	bot->message_create(dpp::message(*channel, scoreText));
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

void doJob(dpp::cluster* bot, dpp::snowflake* channel)
{
	std::string myJob = GetJob();

	if (myJob == "newScore")
	{
		PrintNewestScore(bot, channel);
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

			dpp::snowflake myChannel = dpp::snowflake("838441750611230723");

			bot.message_create(dpp::message(myChannel, "Am alive!"));

			//doJob(&bot, &myChannel);
		});

	bot.on_message_create([&bot](const dpp::message_create_t& event)
		{
			if (event.msg->content == "!scores")
			{
				cout << event.msg->channel_id << endl;
				PrintAllScores(&bot, &(event.msg->channel_id));
			}

			else if (event.msg->content == "!getChannel")
			{
				cout << event.msg->channel_id << endl;
				globalChannel = &event.msg->channel_id;

				bot.message_create(dpp::message(*globalChannel, "Am alive!"));
			}

			else if (event.msg->content == "!top5")
			{
				Print5Scores(&bot, &(event.msg->channel_id));
			}

			else if (event.msg->content == "!highscore")
			{
				PrintHighScores(&bot, &(event.msg->channel_id));
			}

			else if (event.msg->content == "!help")
			{
				bot.message_create(dpp::message(event.msg->channel_id, "Commands"));
				bot.message_create(dpp::message(event.msg->channel_id, "-----"));
				bot.message_create(dpp::message(event.msg->channel_id, "Use !scores to get all stored scores"));
				bot.message_create(dpp::message(event.msg->channel_id, "Use !top5 to get top 5 stored scores"));
				bot.message_create(dpp::message(event.msg->channel_id, "Use !highscore to get highscore"));
			}
		});

	bot.start(false);
	return 0;
}