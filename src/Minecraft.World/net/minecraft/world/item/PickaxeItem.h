#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/item/DiggerItem.h"

class PickaxeItem : public DiggerItem {
public:
    static arrayWithLength<Block*> DIGGABLES;

    static void staticCtor();

    PickaxeItem(const Item::Tier* tier);

    ~PickaxeItem() override {}

    float getDestroySpeed(not_null_ptr<ItemInstance> itemInstance, BlockState* state) override;
    bool canDestroySpecial(const BlockState* state) override;
};
