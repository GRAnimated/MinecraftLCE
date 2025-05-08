#include "Minecraft.World/entity/ai/control/JumpControl.h"

#include "Minecraft.World/entity/mob/Mob.h"

JumpControl::JumpControl(Mob* mob) {
    this->mMob = mob;
}

JumpControl::~JumpControl() {}

void JumpControl::tick() {
    this->mMob->setJumping(this->mJumping);
    this->mJumping = false;
}