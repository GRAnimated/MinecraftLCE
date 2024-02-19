#pragma once

#include "Minecraft.World/level/material/Material.h"

class GasMaterial : public Material {
public:
    GasMaterial(MaterialColor const* color);
    ~GasMaterial() override;
    bool isSolid() override;
    bool blocksLight() override;
    bool blocksMotion() override;
};