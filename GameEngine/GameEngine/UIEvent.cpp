#include "UIEvent.h"

UIEvent::UIEvent(std::string type, std::vector<Event*>* queue, IrrlichtDevice* dev, video::IVideoDriver* driv, ISceneManager* man, IrrIMGUI::CIMGUIEventReceiver* evRec)
{
	myData = new EventData();

	eventSubsystem = UISub;

	if (type == "CreateHandler")
	{
		eventType = CreateHandler;
	}
	else
	{
		std::cout << "ERROR, unknown Asset event type!" << std::endl;
	}

	myData->myEventReceiver = evRec;
	myData->myDevice = dev;
	myData->myDriver = driv;
	myData->mySmgr = man;

	EQueue = queue;

	Throw();
}

UIEvent::UIEvent(std::string type, std::vector<Event*>* queue)
{
	eventSubsystem = UISub;

	if (type == "DrawUI")
	{
		eventType = DrawUI;
		//cout << "Draw time gamers!" << endl;
	}
	else
	{
		std::cout << "ERROR, unknown Asset event type!" << std::endl;
	}

	EQueue = queue;

	Throw();
}
