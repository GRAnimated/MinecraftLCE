#pragma once
#include "Minecraft.World/ArrayWithLength.h"

class GrassColor {
public:
    static int get(double, double);
    static int set(double, double, unsigned int);

    static void init(arrayWithLength<int> pixels);
};
