#pragma once
#include "Actor.h"
class FollowActor : public Actor
{
public:
	FollowActor();

	void actorInput(const InputState& inputState) override;
	void updateActor(float dt) override;
	void setVisible(bool isVisibleP);
	void setSpeed(float speedP);
	void shoot();
	void fixCollisions();

private:
	class MoveComponent* moveComponent;
	class FollowCameraComponent* cameraComponent;
	class MeshComponent* meshComponent;
	class BoxComponent* boxComponent;
	float speed;
};
