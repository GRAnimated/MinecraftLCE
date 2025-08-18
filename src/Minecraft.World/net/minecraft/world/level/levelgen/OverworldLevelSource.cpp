#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/levelgen/OverworldLevelSource.h"
#include "net/minecraft/world/level/levelgen/feature/LargeCaveFeature.h"
#include "net/minecraft/world/level/levelgen/feature/StrongholdFeature.h"
#include "net/minecraft/world/level/storage/LevelData.h"

OverworldLevelSource::OverworldLevelSource(Level* level, long long seed, bool generateStructures,
                                           SuperflatConfig* sourceSettings) {
    level->getLevelData()->fillMoatValues(&mIsClassicMoat, &mIsSmallMoat, &mIsMediumMoat);

    mSize = level->getLevelData()->getXZSize();
    mLevel = level;
    mShouldGenerateStructures = generateStructures;
    mGeneratorType = level->getLevelData()->getGeneratorType();

    mCaveFeature = new LargeCaveFeature();
    // mStrongholdFeature = new StrongholdFeature();
    // mVillageFeature
}

// NON_MATCHING | Score: 2915 (lower is better)
float OverworldLevelSource::getHeightFalloff(int x, int z, int* distance) {
    int size = 16 * this->mSize;
    int res = unkMethod(32.0f, this, x, z, size);

    if (this->mIsClassicMoat && size > 864) {
        int n = unkMethod(32.0f, this, x, z, 864);
        if (n < res)
            res = n;
    }

    if (this->mIsSmallMoat && size > 1024) {
        int n = unkMethod(32.0f, this, x, z, 1024);
        if (n < res)
            res = n;
    }

    if (this->mIsMediumMoat && size > 3072) {
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
