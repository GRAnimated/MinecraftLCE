#pragma once

#include "net/minecraft/world/level/material/Material.h"

class WebMaterial : public Material {
public:
    WebMaterial(const MaterialColor* color);
    ~WebMaterial() override;
    bool blocksMotion() override;
};