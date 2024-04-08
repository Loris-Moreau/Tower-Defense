#include "CircleCollisionComponent.h"
#include "Actor.h"

CircleCollisionComponent::CircleCollisionComponent(Actor* owner) : Component(owner), radius(1.0f)
{
}

float CircleCollisionComponent::getRadius() const
{
	return owner.getScale() * radius;
}

void CircleCollisionComponent::setRadius(float radiusP)
{
	radius = radiusP;
}

const Vector2 CircleCollisionComponent::getCenter() const
{
	const Vector3 position = owner.getPosition();
	return Vector2(position.x, position.y);
}

bool Intersect(const CircleCollisionComponent& a, const CircleCollisionComponent& b)
{
	const Vector2 aCenter = a.getCenter();
	const Vector2 bCenter = b.getCenter();
	const Vector2 ab = bCenter - aCenter;
	const float distSq = ab.lengthSq();
	const float sumOfRadius = a.getRadius() + b.getRadius();
	return distSq <= sumOfRadius * sumOfRadius;
}