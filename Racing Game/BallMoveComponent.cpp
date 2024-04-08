#include "BallMoveComponent.h"
#include "Actor.h"
#include "Vector3.h"
#include "LineSegment.h"
#include "Collisions.h"
#include "PhysicsSystem.h"
#include "BallActor.h"
#include "TargetActor.h"
#include "Game.h"
#include "CubeActor.h"

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
	constexpr float segmentLength = 30.0f;
	const Vector3 start = owner.getPosition();
	Vector3 dir = owner.getForward();
	const Vector3 end = start + dir * segmentLength;

	// Create line segment
	const LineSegment l(start, end);

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;
	// (Don't collide vs player)
	if (owner.getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != player)
	{
		// If we collided, reflect the ball about the normal
		dir = Vector3(1.0f, 0.0f, 0.0f);
		owner.rotateToNewForward(dir);
		// Did we hit a target?
		CubeActor* cube = dynamic_cast<CubeActor*>(info.actor);
		if (cube)
		{
			static_cast<BallActor*>(&owner)->hitTarget(cube);
		}
	}

	// Base class update moves based on forward speed
	MoveComponent::update(dt);
}