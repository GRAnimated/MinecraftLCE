#include "net/minecraft/world/entity/ai/control/JumpControl.h"

#include "net/minecraft/world/entity/mob/Mob.h"

JumpControl::JumpControl(Mob* mob) {
    this->mMob = mob;
}

JumpControl::~JumpControl() {}

void JumpControl::tick() {
    this->mMob->setJumping(this->mJumping);
    this->mJumping = false;
}