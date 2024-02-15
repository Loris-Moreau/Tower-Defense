#include "BallMoveComponent.h"
#include "Actor.h"
#include "Vector3.h"
#include "LineSegment.h"
#include "Collisions.h"
#include "PhysicsSystem.h"
#include "BallActor.h"
#include "CubeActor.h"
#include "TargetActor.h"
#include "Game.h"

BallMoveComponent::BallMoveComponent(Actor* ownerP) : MoveComponent(ownerP), player(nullptr)
{
}

void BallMoveComponent::setPlayer(Actor* playerP)
{
	player = playerP;
}

void BallMoveComponent::update(float dt)
{
	// Construct segment in direction of travel
	const float segmentLength = 30.0f;
	Vector3 start = owner.getPosition();
	Vector3 dir = owner.getForward();
	Vector3 end = start + dir * segmentLength;

	// Create line segment
	LineSegment l(start, end);

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;
	// (Don't collide vs player)
	if (owner.getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != player)
	{
		// If we collided, reflect the ball about the normal
		dir = Vector3::reflect(dir, info.normal);
		owner.rotateToNewForward(dir);

		// Did we hit a Cube ?
		CubeActor* target = dynamic_cast<CubeActor*>(info.actor);
		if (target)
		{
			static_cast<BallActor*>(&owner)->hitTarget(target);
		}

		// Did we hit a Plane ?
		PlaneActor* pTarget = dynamic_cast<PlaneActor*>(info.actor);
		if (pTarget)
		{
			static_cast<BallActor*>(&owner)->hitPlane(pTarget);
		}
	}

	// Base class update moves based on forward speed
	MoveComponent::update(dt);
}
