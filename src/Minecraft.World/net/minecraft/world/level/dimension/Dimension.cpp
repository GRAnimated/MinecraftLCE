#include "net/minecraft/world/level/dimension/Dimension.h"

#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/LevelType.h"
#include "net/minecraft/world/level/border/WorldBorder.h"
#include "net/minecraft/world/level/newbiome/layer/Layer.h"
#include "net/minecraft/world/level/storage/LevelData.h"

Dimension::Dimension() {
    field_28 = false;
    mIsHasCeiling = false;
    mBrightnessRamp = new float[16];
    mGeneratorOptions = nullptr;
    mLevel = nullptr;
    mIsHasSkyLight = false;
}

void Dimension::init(Level* level) {
    mLevel = level;

    updateLightRamp();
    mLevelType = level->getLevelData()->getGeneratorType();
    mGeneratorOptions = level->getLevelData()->getGeneratorOptions();

    init();
    mXZSize = level->getLevelData()->getXZSize();
}

void Dimension::updateLightRamp() {
    for (int i = 0; i != 16; i++) {
        float f2 = 1.0f - (float)i / 15.0f;
        mBrightnessRamp[i] = (1.0f - f2) / (f2 * 3.0f + 1.0f) * 1.0f + 0.0f;
    }
}

int Dimension::getMoonPhase(long long time) const {
    return (int)(time / 24000L % 8L + 8L) % 8;
}

bool Dimension::mayRespawn() const {
    return true;
}

bool Dimension::hasGround() {
    return true;
}

void* Dimension::getSpawnPos() const {
    return nullptr;
}

int Dimension::getSpawnYPosition() {
    return mLevelType == LevelType::FLAT ? 4 : 64;
}

bool Dimension::isFoggyAt(int x, int z) {
    return false;
}

bool Dimension::containsChunk(int x, int z) {
    const int xzAxis = this->getXZSize() / 2;

    return (-xzAxis <= x && x < xzAxis)
        && (-xzAxis <= z && z < xzAxis);
}

BiomeSource* Dimension::getBiomeSource() {
    return mBiomeSource;
}

bool Dimension::isHasCeiling() {
    return mIsHasCeiling;
}

float* Dimension::getBrightnessRamp() {
    return mBrightnessRamp;
}

WorldBorder* Dimension::createWorldBorder(Level* level) {
    return new WorldBorder(level);
}

int Dimension::getXZSize() {
    return mXZSize;
}

bool Dimension::canUnloadChunk(int x, int z) {
    return true;
}
