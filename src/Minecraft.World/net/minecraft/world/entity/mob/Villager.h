#pragma once

#include "net/minecraft/world/item/trading/Merchant.h"
#include "AgableMob.h"
#include "net/minecraft/world/entity/NPC.h"

// ENTITY STUB
class Villager : public AgableMob, public NPC, public Merchant {
public:
    static void staticCtor();
};
