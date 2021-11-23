#pragma once
#include "SubSystem.h"
//#include <dpp/dpp.h>

class NetworkSystem :
	public SubSystem
{
public:
	int scoreValue = 0;

	std::string scoreFilePath = "../../scoreData.txt";
	std::string jobFilePath = "../../jobData.txt";
	//std::string botToken = "OTExNDEzMzQwOTI3MDQ1NzI2.YZhB0Q.Ug6ghF6e1bf62D7W4c3g7kTVUBI";
	//dpp::cluster* epicGamerBotPointer = NULL;

	virtual void Start();
	virtual void Update();
	virtual void Exit();
};

