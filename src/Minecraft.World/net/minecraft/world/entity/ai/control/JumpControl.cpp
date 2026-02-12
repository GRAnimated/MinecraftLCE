#include "net/minecraft/world/entity/ai/control/JumpControl.h"

#include "net/minecraft/world/entity/mob/Mob.h"

JumpControl::JumpControl(Mob* mob) {
    this->m_mob = mob;
}

JumpControl::~JumpControl() {}

void JumpControl::tick() {
    this->m_mob->setJumping(this->m_jumping);
    this->m_jumping = false;
}
