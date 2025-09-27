#pragma once

#include "AgableMob.h"
#include "net/minecraft/world/entity/NPC.h"
#include "net/minecraft/world/item/trading/Merchant.h"

// ENTITY STUB
class Villager : public AgableMob, public NPC, public Merchant {
public:
    static void staticCtor();
};
