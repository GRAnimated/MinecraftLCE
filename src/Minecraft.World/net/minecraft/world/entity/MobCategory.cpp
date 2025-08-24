#include "net/minecraft/world/entity/MobCategory.h"

void MobCategory::staticCtor() {
    MONSTER = new MobCategory(70, Material::AIR, 0, 0, eMonster, 0, 50);
    CREATURE = new MobCategory(10, Material::AIR, 1, 1, eCreature, 0, 50);
    AMBIENT = new MobCategory(15, Material::AIR, 1, 0, eAmbientCreature, 0, 20);
    WATER_CREATURE = new MobCategory(5, Material::WATER, 1, 0, eWaterCreature, 0, 30);
    CATEGORIES[0] = MONSTER;
    CATEGORIES[1] = CREATURE;
    CATEGORIES[2] = AMBIENT;
    CATEGORIES[3] = WATER_CREATURE;

    WOLF = new MobCategory(3, Material::AIR, 1, 1, eWolf, 1, 8);
    CHICKEN = new MobCategory(2, Material::AIR, 1, 1, eChicken, 1, 8);
    MUSHROOM_COW = new MobCategory(2, Material::AIR, 1, 1, eMushroomCow, 1, 2);
    SLIME = new MobCategory(15, Material::AIR, 0, 0, eSlime, 1, 25);
    GUARDIAN = new MobCategory(25, Material::WATER, 0, 0, eGuardian, 1, 35);
    CATEGORIES[4] = WOLF;
    CATEGORIES[5] = CHICKEN;
    CATEGORIES[6] = MUSHROOM_COW;
    CATEGORIES[7] = SLIME;
    CATEGORIES[8] = GUARDIAN;
}
