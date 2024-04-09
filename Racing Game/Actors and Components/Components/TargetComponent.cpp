#include "TargetComponent.h"
#include "..\..\Main/Game.h"

TargetComponent::TargetComponent(Actor* owner) : Component(owner)
{
	Game::instance().getHUD()->addTargetComponent(this);
}

TargetComponent::~TargetComponent()
{
	Game::instance().getHUD()->removeTargetComponent(this);
}
