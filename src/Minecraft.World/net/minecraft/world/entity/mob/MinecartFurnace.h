#pragma once

#include "net/minecraft/world/entity/mob/Minecart.h"

class MinecartFurnace : public Minecart {
public:
    static void staticCtor();

    double getMaxSpeed() override;
    void moveAlongTrack(const BlockPos&, const BlockState*) override;
    void applyNaturalSlowdown() override;

    int m_fuel;
    double m_pushX;
    double m_pushZ;
};

ASSERT_SIZEOF(MinecartFurnace, 0x320)
