#include "ContactCallback.h"

void ContactCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	PX_UNUSED((pairHeader));
	std::vector<PxContactPairPoint> contactPoints;

	for (PxU32 i = 0; i < nbPairs; i++)
	{
		PxU32 contactCount = pairs[i].contactCount;
		if (contactCount)
		{
			contactPoints.resize(contactCount);
			pairs[i].extractContacts(&contactPoints[0], contactCount);

			for (PxU32 j = 0; j < contactCount; j++)
			{
				contactPositions.push_back(contactPoints[j].position);
				contactImpulses.push_back(contactPoints[j].impulse);

				colShape1 = pairs[i].shapes[0];
				colShape2 = pairs[i].shapes[1];
			}
		}
	}
}
