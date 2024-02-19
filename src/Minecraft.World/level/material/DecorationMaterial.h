#pragma once

#include "Minecraft.World/level/material/Material.h"

class DecorationMaterial : public Material {
public:
    DecorationMaterial(MaterialColor const* color);
    ~DecorationMaterial() override;
    bool isSolid() override;
    bool blocksLight() override;
    bool blocksMotion() override;
};