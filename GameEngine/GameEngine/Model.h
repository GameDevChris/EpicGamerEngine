#pragma once
#include "irrlicht.h";
#include <vector>;
#include <iostream>;
using namespace irr;
using namespace core;
using namespace scene;
using namespace std;

struct Model
{
public:
	enum ModelType
	{
		Dragon,
		Chris
	};

	std::string modelName = "";
	ModelType type;
	//IAnimatedMeshSceneNode* node;
	IAnimatedMesh* mesh;
	std::string texturePath;
	std::string modelPath;

	vector<std::string>* texturePaths;

	Model(IAnimatedMesh* myMesh, vector<std::string>* myTextures, std::string myModel, int myType)
	{
		mesh = myMesh;
		texturePaths = myTextures;
		modelPath = myModel;
		type = ModelType(myType);

		if (myType == 0)
		{
			modelName = "Dragon";
		}

		else if (myType == 1)
		{
			modelName = "Chris";
		}
	}
};