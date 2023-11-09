#pragma once

#include "Actor.h"

class Component;

class Car : public Actor
{
public:
	Car();

	void processInput(const Uint8* keyState);
	void update(float dt);
};
