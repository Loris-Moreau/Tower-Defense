#pragma once

#include "Actor.h"
#include "BoxComponent.h"

class EndGame : public Actor
{
public:
    EndGame();
    ~EndGame();
    
    class BoxComponent* getBox() {return box;}

private:
    class BoxComponent* box;
};
