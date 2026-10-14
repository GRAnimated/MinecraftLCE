#include "net/minecraft/util/Mth.h"

int Mth::floor(double value) {
    return (int)value - ((int)value > value);
}

int Mth::floor(float value) {
    return (int)value - ((int)value > value);
}
