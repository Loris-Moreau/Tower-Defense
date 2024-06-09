#include "BallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "Door.h"
#include "BallMoveComponent.h"
#include "Game.h"

BallActor::BallActor() : Actor(), lifetimeSpan(1.75f),ballMove(nullptr)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
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

void BallActor::hitTarget()
{
	getGame().getDoors().at(0)->setStateDoor(true);
}
