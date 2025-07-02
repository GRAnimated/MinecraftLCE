#pragma once

#include "Minecraft.World/level/material/Material.h"

class LiquidMaterial : public Material {
public:
    LiquidMaterial(const MaterialColor* color);
    ~LiquidMaterial() override;
    bool isLiquid() override;
    bool isSolid() override;
    bool blocksMotion() override;
};