#pragma once

#include "Minecraft.World/item/Item.h"

class ArmorStandItem : public Item {
public:
    ArmorStandItem();    

    virtual ActionResultType useOn(std::shared_ptr<Player> user, Level* level, const BlockPos& pos,
        InteractionHand::EInteractionHand hand, const Direction* direction,
        float rayX, float rayY, float rayZ,
        bool missOrInside) override; 
};