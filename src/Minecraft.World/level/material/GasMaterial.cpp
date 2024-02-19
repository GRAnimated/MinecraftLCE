#include "Minecraft.World/level/material/GasMaterial.h"

GasMaterial::GasMaterial(MaterialColor const* color) : Material(color) {
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