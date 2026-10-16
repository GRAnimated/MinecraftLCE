#include "net/minecraft/util/Mth.h"
#include <cmath>

MthLong Mth::round(double value) {
    return static_cast<MthLong>(std::floor(value + 0.5));
}
