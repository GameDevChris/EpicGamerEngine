#include "Engine.h"
#include <SFML/Window/Keyboard.hpp>

bool runEngine;

int main(int argc, char* args[])
{
	
	runEngine = true;
	Engine myEngine;
	myEngine.Start();

	while (runEngine)
	{
		myEngine.Update();

		if (myEngine.finished)
		{
			std::cout << std::endl;
			std::cout << "Engine Finished" << std::endl;
			runEngine = false;
		}
	}

	
	return 0;
	
}

/*#include <PxPhysicsAPI.h>

int main() {

	// declare variables
	



}*/







