#pragma once

#include "Actor.h"
#include "BoxComponent.h"

class TheEnd : public Actor
{
public:
    TheEnd();
    ~TheEnd();
    
    class BoxComponent* getBox() {return box;}

private:
    class BoxComponent* box;
};
