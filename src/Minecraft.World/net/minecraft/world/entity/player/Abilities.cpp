#include "net/minecraft/world/entity/player/Abilities.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"

Abilities::Abilities() {}

bool Abilities::operator==(const Abilities& abilities) const {
    if (m_isInvulnerable != abilities.m_isInvulnerable) {
        return false;
    }
    if (m_isFlying != abilities.m_isFlying) {
        return false;
    }
    if (m_isEnableFly != abilities.m_isEnableFly) {
        return false;
    }
    if (m_isInstabuild != abilities.m_isInstabuild) {
        return false;
    }
    if (m_isEnableBuild != abilities.m_isEnableBuild) {
        return false;
    }
    if (m_flySpeed == abilities.m_flySpeed)
        return m_walkSpeed == abilities.m_walkSpeed;

    return false;
}

void Abilities::addSaveData(CompoundTag* tag) {
    CompoundTag* localTag = new CompoundTag();
    localTag->putBoolean(L"invulnerable", m_isInvulnerable);
    localTag->putBoolean(L"flying", m_isFlying);
    localTag->putBoolean(L"mayfly", m_isEnableFly);
    localTag->putBoolean(L"instabuild", m_isInstabuild);
    localTag->putBoolean(L"mayBuild", m_isEnableBuild);
    localTag->putFloat(L"flySpeed", m_flySpeed);
    localTag->putFloat(L"walkSpeed", m_walkSpeed);
    tag->put(L"abilities", localTag);
}

void Abilities::loadSaveData(CompoundTag* tag) {
    if (!tag->contains(L"abilities", 10))
        return;

    CompoundTag* localTag = tag->getCompound(L"abilities");
    m_isInvulnerable = localTag->getBoolean(L"invulnerable");
    m_isFlying = localTag->getBoolean(L"flying");
    m_isEnableFly = localTag->getBoolean(L"mayfly");
    m_isInstabuild = localTag->getBoolean(L"instabuild");

    if (localTag->contains(L"flySpeed", 99)) {
        m_flySpeed = localTag->getFloat(L"flySpeed");
        m_walkSpeed = localTag->getFloat(L"walkSpeed");
    }

    if (localTag->contains(L"mayBuild", 1))
        m_isEnableBuild = localTag->getBoolean(L"mayBuild");
}

float Abilities::getFlyingSpeed() {
    return m_flySpeed;
}

void Abilities::setFlyingSpeed(float flyingSpeed) {
    m_flySpeed = flyingSpeed;
}

float Abilities::getWalkingSpeed() {
    return m_walkSpeed;
}

void Abilities::setWalkingSpeed(float walkingSpeed) {
    m_walkSpeed = walkingSpeed;
}

void Abilities::write(DataOutputStream* output) {
    output->writeBoolean(m_isInvulnerable);
    output->writeBoolean(m_isFlying);
    output->writeBoolean(m_isEnableFly);
    output->writeBoolean(m_isInstabuild);
    output->writeBoolean(m_isEnableBuild);
    output->writeFloat(m_flySpeed);
    output->writeFloat(m_walkSpeed);
}

void Abilities::read(DataInputStream* input) {
    m_isInvulnerable = input->readBoolean();
    m_isFlying = input->readBoolean();
    m_isEnableFly = input->readBoolean();
    m_isInstabuild = input->readBoolean();
    m_isEnableBuild = input->readBoolean();
    m_flySpeed = input->readFloat();
    m_walkSpeed = input->readFloat();
}
