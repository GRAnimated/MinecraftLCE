#pragma once

#include "Minecraft.World/level/material/Material.h"

class PortalMaterial : public Material {
public:
    PortalMaterial(MaterialColor const* color);
    ~PortalMaterial() override;
    bool isSolid() override;
    bool blocksLight() override;
    bool blocksMotion() override;
};