#pragma once

#include "net/minecraft/world/level/material/Material.h"

class GasMaterial : public Material {
public:
    GasMaterial(const MaterialColor* color);
    ~GasMaterial() override {}
    bool isSolid() override;
    bool blocksLight() override;
    bool blocksMotion() override;
};
