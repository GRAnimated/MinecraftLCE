#include "Minecraft.World/level/material/DecorationMaterial.h"

DecorationMaterial::DecorationMaterial(MaterialColor const* color) : Material(color) {
    makeDestroyedByHand();
}

bool DecorationMaterial::isSolid() {
    return false;
}

bool DecorationMaterial::blocksLight() {
    return false;
}

bool DecorationMaterial::blocksMotion() {
    return false;
}