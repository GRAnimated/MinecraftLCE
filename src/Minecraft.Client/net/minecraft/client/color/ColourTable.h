#pragma once

#include "net/minecraft/world/level/material/MaterialColor.h"

class ColourTable {
public:
    static void staticCtor();
    unsigned int getColour(eMinecraftColour);
};
