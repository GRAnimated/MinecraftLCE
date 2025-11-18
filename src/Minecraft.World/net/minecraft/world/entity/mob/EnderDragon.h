#pragma once

#include "net/minecraft/world/entity/mob/Enemy.h"
#include "net/minecraft/world/entity/mob/BossMob.h"
#include "net/minecraft/world/entity/mob/Mob.h"
#include "net/minecraft/world/entity/mob/MultiEntityMob.h"

// ENTITY STUB
class EnderDragon : public Mob, public BossMob, public MultiEntityMob, public Enemy {
public:
    static void staticCtor();
};
