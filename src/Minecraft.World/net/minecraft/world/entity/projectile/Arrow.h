#pragma once
#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.World/entity/projectile/Projectile.h"

class Arrow : public Entity, public Projectile {
public:
    void setCritArrow(bool);
};