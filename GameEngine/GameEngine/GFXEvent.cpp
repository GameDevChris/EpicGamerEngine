#include "GFXEvent.h"

GFXEvent::GFXEvent(std::string type, int modelType, vector<Event*>* queue)
{
	eventSubsystem = GraphicsSub;
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
	eventSubsystem = GraphicsSub;

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
	Throw();
}
