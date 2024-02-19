#include "Minecraft.World/level/material/WebMaterial.h"

WebMaterial::WebMaterial(MaterialColor const* color) : Material(color) {}

bool WebMaterial::blocksMotion() {
    return false;
}