#include "Minecraft.World/entity/player/Abilities.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Nbt/CompoundTag.h"

Abilities::Abilities() {}

bool Abilities::operator==(const Abilities& abilities) const {
    if (mIsInvulnerable != abilities.mIsInvulnerable) {
        return false;
    }
    if (mIsFlying != abilities.mIsFlying) {
        return false;
    }
    if (mIsEnableFly != abilities.mIsEnableFly) {
        return false;
    }
    if (mIsInstabuild != abilities.mIsInstabuild) {
        return false;
    }
    if (mIsEnableBuild != abilities.mIsEnableBuild) {
        return false;
    }
    if (mFlySpeed == abilities.mFlySpeed)
        return mWalkSpeed == abilities.mWalkSpeed;

    return false;
}

void Abilities::addSaveData(CompoundTag* tag) {
    CompoundTag* localTag = new CompoundTag();
    localTag->putBoolean(L"invulnerable", mIsInvulnerable);
    localTag->putBoolean(L"flying", mIsFlying);
    localTag->putBoolean(L"mayfly", mIsEnableFly);
    localTag->putBoolean(L"instabuild", mIsInstabuild);
    localTag->putBoolean(L"mayBuild", mIsEnableBuild);
    localTag->putFloat(L"flySpeed", mFlySpeed);
    localTag->putFloat(L"walkSpeed", mWalkSpeed);
    tag->put(L"abilities", localTag);
}

void Abilities::loadSaveData(CompoundTag* tag) {
    if (!tag->contains(L"abilities", 10))
        return;

    CompoundTag* localTag = tag->getCompound(L"abilities");
    mIsInvulnerable = localTag->getBoolean(L"invulnerable");
    mIsFlying = localTag->getBoolean(L"flying");
    mIsEnableFly = localTag->getBoolean(L"mayfly");
    mIsInstabuild = localTag->getBoolean(L"instabuild");

    if (localTag->contains(L"flySpeed", 99)) {
        mFlySpeed = localTag->getFloat(L"flySpeed");
        mWalkSpeed = localTag->getFloat(L"walkSpeed");
    }

    if (localTag->contains(L"mayBuild", 1))
        mIsEnableBuild = localTag->getBoolean(L"mayBuild");
}

float Abilities::getFlyingSpeed() {
    return mFlySpeed;
}

void Abilities::setFlyingSpeed(float flyingSpeed) {
    mFlySpeed = flyingSpeed;
}

float Abilities::getWalkingSpeed() {
    return mWalkSpeed;
}

void Abilities::setWalkingSpeed(float walkingSpeed) {
    mWalkSpeed = walkingSpeed;
}

void Abilities::write(DataOutputStream* output) {
    output->writeBoolean(mIsInvulnerable);
    output->writeBoolean(mIsFlying);
    output->writeBoolean(mIsEnableFly);
    output->writeBoolean(mIsInstabuild);
    output->writeBoolean(mIsEnableBuild);
    output->writeFloat(mFlySpeed);
    output->writeFloat(mWalkSpeed);
}

void Abilities::read(DataInputStream* input) {
    mIsInvulnerable = input->readBoolean();
    mIsFlying = input->readBoolean();
    mIsEnableFly = input->readBoolean();
    mIsInstabuild = input->readBoolean();
    mIsEnableBuild = input->readBoolean();
    mFlySpeed = input->readFloat();
    mWalkSpeed = input->readFloat();
}
