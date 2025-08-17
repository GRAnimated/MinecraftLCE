#pragma once

#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/item/DiggerItem.h"

class ShovelItem : public DiggerItem {
public:
    static arrayWithLength<Block*> DIGGABLES;

    static void staticCtor();

    ShovelItem(const Item::Tier*);

    ~ShovelItem() override {}
    ActionResultType useOn(std::shared_ptr<Player>, Level*, const BlockPos&,
                           InteractionHand::EInteractionHand, const Direction*, float, float, float,
                           bool) override;
    bool canDestroySpecial(const BlockState*) override;
};
