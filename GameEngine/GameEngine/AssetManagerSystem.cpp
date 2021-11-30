#include "AssetManagerSystem.h"

Model* AssetManagerSystem::LoadModel(std::string modelPath, std::vector<std::string>* myTexturePaths, int modelType, std::string modelName)
{
	IAnimatedMesh* mesh = smgr->getMesh(modelPath.c_str());
	if (!mesh)
	{
		device->drop();
		std::cout << "Failed to load mesh" << std::endl;
	}

	else
	{
		Model* newModel = new Model(mesh, myTexturePaths, modelPath, modelType, modelName);

		return(newModel);
	}

	return(0);
}

void AssetManagerSystem::Update()
{
	if (!(*engineEventQueue).empty())
	{
		for (int i = 0; i < (*engineEventQueue).size(); i++)
		{
			if ((*engineEventQueue)[i]->eventSubsystem == (*engineEventQueue)[i]->AssetSub)
			{
				std::cout << "Asset Event found" << std::endl;
				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->ASSETLoad)
				{
					std::cout << "Loading Asset" << std::endl;
					Model* newModel = LoadModel((*engineEventQueue)[i]->myData->modPath, (*engineEventQueue)[i]->myData->texPaths, (*engineEventQueue)[i]->myData->modType, (*engineEventQueue)[i]->myData->myName);
					models.push_back(newModel);
				}

				//delete((*engineEventQueue)[i]);
				//engineEventQueue->erase(engineEventQueue->begin() + i);
			}
		}
	}
}
