#include "Component.h"
#include "..\Actors\Actor.h"
#include "..\..\Inputs\InputSystem.h"

Component::Component(Actor* ownerP, int updateOrderP):
	owner(*ownerP),
	updateOrder(updateOrderP)
{
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
}

void Component::processInput(const InputState& inputState)
{
}

void Component::update(float dt)
{
}
