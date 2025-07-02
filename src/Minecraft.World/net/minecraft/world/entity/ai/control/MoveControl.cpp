#include "net/minecraft/world/entity/ai/control/MoveControl.h"

MoveControl::MoveControl(Mob* mob) : mMob(mob) {}

MoveControl::~MoveControl() {}

void MoveControl::setWantedPosition(double wantedX, double wantedY, double wantedZ, double speedModifier) {
    this->mWantedX = wantedX;
    this->mWantedY = wantedY;
    this->mWantedZ = wantedZ;
    this->mSpeedModifier = speedModifier;
    this->mOperation = 1;  // this is enum prob
}

// no one cares about this rn
// void MoveControl::tick() {}