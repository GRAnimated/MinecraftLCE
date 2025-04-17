#pragma once

#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.World/entity/LivingEntity.h"

class DamageSource;

class Player : public LivingEntity {
    static void staticCtor();

    // dunno the type
    static std::vector<void*> sSkins;
};