#include "BallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
//#include "AudioComponent.h"
#include "BallMoveComponent.h"
#include "PhysicsSystem.h"

BallActor::BallActor() : Actor(), lifetimeSpan(20.0f),/* audio(nullptr),*/ ballMove(nullptr)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	//audio = new AudioComponent(this);
	ballMove = new BallMoveComponent(this);
	ballMove->setForwardSpeed(1500.0f);
}

void BallActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	lifetimeSpan -= dt;
	if (lifetimeSpan < 0.0f)
	{
		setState(ActorState::Dead);
	}
}

void BallActor::setPlayer(Actor* player)
{
	ballMove->setPlayer(player);
}

void BallActor::hitTarget(CubeActor* target)
{
	if (target != nullptr)
	{
		target->setState(ActorState::Dead);
	}
	setState(ActorState::Dead);
}

void BallActor::hitPlane(PlaneActor* actor)
{
	setAngle(Vector3::unitX, 0);
}
