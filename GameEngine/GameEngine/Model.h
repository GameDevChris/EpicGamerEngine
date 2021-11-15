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

	ModelType type;
	//IAnimatedMeshSceneNode* node;
	IAnimatedMesh* mesh;
	std::string texture;

	Model(IAnimatedMesh* myMesh, std::string myTexture,  int myType)
	{
		mesh = myMesh;
		texture = myTexture;
		type = ModelType(myType);
	}
};