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
	IAnimatedMeshSceneNode* node;

	Model(IAnimatedMeshSceneNode* myNode, int myType)
	{
		node = myNode;
		type = ModelType(myType);
	}
};