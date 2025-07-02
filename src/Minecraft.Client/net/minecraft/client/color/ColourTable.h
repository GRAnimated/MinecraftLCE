#pragma once

#include "Minecraft.World/level/material/MaterialColor.h"

class ColourTable {
public:
    static void staticCtor();
    unsigned int getColour(eMinecraftColour);
};
