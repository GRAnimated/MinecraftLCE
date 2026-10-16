#include "net/minecraft/util/Mth.h"

int Mth::ceil(float value) {
    int truncated = static_cast<int>(value);
    return truncated + (truncated < value);
}
