#include "UIEvent.h"

UIEvent::UIEvent(std::string type, vector<Event*>* queue, IrrlichtDevice* dev, video::IVideoDriver* driv, ISceneManager* man, IrrIMGUI::CIMGUIEventReceiver* evRec)
{
	myData = new EventData();

	eventSubsystem = UISub;

	if (type == "CreateHandler")
	{
		eventType = CreateHandler;
	}
	else
	{
		cout << "ERROR, unknown Asset event type!" << endl;
	}

	myData->myEventReceiver = evRec;
	myData->myDevice = dev;
	myData->myDriver = driv;
	myData->mySmgr = man;

	EQueue = queue;

	Throw();
}

UIEvent::UIEvent(std::string type, vector<Event*>* queue)
{
	eventSubsystem = UISub;

	if (type == "DrawUI")
	{
		eventType = DrawUI;
		//cout << "Draw time gamers!" << endl;
	}
	else
	{
		cout << "ERROR, unknown Asset event type!" << endl;
	}

	EQueue = queue;

	Throw();
}
