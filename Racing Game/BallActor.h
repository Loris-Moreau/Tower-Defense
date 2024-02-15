#pragma once

#include "Actor.h"
#include "CubeActor.h"
#include "PlaneActor.h"

class BallActor : public Actor
{
public:
	BallActor();

	void updateActor(float dt) override;
	void setPlayer(Actor* player);

	//hit functions
	void hitTarget(CubeActor* target);
	void hitPlane(PlaneActor* actor);

private:
	//class AudioComponent* audio;
	class BallMoveComponent* ballMove;
	float lifetimeSpan;
};

