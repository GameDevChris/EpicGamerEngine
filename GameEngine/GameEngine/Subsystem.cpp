#include "SubSystem.h"

SubSystem::SubSystem()
{
}

void SubSystem::Start()
{
	std::cout << "Subsystem " << name << " -started!" << std::endl;
}

void SubSystem::Update()
{
	
}

void SubSystem::ProcessEvents()
{
}

void SubSystem::LateUpdate()
{
	std::cout << name << "Late updated" << std::endl;
}

void SubSystem::Exit()
{
}
