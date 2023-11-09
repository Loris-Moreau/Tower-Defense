#pragma once

#include "Actor.h"

class Track : public Actor
{
public:
    Track(Actor* ownerP, int updateOrderP);

    void update(float dt) override;
};
