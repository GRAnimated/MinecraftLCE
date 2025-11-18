#pragma once

#include "net/minecraft/world/entity/mob/Enemy.h"
#include "net/minecraft/world/entity/mob/PathfinderMob.h"
#include "net/minecraft/world/entity/Entity.h"

class Monster : public Enemy, public PathfinderMob {
public:
    eINSTANCEOF GetType() override;
    void defineSynchedData() override;
    void readAdditionalSaveData(CompoundTag*) override;
    void addAdditonalSaveData(CompoundTag*) override;
};
