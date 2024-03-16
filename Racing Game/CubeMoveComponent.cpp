#include "CubeMoveComponent.h"
#include "Actor.h"
#include "Vector3.h"
#include "LineSegment.h"
#include "PhysicsSystem.h"
#include "BallActor.h"
#include "Game.h"

CubeMoveComponent::CubeMoveComponent(Actor* ownerP) : MoveComponent(ownerP), arrow(nullptr)
{

}
void CubeMoveComponent::setArrow(Actor* arrowP)
{
	arrow = arrowP;
}

void CubeMoveComponent::update(float dt)
{
	const float segmentLength = 4.0f;
	Vector3 start = owner.getPosition();
	Vector3 dir = owner.getForward();
	Vector3 end = start + dir * segmentLength;
	LineSegment l(start, end);
	PhysicsSystem::CollisionInfo info;
	if (owner.getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != arrow)
	{
		BallActor* ball = dynamic_cast<BallActor*>(info.actor);
		if(ball)
		{
			dir = Vector3::reflect(owner.getForward(), Vector3::normalize(ball->getPosition()));
		}
		dir.z = 0;
		if(dir.x <= 0)
		{
			dir.x = 1;
		}
		if (ball)
		{
			owner.rotateToNewForward(dir - ball->getForward());
		}

		CubeActor* pins = dynamic_cast<CubeActor*>(info.actor);

		if (owner.getGame().getPhysicsSystem().segmentCast(l , info) && info.actor != arrow)
		{
			this->setForwardSpeed(150.0f);
			static_cast<CubeActor*>(&owner)->hitBall(ball);
		}

		if (owner.getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != arrow)
		{
			static_cast<CubeActor*>(&owner)->hitPins(pins);
		}
	}
	MoveComponent::update(dt);
}