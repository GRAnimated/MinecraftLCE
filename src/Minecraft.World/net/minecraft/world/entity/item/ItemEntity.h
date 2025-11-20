#pragma once

#include "net/minecraft/world/entity/Entity.h"
#include <string>

class ItemEntity : public Entity {
public:
    ItemEntity(Level*, double, double, double, not_null_ptr<ItemInstance>);

    eINSTANCEOF GetType() override;
    void defineSynchedData() override;
    void readAdditionalSaveData(CompoundTag*) override;
    void addAdditonalSaveData(CompoundTag*) override;

    void setNoPickUpDelay();
    void setOwner(const std::wstring&);
    void makeFakeItem();

    static void staticCtor();

    void* padding[8];
};
