#pragma once
#include "Actor.h"
#include "BoxComponent.h"

class Door : public Actor
{
public:
    Door();
    ~Door();
    
    class BoxComponent* getBox() {return box;}
    void openDoor();
    bool getStateDoor() {return isOpen;}
    void setStateDoor(bool pisOpen);
    void updateActor(float dt) override;

private:
    class BoxComponent* box;
    bool isOpen = false;
};
