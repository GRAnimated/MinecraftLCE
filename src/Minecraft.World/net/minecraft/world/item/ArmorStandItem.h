#pragma once

#include "net/minecraft/world/item/Item.h"

class ArmorStandItem : public Item {
public:
    ArmorStandItem();
    ~ArmorStandItem() override;

    ActionResultType useOn(std::shared_ptr<Player> user, Level* level, const BlockPos& pos,
                           InteractionHand::EInteractionHand hand, const Direction* direction, float rayX,
                           float rayY, float rayZ, bool missOrInside) override;
};