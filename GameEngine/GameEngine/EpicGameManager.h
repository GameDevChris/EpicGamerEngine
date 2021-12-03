#pragma once
#include <iostream>
#include "MyVec3.h"
#include <random>

struct EpicGameManager
{
	int score = 0;


	bool levelStarted = false;
	enum Scene
	{
		Start,
		Editor,
		Game,
		End
	};

	Scene currentScene = Start;

	//Graphic Settings
	std::string EngineTitle = "";
	int EngineWidth = 0;
	int EngineHeight = 0;
	MyVec3 BGColour;
	int BitPerPixel = 32;
	bool Fullscreen = false;
	bool StencilBuffer = true;
	int AntiAlias = 16;
	bool VSync = false;

	//Gameplay Settings
	int playerID = 0;
	int platformID = 0;
	int buttonID = 0;
	
	MyVec3 PlayerSize = MyVec3(10, 10, 10);
	MyVec3 targetColor = MyVec3(255, 20, 147);

	std::vector<MyVec3>* colours;

	bool FreeCamEnable = true;

	//Player Settings
	int PlayerLinearSpeed = 20;
	int	PlayerAngularSpeed = 10;
	int	PlayerJumpHeight = 100;

	//Network Settings
	std::string botScoreTextPath = "";
	std::string	botJobTextPath = "";
	std::string	discordLink = "";

	//Sound Settings
	std::string backgroundMusic = "";

	MyVec3 AssignColour() 
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> randCol(0, 255);

		MyVec3 newVec((float)randCol(rng), (float)randCol(rng), (float)randCol(rng));

		return newVec;
	}
};