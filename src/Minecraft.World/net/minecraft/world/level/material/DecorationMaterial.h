#pragma once

#include "net/minecraft/world/level/material/Material.h"

class DecorationMaterial : public Material {
public:
    DecorationMaterial(const MaterialColor* color);
    ~DecorationMaterial() override;
    bool isSolid() override;
    bool blocksLight() override;
    bool blocksMotion() override;
};