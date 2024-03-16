#include "CubeActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BoxComponent.h"
#include "BallActor.h"
#include "CubeMoveComponent.h"
#include "Game.h"
#include "MoveComponent.h"

CubeActor::CubeActor() : lifetimeSpan(10.0f)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
	BoxComponent* bc = new BoxComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Cube").getBox());
	cubeMove = new CubeMoveComponent(this);
}

CubeActor::CubeActor(std::string spriteNameP) : spriteName(spriteNameP)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
	SpriteComponent* sp = new SpriteComponent(this, Assets::getTexture(spriteName));
	sp->setVisible(true);
	cubeMove = new CubeMoveComponent(this);
}

void CubeActor::updateActor(float dt)
{
	Actor::updateActor(dt);
	if (gotHit) lifetimeSpan -= 1;
	if (lifetimeSpan < 0.0f || cubeMove->getOwner().getPosition().x >= 800)
	{
		getGame().setScore();
		setState(ActorState::Dead);
	}
}

void CubeActor::hitBall(BallActor* ball)
{
	if(ball != nullptr)
	{
		gotHit = true;
	}
}
void CubeActor::hitPins(CubeActor* pins)
{
	if (pins != nullptr)
	{
		gotHit = true;
		pins->lifetimeSpan = 2.0f;
		Vector3 dir = getForward();
		dir = Vector3::reflect(getForward(), Vector3::normalize(pins->getPosition()));
		dir.z = 0;
		if(dir.x <= 0)
		{
			dir.x = 1;
		}
		pins->cubeMove->setForwardSpeed(150);
		rotateToNewForward(dir);
	}
}

void CubeActor::setArrow(Actor* arrow)
{
	cubeMove->setArrow(arrow);
}