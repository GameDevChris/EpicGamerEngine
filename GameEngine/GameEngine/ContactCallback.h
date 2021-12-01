#pragma once
#include <PxPhysicsAPI.h>
#include <vector>
using namespace physx;

class ContactCallback : public PxSimulationEventCallback
{
public:

	physx::PxShape* colShape1;
	physx::PxShape* colShape2;


	std::vector<PxVec3> contactPositions;
	std::vector<PxVec3> contactImpulses;

	void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) { PX_UNUSED(constraints); PX_UNUSED(count); }
	void onWake(PxActor** actors, PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count); }
	void onSleep(PxActor** actors, PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count); }
	void onTrigger(PxTriggerPair* pairs, PxU32 count) { PX_UNUSED(pairs); PX_UNUSED(count); }
	void onAdvance(const PxRigidBody* const*, const PxTransform*, const PxU32) {}

	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
};

