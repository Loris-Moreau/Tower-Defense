#pragma once

#include "Actor.h"

class Component;

class Car : public Actor
{
public:
	Car(Actor* ownerP, int updateOrderP = 100);

	void processInput(const Uint8* keyState) override;
	void update(float dt) override;
};
