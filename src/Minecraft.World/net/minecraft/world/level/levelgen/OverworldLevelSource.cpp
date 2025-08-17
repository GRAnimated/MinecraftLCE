#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/levelgen/OverworldLevelSource.h"
#include "net/minecraft/world/level/levelgen/feature/LargeCaveFeature.h"
#include "net/minecraft/world/level/levelgen/feature/StrongholdFeature.h"
#include "net/minecraft/world/level/storage/LevelData.h"

OverworldLevelSource::OverworldLevelSource(Level* level, long long seed, bool generateStructures,
                                           SuperflatConfig* sourceSettings) {
    level->getLevelData()->fillMoatValues(&mIsClassicMoat, &mIsSmallMoat, &mIsMediumMoat);

    mXZSize2 = level->getLevelData()->getXZSize();
    mLevel = level;
    mShouldGenerateStructures = generateStructures;
    mGeneratorType = level->getLevelData()->getGeneratorType();

    mCaveFeature = new LargeCaveFeature();
    // mStrongholdFeature = new StrongholdFeature();
    // mVillageFeature
}
