#include "net/minecraft/world/level/material/DecorationMaterial.h"

DecorationMaterial::DecorationMaterial(const MaterialColor* color) : Material(color) {
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
