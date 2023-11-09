#pragma once

#include "Actor.h"
#include "Component.h"

class Track : public Actor
{
public:
    Track();

    void update(float dt);
};
