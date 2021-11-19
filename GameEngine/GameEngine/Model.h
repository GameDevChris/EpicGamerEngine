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
	IAnimatedMeshSceneNode* myNode;
	std::string texturePath;
	std::string modelPath;

	float sizeX = 0;
	float sizeY = 0;
	float sizeZ = 0;

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