#pragma once
#include "Model.h"
#include "SubSystem.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class AssetManagerSystem :
	public SubSystem
{
public:
	IrrlichtDevice* device = NULL;
	IVideoDriver* driver = NULL;
	ISceneManager* smgr = NULL;

	std::vector<Model*> models;
	Model* LoadModel(std::string modelPath, std::vector<std::string>* myTexturePaths, int modelType, std::string modelName);

	virtual void Update();
};

