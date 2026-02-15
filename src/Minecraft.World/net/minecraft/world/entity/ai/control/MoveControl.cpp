#include "net/minecraft/world/entity/ai/control/MoveControl.h"

MoveControl::MoveControl(Mob* mob) : m_mob(mob) {}

MoveControl::~MoveControl() {}

void MoveControl::setWantedPosition(double wantedX, double wantedY, double wantedZ, double speedModifier) {
    this->m_wantedX = wantedX;
    this->m_wantedY = wantedY;
    this->m_wantedZ = wantedZ;
    this->m_speedModifier = speedModifier;
    this->m_operation = 1;  // this is enum prob
}

// no one cares about this rn
// void MoveControl::tick() {}
