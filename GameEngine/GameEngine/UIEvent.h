#pragma once
#include "Event.h"
class UIEvent :
	public Event
{
public:
	UIEvent(std::string type, std::vector<Event*>* queue, IrrlichtDevice* dev, video::IVideoDriver* driv, ISceneManager* man, IrrIMGUI::CIMGUIEventReceiver* evRec);
	UIEvent(std::string type, std::vector<Event*>* queue);
};

