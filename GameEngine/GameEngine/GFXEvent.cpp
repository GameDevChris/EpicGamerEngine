#include "GFXEvent.h"

GFXEvent::GFXEvent(std::string type, int modelType, vector<Event*>* queue)
{
	//eventSubsystem = GraphicsSub;
	myData->modType = modelType;

	if (type == "GFXDefault")
	{
		eventType = GFXDefault;
	}

	else if (type == "GFXQuit")
	{
		eventType = GFXQuit;
	}

	else if (type == "GFXUp")
	{
		eventType = GFXUp;
	}

	else if (type == "GFXDown")
	{
		eventType = GFXDown;
	}

	else if (type == "GFXLeft")
	{
		eventType = GFXLeft;
	}

	else if (type == "GFXRight")
	{
		eventType = GFXRight;
	}

	else if (type == "GFXCamUp")
	{
		eventType = GFXCamUp;
	}

	else if (type == "GFXCamDown")
	{
		eventType = GFXCamDown;
	}

	else if (type == "GFXCamLeft")
	{
		eventType = GFXCamLeft;
	}

	else if (type == "GFXCamRight")
	{
		eventType = GFXCamRight;
	}

	else if (type == "GFXCamForward")
	{
		eventType = GFXCamForward;
	}

	else if (type == "GFXCamBackward")
	{
		eventType = GFXCamBackward;
	}

	else if (type == "GFXUseModel")
	{
		eventType = GFXUseModel;
	}

	else
	{
		cout << "ERROR, unknown GFX event type!" << endl;
	}

	EQueue = queue;
}

GFXEvent::GFXEvent(std::string type, vector<Event*>* queue)
{
	cout << "Constructor for gfx used" << endl;
	EventType myEventType;
	//eventSubsystem = GraphicsSub;
	
	myEventType = GFXDefault;

	if (type == "GFXQuit")
	{
		myEventType = GFXQuit;
	}

	else if (type == "GFXUp")
	{
		myEventType = GFXUp;
	}

	else if (type == "GFXDown")
	{
		myEventType = GFXDown;
	}

	else if (type == "GFXLeft")
	{
		myEventType = GFXLeft;
		cout << "LEFT INNIT" << endl;
	}

	else if (type == "GFXRight")
	{
		myEventType = GFXRight;
	}

	else if (type == "GFXCamUp")
	{
		myEventType = GFXCamUp;
	}

	else if (type == "GFXCamDown")
	{
		myEventType = GFXCamDown;
	}

	else if (type == "GFXCamLeft")
	{
		myEventType = GFXCamLeft;
	}

	else if (type == "GFXCamRight")
	{
		myEventType = GFXCamRight;
	}

	else if (type == "GFXCamForward")
	{
		myEventType = GFXCamForward;
	}

	else if (type == "GFXCamBackward")
	{
		myEventType = GFXCamBackward;
	}

	else if (type == "GFXUseModel")
	{
		myEventType = GFXUseModel;
	}

	else
	{
		cout << "ERROR, unknown GFX event type!" << endl;
	}

	EQueue = queue;

	Throw(myEventType, *this);
}
