#pragma once

#include "Minecraft.World/level/material/Material.h"

class GasMaterial : public Material {
public:
    GasMaterial(const MaterialColor* color);
    ~GasMaterial() override;
    bool isSolid() override;
    bool blocksLight() override;
    bool blocksMotion() override;
};