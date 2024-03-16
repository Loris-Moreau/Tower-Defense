#include "FPSActor.h"
#include "MoveComponent.h"
#include "Game.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "FPSCameraComponent.h"
#include "MeshComponent.h"
#include "BallActor.h"
#include "BoxComponent.h"
#include "Collisions.h"
#include "CubeActor.h"

FPSActor::FPSActor() :
	Actor(),
	moveComponent(nullptr),
	audioComponent(nullptr),
	meshComponent(nullptr),
	cameraComponent(nullptr),
	lastFootstep(0.0f),
	boxComponent(nullptr)
{
	moveComponent = new MoveComponent(this);
	cameraComponent = new FPSCameraComponent(this);

	FPSModel = new Actor();
	FPSModel->setScale(Vector3(1.0f, 0.75f, 1.0f));

	boxComponent = new BoxComponent(this);
	AABB collision(Vector3(-25.0f, -25.0f, -87.5f), Vector3(25.0f, 25.0f, 87.5f));
	boxComponent->setObjectBox(collision);
	boxComponent->setShouldRotate(false);
}

void FPSActor::updateActor(float dt)
{
	Actor::updateActor(dt);
	delay -= 1 * dt;
	if (shootCount == 2 && delay <= 2)
	{
		CubeActor* score = new CubeActor(std::to_string(getGame().getScore()));
		score->setScale(Vector3(2.0f, 1.5f, 1.5f));
		getGame().addCubes(score);
	}
	if(shootCount>= 2 && delay <=0)
	{
		getGame().deleteCubes(getGame().getCubes());
		getGame().initiateGame();
		shootCount = 0;
		getGame().setScore(0);
	}

	if (delay <= 0 && hasShoot)
	{
		hasShoot = false;
	}


	Vector3 modelPosition = getPosition();
	modelPosition += getForward() * MODEL_OFFSET.x;
	modelPosition += getRight() * MODEL_OFFSET.y;
	modelPosition.z += MODEL_OFFSET.z;
	FPSModel->setPosition(modelPosition);
	Quaternion q = getRotation();
	q = Quaternion::concatenate(q, Quaternion(getRight(), cameraComponent->getPitch()));
	FPSModel->setRotation(q);

	fixCollisions();
}

void FPSActor::actorInput(const InputState& inputState)
{
	// Shoot
	if (delay <= 0 && shootCount < 2)
	{
		if (inputState.mouse.getButtonState(1) == ButtonState::Pressed && directionClick && powerClick && !hasShoot)
		{
			shoot();
			hasShoot = true;
			directionClick = false;
			powerClick = false;
			shootCount++;
			delay = 6.0f;

		}

		if (inputState.mouse.getButtonState(1) == ButtonState::Pressed && directionClick && !powerClick)
		{
			powerClick = true;
		}

		if (inputState.mouse.getButtonState(1) == ButtonState::Pressed && !hasShoot)
		{
			directionClick = true;
		}

	}
}

void FPSActor::shoot()
{
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	Vector3 start = getGame().getRenderer().unproject(screenPoint);
	screenPoint.z = 0.9f;
	Vector3 end = getGame().getRenderer().unproject(screenPoint);
	Vector3 dir = Vector3(getGame().getArrow()->getRotation().w, getGame().getArrow()->getRotation().z, 0);
	dir.normalize();
	BallActor* ball = new BallActor();
	ball->setPlayer(this);
	ball->setArrow(getGame().getArrow());
	ball->setPosition(Vector3(0.0f, 38.0f, 10.0f));
	ball->rotateToNewForward(dir);
}

void FPSActor::setVisible(bool isVisible)
{
	meshComponent->setVisible(isVisible);
}

void FPSActor::fixCollisions()
{
	computeWorldTransform();

	const AABB& playerBox = boxComponent->getWorldBox();
	Vector3 pos = getPosition();

	auto& planes = getGame().getPlanes();
	for (auto pa : planes)
	{
		const AABB& planeBox = pa->getBox()->getWorldBox();
		if (Collisions::intersect(playerBox, planeBox))
		{
			float dx1 = planeBox.max.x - playerBox.min.x;
			float dx2 = planeBox.min.x - playerBox.max.x;
			float dy1 = planeBox.max.y - playerBox.min.y;
			float dy2 = planeBox.min.y - playerBox.max.y;
			float dz1 = planeBox.max.z - playerBox.min.z;
			float dz2 = planeBox.min.z - playerBox.max.z;

			float dx = Maths::abs(dx1) < Maths::abs(dx2) ? dx1 : dx2;
			float dy = Maths::abs(dy1) < Maths::abs(dy2) ? dy1 : dy2;
			float dz = Maths::abs(dz1) < Maths::abs(dz2) ? dz1 : dz2;

			if (Maths::abs(dx) <= Maths::abs(dy) && Maths::abs(dx) <= Maths::abs(dz))
			{
				pos.x += dx;
			}
			else if (Maths::abs(dy) <= Maths::abs(dx) && Maths::abs(dy) <= Maths::abs(dz))
			{
				pos.y += dy;
			}
			else
			{
				pos.z += dz;
			}

			setPosition(pos);
			boxComponent->onUpdateWorldTransform();
		}
	}
}