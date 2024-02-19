#pragma once

#include "Minecraft.World/level/material/Material.h"

class WebMaterial : public Material {
public:
    WebMaterial(MaterialColor const* color);
    ~WebMaterial() override;
    bool blocksMotion() override;
};