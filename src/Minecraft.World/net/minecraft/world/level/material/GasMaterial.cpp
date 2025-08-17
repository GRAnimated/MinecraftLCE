#include "net/minecraft/world/level/material/GasMaterial.h"

GasMaterial::GasMaterial(const MaterialColor* color) : Material(color) {
    replaceable();
}

bool GasMaterial::isSolid() {
    return false;
}

bool GasMaterial::blocksLight() {
    return false;
}

bool GasMaterial::blocksMotion() {
    return false;
}
