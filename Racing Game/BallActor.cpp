#include "BallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BallMoveComponent.h"
#include "LevelLoader.h"

BallActor::BallActor() : Actor(), lifetimeSpan(2.0f), ballMove(nullptr)
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
}

void BallActor::loadProperties(const rapidjson::Value& inObj)
{
	Actor::loadProperties(inObj);
	JsonHelper::getFloat(inObj, "lifespan", lifetimeSpan);
}

void BallActor::saveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	Actor::saveProperties(alloc, inObj);
	JsonHelper::addFloat(alloc, inObj, "lifespan", lifetimeSpan);
}
