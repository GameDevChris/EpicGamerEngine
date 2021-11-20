#include <dpp/dpp.h>
#include <iostream>  
#include <sstream>  
#include <vector>
#include <windows.h>
#include <urlmon.h>

using namespace std;

void GetFile()
{
	LPCTSTR szUrl = (LPCTSTR)("https://gist.githubusercontent.com/CampfireGames-Chris/f0dd268fd097c56b3557d4347b0ee48e/raw/6db43ac4d139b13e38c3a6a8e8ac3f13ed72c807/scoreData.txt");

	LPCTSTR szOutput = (LPCTSTR)("../downloadedScoreData.txt");

	HRESULT result = URLDownloadToFile(nullptr, szUrl, szOutput, 0, nullptr);

	switch (result)
	{
	case S_OK:
		cout << "Download ok.";
		break;
	case E_OUTOFMEMORY:
		cout << "The buffer length is invalid, or there is insufficient memory to complete the operation.";
		break;
	case INET_E_DOWNLOAD_FAILURE:
		cout << "The specified resource or callback interface was invalid.";
		break;
	}

}

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

int main()
{
	GetFile();

	dpp::cluster bot("OTExNDEzMzQwOTI3MDQ1NzI2.YZhB0Q.Ug6ghF6e1bf62D7W4c3g7kTVUBI");

	bot.on_ready([&bot](const dpp::ready_t& event)
		{
			std::cout << "Logged in as " << bot.me.username << "!\n";
		});

	bot.on_message_create([&bot](const dpp::message_create_t& event)
		{
			if (event.msg->content == "!scores")
			{
				PrintAllScores(&bot, &(event.msg->channel_id));
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