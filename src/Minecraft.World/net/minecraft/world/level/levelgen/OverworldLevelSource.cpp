#include "net/minecraft/world/level/levelgen/GenericOverworldLevelSource.h"

// NON_MATCHING | Score: 2915 (lower is better)
float OverworldLevelSource::getHeightFalloff(int x, int z, int* distance) {
    int size = 16 * this->mSize;
    int res = unkMethod(32.0f, this, x, z, size);

    if (this->mIsLevelClassic && size > 864) {
        int n = unkMethod(32.0f, this, x, z, 864);
        if (n < res)
            res = n;
    }

    if (this->mIsLevelSmall && size > 1024) {
        int n = unkMethod(32.0f, this, x, z, 1024);
        if (n < res)
            res = n;
    }

    if (this->mIsLevelMedium && size > 3072) {
        int n = unkMethod(32.0f, this, x, z, 3072);
        if (n < res)
            res = n;
    }

    *distance = res;

    if (res >= 32) {
        return 0.0;
    } else {
        return (32 - res) * 0.03125f * 128.0f;
    }
}
