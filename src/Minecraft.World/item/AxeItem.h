#pragma once

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/item/DiggerItem.h"

class AxeItem : public DiggerItem {
public:
    static arrayWithLength<Block*> DIGGABLES;

    static void staticCtor();

    AxeItem(const Item::Tier*);

    ~AxeItem() override;
    float getDestroySpeed(not_null_ptr<ItemInstance>, BlockState*) override;
};