#pragma once

#include "net/minecraft/world/entity/Entity.h"

class EnderCrystal : public Entity {
public:
    EnderCrystal(Level* level, double x, double y, double z);

    void setShowBottom(bool show);

    eINSTANCEOF GetType() override;
    void defineSynchedData() override;
    void readAdditionalSaveData(CompoundTag*) override;
    void addAdditonalSaveData(CompoundTag*) override;

    void* fill;
};
