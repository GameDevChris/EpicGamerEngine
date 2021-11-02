#include "AssetManagerSystem.h"

Model* AssetManagerSystem::LoadModel(std::string modelPath, std::string texturePath, int modelType)
{
	IAnimatedMesh* mesh = smgr->getMesh(modelPath.c_str());
	if (!mesh)
	{
		device->drop();
		cout << "Failed to load mesh" << endl;
	}

	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialTexture(0, driver->getTexture(texturePath.c_str()));

		Model newModel(node, modelType);
		return(&newModel);
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
				cout << "Asset Event found" << endl;
				if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->ASSETLoad)
				{
					cout << "Loading Asset" << endl;
					Model* newModel = LoadModel((*engineEventQueue)[i]->myData->modPath, (*engineEventQueue)[i]->myData->texPath, (*engineEventQueue)[i]->myData->modType);
					models.push_back(newModel);
				}

				else if ((*engineEventQueue)[i]->eventType == (*engineEventQueue)[i]->ASSETAssign)
				{
					cout << "Assigning Asset" << endl;
					GFXEvent newGFX("GFXUseModel", (*engineEventQueue)[i]->myData->modType, engineEventQueue);
					newGFX.myData->myModel = models[(*engineEventQueue)[i]->myData->modType];
					newGFX.Throw();
				}
			}
		}
	}
}
