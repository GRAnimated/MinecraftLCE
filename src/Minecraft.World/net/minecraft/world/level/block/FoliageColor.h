#pragma once
#include "Minecraft.World/ArrayWithLength.h"

class FoliageColor {
public:
    static int get(double, double);
    static int set(double, double, unsigned int);

    static void init(arrayWithLength<int> pixels);
};
