#include "Minecraft.World/level/levelgen/CustomizableSourceSettings.h"

CustomizableSourceSettings::Builder::Builder() {
    setDefaults();
}

// NON_MATCHING: Different order
void CustomizableSourceSettings::Builder::setDefaults() {
    waterLakeChance = 4;
    lavaLakeChance = 80;
    fixedBiome = -1;
    biomeSize = 4;
    coordinateScale = 684.41;
    heightScale = 684.41;
    lowerLimitScale = 512.0;
    upperLimitScale = 512.0;
    depthNoiseScaleX = 200.0;
    depthNoiseScaleZ = 200.0;
    riverSize = 4;
    dirtSize = 33;
    dirtCount = 10;
    dirtMinHeight = 0;
    graniteCount = 10;
    graniteMinHeight = 0;
    dioriteCount = 10;
    dioriteMinHeight = 0;
    andesiteCount = 10;
    andesiteMinHeight = 0;
    depthNoiseScaleExponent = 0.5;
    mainNoiseScaleX = 80.0;
    andesiteMaxHeight = 80;
    coalSize = 17;
    mainNoiseScaleY = 160.0;
    mainNoiseScaleZ = 80.0;
    coalCount = 20;
    coalMinHeight = 0;
    ironCount = 20;
    ironMinHeight = 0;
    baseSize = 8.5;
    stretchY = 12.0;
    dirtMaxHeight = 128;
    gravelSize = 33;
    gravelMaxHeight = 128;
    graniteSize = 33;
    dungeonChance = 8;
    gravelCount = 8;
    gravelMinHeight = 0;
    ironMaxHeight = 64;
    goldSize = 9;
    redstoneCount = 8;
    redstoneMinHeight = 0;
    biomeDepthWeight = 1.0;
    biomeDepthOffset = 0.0;
    biomeScaleWeight = 1.0;
    biomeScaleOffset = 0.0;
    graniteMaxHeight = 80;
    dioriteSize = 33;
    dioriteMaxHeight = 80;
    andesiteSize = 33;
    goldCount = 2;
    goldMinHeight = 0;
    seaLevel = 63;
    redstoneMaxHeight = 16;
    diamondSize = 8;
    useCaves = 1;
    useDungeons = 1;
    byte_4C = 1;
    byte_4D = 1;
    byte_4E = 1;
    byte_4F = 1;
    byte_50 = 1;
    byte_51 = 1;
    byte_52 = 1;
    useWaterLakes = 1;
    useLavaLakes = 1;
    useLavaOceans = 0;
    coalMaxHeight = 128;
    ironSize = 9;
    goldMaxHeight = 32;
    redstoneSize = 8;
    diamondCount = 1;
    diamondMinHeight = 0;
    diamondMaxHeight = 16;
    lapisSize = 7;
    lapisCount = 1;
    lapisCenterHeight = 16;
    lapisSpread = 16;
}

CustomizableSourceSettings::Builder* CustomizableSourceSettings::Builder::fromString(SuperflatConfig* config) {
    return new Builder();
}

CustomizableSourceSettings* CustomizableSourceSettings::Builder::build() {
    return new CustomizableSourceSettings(this);
}

// NON_MATCHING: Shouldn't inline
CustomizableSourceSettings::CustomizableSourceSettings(CustomizableSourceSettings::Builder* builder) : mBuilder(*builder) {}
