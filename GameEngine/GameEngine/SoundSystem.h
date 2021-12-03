#pragma once
#include "SubSystem.h"
#include <irrKlang.h>
#include <map>
#include "fmod_studio.hpp"
#include "fmod.hpp"

class SoundSystem :
	public SubSystem
{
private:
	irrklang::ISoundEngine* engine;

public:
	
	virtual void Start();
	virtual void Update();
	virtual void ProcessEvents();
	virtual void Exit();
};

