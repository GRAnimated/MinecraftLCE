#include "Minecraft.World/level/material/WebMaterial.h"

WebMaterial::WebMaterial(const MaterialColor* color) : Material(color) {}

bool WebMaterial::blocksMotion() {
    return false;
}