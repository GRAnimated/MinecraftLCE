#include "net/minecraft/util/Mth.h"

int Mth::floor(double value) {
    return (int)value - ((int)value > value);
}
