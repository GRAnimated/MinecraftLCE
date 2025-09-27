#pragma once
#include "BossMob.h"
#include "Enemy.h"
#include "Mob.h"
#include "MultiEntityMob.h"

// ENTITY STUB
class EnderDragon : public Mob, public BossMob, public MultiEntityMob, public Enemy {
public:
    static void staticCtor();
};