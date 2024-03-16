#include "BallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BallMoveComponent.h"
#include "CubeActor.h"
#include "Game.h"
#include "BoxComponent.h"


BallActor::BallActor() : Actor(), lifetimeSpan(10.0f), audio(nullptr), ballMove(nullptr)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	ballMove = new BallMoveComponent(this);
	ballMove->setForwardSpeed(6*getGame().getArrow()->getScale().x);
	BoxComponent* bc = new BoxComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Sphere").getBox());
}

void BallActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	lifetimeSpan -= dt;
	ballMove->setForwardSpeed(ballMove->getForwardSpeed() * 0.995);
	if (lifetimeSpan < 0.0f || ballMove->getForwardSpeed() <0 || ballMove->getOwner().getPosition().x >= 750)
	{
		setState(ActorState::Dead);
	}
	if(ballMove->getOwner().getPosition().y > 135 || ballMove->getOwner().getPosition().y < -50)
	{
		ballMove->getOwner().rotateToNewForward(Vector3::unitX);
	}
}

void BallActor::setPlayer(Actor* player)
{
	ballMove->setPlayer(player);
}

void BallActor::setArrow(Actor* arrow)
{
	ballMove->setArrow(arrow);
}

void BallActor::hitTarget(CubeActor* target)
{
		
}