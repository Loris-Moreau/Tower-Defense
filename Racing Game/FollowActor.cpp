#include "FollowActor.h"
#include "MoveComponent.h"
#include "FollowCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "InputSystem.h"
#include "BallActor.h"
#include "Game.h"
#include "BoxComponent.h"
#include "Collisions.h"

FollowActor::FollowActor() :
	Actor(),
	moveComponent(nullptr),
	cameraComponent(nullptr),
	meshComponent(nullptr)
{
	meshComponent = new MeshComponent(this);
	meshComponent->setMesh(Assets::getMesh("Mesh_RacingCar"));
	setPosition(Vector3(0.0f, 0.0f, 500.0f));		// Position Car on the map with coordinate

	boxComponent = new BoxComponent(this);
	const AABB collision(Vector3(-35.0f, -35.f, -85.7f), Vector3(35.f, 35.f, 87.5f));
	boxComponent->setObjectBox(collision);
	boxComponent->setShouldRotate(false);

	moveComponent = new MoveComponent(this);
	cameraComponent = new FollowCameraComponent(this);
	cameraComponent->snapToIdeal();
}

void FollowActor::actorInput(const InputState& inputState)
{
	float strafeSpeed = 0.0f;
	
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		strafeSpeed -= 1000.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		strafeSpeed += 1000.0f;
	}
	if (inputState.mouse.getButtonState(1) == ButtonState::Pressed)
	{
		shoot();
	}

	moveComponent->setForwardSpeed(speed);
	moveComponent->setStrafeSpeed(strafeSpeed);
}

void FollowActor::updateActor(float dt)
{
	fixCollisions();
}


void FollowActor::setVisible(bool isVisibleP)
{
	meshComponent->setVisible(isVisibleP);
}

void FollowActor::setSpeed(float speedP)
{
	speed = speedP;
}

void FollowActor::shoot()
{
	//Get start point (in center of screen on near plane)
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	const Vector3 start = getGame().getRenderer().unproject(screenPoint);

	//Get end point (in center of screen, between near and far)
	screenPoint.z = 0.9f;
	const Vector3 end = getGame().getRenderer().unproject(screenPoint);

	//Get direction vector
	Vector3 dir = end - start;
	dir.normalize();

	//Spawn a ball
	BallActor* ball = new BallActor();
	ball->setPlayer(this);
	ball->setPosition(getPosition());

	//Rotate the ball to face new direction
	ball->rotateToNewForward(dir);

}

void FollowActor::fixCollisions()
{
	// Need to recompute world transform to update world box
	computeWorldTransform();

	const AABB& playerBox = boxComponent->getWorldBox();
	Vector3 pos = getPosition();

	const auto& planes = getGame().getPlanes();
	for (const auto pa : planes)
	{
		// Do we collide with this PlaneActor?
		const AABB& planeBox = pa->getBox()->getWorldBox();
		if (Collisions::intersect(playerBox, planeBox))
		{
			// Calculate all our differences
			float dx1 = planeBox.max.x - playerBox.min.x;
			float dx2 = planeBox.min.x - playerBox.max.x;
			float dy1 = planeBox.max.y - playerBox.min.y;
			float dy2 = planeBox.min.y - playerBox.max.y;
			float dz1 = planeBox.max.z - playerBox.min.z;
			float dz2 = planeBox.min.z - playerBox.max.z;

			// Set dx to whichever of dx1/dx2 have a lower abs
			const float dx = Maths::abs(dx1) < Maths::abs(dx2) ? dx1 : dx2;
			// Ditto for dy
			const float dy = Maths::abs(dy1) < Maths::abs(dy2) ? dy1 : dy2;
			// Ditto for dz
			const float dz = Maths::abs(dz1) < Maths::abs(dz2) ? dz1 : dz2;

			// Whichever is closest, adjust x/y position
			if (Maths::abs(dx) <= Maths::abs(dy) && Maths::abs(dx) <= Maths::abs(dz))
			{
				pos.x += dx;
			}
			else if (Maths::abs(dy) <= Maths::abs(dx) && Maths::abs(dy) <= Maths::abs(dz))
			{
				if(dy < 0)
				{
					pos.y += dy - 10;
				}
				if (dy>0)
				{
					pos.y += dy + 10;
				}
				if ( dy == 0)
				{
					pos.y = getPosition().y;
				}
			}
			else
			{
				pos.z += dz;
			}

			// Need to set position and update box component
			setPosition(pos);
			boxComponent->onUpdateWorldTransform();
		}
	}
}
