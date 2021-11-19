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

	std::string modelName = "";

	int type;
 
	IAnimatedMesh* mesh;
	IAnimatedMeshSceneNode* myNode;
	std::string texturePath;
	std::string modelPath;

	float sizeX = 0;
	float sizeY = 0;
	float sizeZ = 0;

	vector<std::string>* texturePaths;

	Model(IAnimatedMesh* myMesh, vector<std::string>* myTextures, std::string myModel, int myType, std::string name)
	{
		mesh = myMesh;
		texturePaths = myTextures;
		modelPath = myModel;
		type = myType;
		modelName = name;
	}
};