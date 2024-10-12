#include "Minecraft.World/level/biome/Biome.h"

#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.Client/color/ColourTable.h"
#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Util/Mth.h"
#include "Minecraft.World/Random.h"
#include "Minecraft.World/level/block/FoliageColor.h"
#include "Minecraft.World/level/block/GrassColor.h"
#include "Minecraft.World/level/levelgen/feature/FlowerFeature.h"
#include "Minecraft.World/level/levelgen/synth/PerlinSimplexNoise.h"
#include "Minecraft.World/level/material/MaterialColor.h"

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

Biome** Biome::getBiomes() {
    return BIOMES;
}

Biome* Biome::getBiome(int id) {
    return getBiome(id, nullptr);
}

Biome* Biome::getBiome(int id, Biome* biome) {
    if ((unsigned int)id > EBiomeIDs::LIMIT)  // cast required for match
        return OCEAN;
    if (BIOMES[id])
        return BIOMES[id];
    return biome;
}

Block* Biome::getRandomFlower(Random& random, const BlockPos* pos) {
    if (random.nextInt(3) > 0)
        return (Block*)FlowerBlock::Flower::YELLOW_FLOWER;
    return (Block*)FlowerBlock::Flower::RED_FLOWER;
}

unsigned int Biome::getSkyColor(float timeOfDay) {
    if (Minecraft::GetInstance()->isUsingDefaultSkin()) {
        float f1 = Mth::clamp(timeOfDay / 3.0f, -1.0f, 1.0f);
        return Mth::hsvToRgb((f1 * -0.05f) + 0.62222f, (f1 * 0.1f) + 0.5f, 1.0f);
    }
    ColourTable* colourTable = Minecraft::GetInstance()->getColourTable();
    return colourTable->getColour(mSkyColor);
}

bool Biome::hasSnow() {
    return isSnowCovered();
}

bool Biome::hasRain() {
    return !isSnowCovered() && mIsDry;
}

bool Biome::isHumid() {
    return getDownfall() > 0.85f;
}

float Biome::getCreatureProbability() {
    return 0.1f;
}

float Biome::getTemperature(const BlockPos* pos) {
    if (pos->getY() > 64) {
        float noise = TEMPERATURE_NOISE->getValue(pos->getX() * 0.125f, pos->getZ() * 0.125f) * 4.0;
        return getTemperature() + (noise + pos->getY() + -64.0f) * -0.05f / 30.0f;
    }
    return getTemperature();
}

unsigned int Biome::getGrassColor(const BlockPos* pos) {
    return GrassColor::get(Mth::clamp(getTemperature(pos), 0.0f, 1.0f), Mth::clamp(getDownfall(), 0.0f, 1.0f));
}

unsigned int Biome::getFoliageColor(const BlockPos* pos) {
    return FoliageColor::get(Mth::clamp(getTemperature(pos), 0.0f, 1.0f), Mth::clamp(getDownfall(), 0.0f, 1.0f));
}

void Biome::setGrassColor(const BlockPos* pos, unsigned int color) {
    double temperature = Mth::clamp(getTemperature(pos), 0.0f, 1.0f);
    double downfall = Mth::clamp(getDownfall(), 0.0f, 1.0f);
    GrassColor::set(temperature, downfall, color);
}

void Biome::setFoliageColor(const BlockPos* pos, unsigned int color) {
    double temperature = Mth::clamp(getTemperature(pos), 0.0f, 1.0f);
    double downfall = Mth::clamp(getDownfall(), 0.0f, 1.0f);
    FoliageColor::set(temperature, downfall, color);
}

int Biome::getTemperatureCategory() {
    float temperature = getTemperature();
    if (temperature < 0.2)
        return 1;
    if (temperature < 1.0f)
        return 2;
    return 3;
}

bool Biome::isAlwaysValidSpawn() {
    return false;
}

void Biome::getWaterColor() {
    Minecraft* minecraft = Minecraft::GetInstance();
    ColourTable* colourTable = minecraft->getColourTable();
    colourTable->getColour(mWaterColor);
}

Vec3 Biome::getFogColor(float a2, float a3) const {
    float v3 = Mth::cos(a2 * 3.1415927f * 2.0f);
    float v4 = std::min(std::max((v3 + v3) + 0.5f, 0.0f), 1.0f);

    unsigned int color = Minecraft::GetInstance()->getColourTable()->getColour(Default_Fog_Colour);

    float f1 = (color >> 16 & 0xFF) / 255.0f;
    float f2 = (color >> 8 & 0xFF) / 255.0f;
    float f3 = (color & 0xFF) / 255.0f;

    f1 *= (v4 * 0.94f) + 0.06f;
    f2 *= (v4 * 0.94f) + 0.06f;
    f3 *= (v4 * 0.91f) + 0.09f;

    return Vec3::newTemp(f1, f2, f3);
}

bool Biome::isFoggy() {
    return false;
}

bool Biome::isNatural() {
    return true;
}

bool Biome::isSnowCovered() {
    return mIsSnow;
}
