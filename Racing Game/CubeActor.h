#pragma once
#include "Actor.h"
#include <xstring>

class BallActor;

class CubeActor : public Actor
{
public:
	CubeActor();
	CubeActor(std::string spriteNameP);
	void setSpriteName(const char* spriteNameP){ spriteName = spriteNameP; }
	void updateActor(float dt) override;
	class CubeMoveComponent* cubeMove;
	void hitBall(BallActor* ball);
	void hitPins(CubeActor* pins);
	void setArrow(Actor* arrow);

private:
	float lifetimeSpan;
	bool gotHit;
	std::string spriteName;
};
