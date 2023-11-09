#include "Component.h"
#include "Actor.h"

#include <stdexcept>

Component::Component(Actor* ownerP, int updateOrderP)
	: owner(*(ownerP ? ownerP : throw std::invalid_argument("ownerP is nullptr"))), updateOrder(updateOrderP)
{
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
}

void Component::processInput(const Uint8* keyState)
{

}

void Component::update(float dt)
{

}
