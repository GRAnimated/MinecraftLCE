#pragma once

#include "Minecraft.World/level/material/Material.h"

class PortalMaterial : public Material {
public:
    PortalMaterial(const MaterialColor* color);
    ~PortalMaterial() override;
    bool isSolid() override;
    bool blocksLight() override;
    bool blocksMotion() override;
};