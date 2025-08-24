#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/material/Material.h"

class MobCategory {
public:
    static MobCategory* MONSTER;
    static MobCategory* CREATURE;
    static MobCategory* AMBIENT;
    static MobCategory* WATER_CREATURE;
    static MobCategory* WOLF;
    static MobCategory* CHICKEN;
    static MobCategory* MUSHROOM_COW;
    static MobCategory* SLIME;
    static MobCategory* GUARDIAN;

    static arrayWithLength<MobCategory*> CATEGORIES;

    MobCategory(int, Material*, bool, bool, eINSTANCEOF, bool, unsigned int);

    static void staticCtor();

    void* size[3];
};
