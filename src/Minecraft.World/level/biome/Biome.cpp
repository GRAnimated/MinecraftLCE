#include "Minecraft.World/level/biome/Biome.h"

// NON_MATCHING
Biome::BiomeProperties::BiomeProperties(const std::wstring& name) : mBiomeName(name) {}

void Biome::BiomeProperties::depth(float depth) {
    mDepth = depth;
}

void Biome::BiomeProperties::downfall(float downfall) {
    mDownfall = downfall;
}

void Biome::BiomeProperties::dry() {
    mIsNotDry = false;
}

Biome::BiomeProperties* Biome::BiomeProperties::mutated(const std::wstring& mutatedName) {
    mMutatedBiomeName = mutatedName;
    return this;
}

void Biome::BiomeProperties::scale(float scale) {
    mScale = scale;
}

void Biome::BiomeProperties::snow() {
    mIsSnow = true;
}

void Biome::BiomeProperties::temperature(float temperature) {
    mTemperature = temperature;
}

void Biome::BiomeProperties::waterColor(int waterColor) {
    mWaterColor = waterColor;
}
