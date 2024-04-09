#include "Camera.h"
#include "..\Components/MoveComponent.h"
#include "..\..\Main/Game.h"

Camera::Camera() : Actor(), moveComponent(nullptr)
{
	moveComponent = new MoveComponent(this);
}

void Camera::updateActor(float deltaTime)
{
	Actor::updateActor(deltaTime);

	// Compute new camera from this actor
	const Vector3 cameraPos = getPosition();
	const Vector3 target = getPosition() + getForward() * 100.0f;
	const Vector3 up = Vector3::unitZ;

	const Matrix4 view = Matrix4::createLookAt(cameraPos, target, up);
	getGame().getRenderer().setViewMatrix(view);
}

void Camera::actorInput(const InputState& inputState)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W))
	{
		forwardSpeed += 300.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S))
	{
		forwardSpeed -= 300.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		angularSpeed -= Maths::twoPi;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		angularSpeed += Maths::twoPi;
	}

	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setAngularSpeed(angularSpeed);
}