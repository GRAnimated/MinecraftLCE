#include "Minecraft.World/level/material/LiquidMaterial.h"

LiquidMaterial::LiquidMaterial(MaterialColor const* color) : Material(color) {
    replaceable()->destroyOnPush();
}

bool LiquidMaterial::isLiquid() {
    return true;
}

bool LiquidMaterial::isSolid() {
    return false;
}

bool LiquidMaterial::blocksMotion() {
    return false;
}
