#include "net/minecraft/world/level/dimension/Dimension.h"

#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/LevelType.h"
#include "net/minecraft/world/level/border/WorldBorder.h"
#include "net/minecraft/world/level/newbiome/layer/Layer.h"
#include "net/minecraft/world/level/storage/LevelData.h"

Dimension::Dimension() {
    m_field28 = false;
    m_isHasCeiling = false;
    m_brightnessRamp = new float[16];
    m_generatorOptions = nullptr;
    m_level = nullptr;
    m_isHasSkyLight = false;
}

void Dimension::init(Level* level) {
    m_level = level;

    updateLightRamp();
    m_levelType = level->getLevelData()->getGeneratorType();
    m_generatorOptions = level->getLevelData()->getGeneratorOptions();

    init();
    m_xzSize = level->getLevelData()->getXZSize();
}

void Dimension::updateLightRamp() {
    for (int i = 0; i != 16; i++) {
        float f2 = 1.0f - (float)i / 15.0f;
        m_brightnessRamp[i] = (1.0f - f2) / (f2 * 3.0f + 1.0f) * 1.0f + 0.0f;
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
    return m_levelType == LevelType::FLAT ? 4 : 64;
}

bool Dimension::isFoggyAt(int x, int z) {
    return false;
}

BiomeSource* Dimension::getBiomeSource() {
    return m_biomeSource;
}

bool Dimension::isHasCeiling() {
    return m_isHasCeiling;
}

float* Dimension::getBrightnessRamp() {
    return m_brightnessRamp;
}

WorldBorder* Dimension::createWorldBorder(Level* level) {
    return new WorldBorder(level);
}

int Dimension::getXZSize() {
    return m_xzSize;
}

bool Dimension::canUnloadChunk(int x, int z) {
    return true;
}
