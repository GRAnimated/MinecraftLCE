#pragma once
#include "Minecraft.World/phys/Vec3.h"

class AABB {
public:
    Vec3 min;
    Vec3 max;

    static AABB* newPermanent(double, double, double, double, double, double);

    static AABB* sCrossShape;  // .got:000000710176F5E0
};
