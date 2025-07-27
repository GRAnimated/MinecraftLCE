#pragma once

#include "net/minecraft/world/item/Item.h"

class LeadItem : public Item {
public:
    static bool bindPlayerMobsTest(std::shared_ptr<Player> player, Level* level, const BlockPos& pos);
};
