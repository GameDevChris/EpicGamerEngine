#include "SubSystem.h"

SubSystem::SubSystem()
{
}

void SubSystem::Start()
{
	//eventQueue.clear();
	cout << "Subsystem " << name << " -started!" << endl;
}

void SubSystem::Update()
{
	
}

void SubSystem::LateUpdate()
{
	cout << name << "Late updated" << endl;
}

void SubSystem::Exit()
{
}
