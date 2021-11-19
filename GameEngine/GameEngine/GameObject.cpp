#include "GameObject.h"

GameObject::GameObject(Model* mod, MyVec3 pos, MyVec3 rot, MyVec3 sca)
{
	myModel = mod;
	Position = pos;
	Scale = sca;
	Rotation = rot;
}

GameObject::GameObject(Model* mod, Rigidbody* rb, MyVec3 pos, MyVec3 rot, MyVec3 sca)
{
	myModel = mod;
	myRB = rb;
	Position = pos;
	Scale = sca;
	Rotation = rot;
}

GameObject::GameObject()
{
	
}

void GameObject::SyncTransform()
{
	if (myRB->myType == "static" || myRB->myType == "Static")
	{
		myModel->myNode->setPosition(vector3df(myRB->staticRB->getGlobalPose().p.x, myRB->staticRB->getGlobalPose().p.y, myRB->staticRB->getGlobalPose().p.z));

		quaternion myRot(myRB->staticRB->getGlobalPose().q.x, myRB->staticRB->getGlobalPose().q.y, myRB->staticRB->getGlobalPose().q.z, myRB->staticRB->getGlobalPose().q.w);

		myRot.normalize();

		vector3df myRotEuler;
		myRot.toEuler(myRotEuler);

		myModel->myNode->setRotation(myRotEuler * RADTODEG);
	}

	else if (myRB->myType == "dynamic" || myRB->myType == "Dynamic")
	{
		myModel->myNode->setPosition(vector3df(myRB->dynamicRB->getGlobalPose().p.x, myRB->dynamicRB->getGlobalPose().p.y, myRB->dynamicRB->getGlobalPose().p.z));
		
		quaternion myRot(myRB->dynamicRB->getGlobalPose().q.x, myRB->dynamicRB->getGlobalPose().q.y, myRB->dynamicRB->getGlobalPose().q.z, myRB->dynamicRB->getGlobalPose().q.w);
		
		myRot.normalize();

		vector3df myRotEuler;
		myRot.toEuler(myRotEuler);
		
		myModel->myNode->setRotation(myRotEuler * RADTODEG);
	}

	else
	{
		cout << "No RigidBody found!" << endl;
	}
}
