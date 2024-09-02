#include "Minecraft.World/entity/player/Abilities.h"
#include "Minecraft.Nbt/CompoundTag.h"

Abilities::Abilities() {}

bool Abilities::operator==(const Abilities& abilities) const {
    if (isInvulnerable != abilities.isInvulnerable) {
        return false;
    }
    if (isFlying != abilities.isFlying) {
        return false;
    }
    if (isEnableFly != abilities.isEnableFly) {
        return false;
    }
    if (isInstabuild != abilities.isInstabuild) {
        return false;
    }
    if (isEnableBuild != abilities.isEnableBuild) {
        return false;
    }
    if (flySpeed == abilities.flySpeed)
        return walkSpeed == abilities.walkSpeed;

    return false;
}

void Abilities::addSaveData(CompoundTag* compoundTag) {
    CompoundTag* localTag = new CompoundTag();
    localTag->putBoolean(L"invulnerable", isInvulnerable);
    localTag->putBoolean(L"flying", isFlying);
    localTag->putBoolean(L"mayfly", isEnableFly);
    localTag->putBoolean(L"instabuild", isInstabuild);
    localTag->putBoolean(L"mayBuild", isEnableBuild);
    localTag->putFloat(L"flySpeed", flySpeed);
    localTag->putFloat(L"walkSpeed", walkSpeed);
    compoundTag->put(L"abilities", localTag);
}