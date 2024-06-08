#pragma once

#include "Actor.h"
#include "BoxComponent.h"

class Teleporter : public Actor
{
public:
    Teleporter();
    ~Teleporter();
    
    class BoxComponent* getBox() {return box;}

private:
    class BoxComponent* box;
};
