#pragma once
#include "Actor.h"
class PlaneActor : public Actor
{
public:
	PlaneActor();
	~PlaneActor();
	class BoxComponent* getBox() const { return box; }


private:
	class BoxComponent* box;
};
