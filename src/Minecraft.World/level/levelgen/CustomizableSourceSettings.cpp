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

CustomizableSourceSettings::Builder*
CustomizableSourceSettings::Builder::fromString(SuperflatConfig* config) {
    return new Builder();
}

// NON_MATCHING
CustomizableSourceSettings* CustomizableSourceSettings::Builder::build() {
    return new CustomizableSourceSettings(this);
}

// NON_MATCHING: thisBld is in wrong register
CustomizableSourceSettings::CustomizableSourceSettings(CustomizableSourceSettings::Builder* builder) {
    CustomizableSourceSettings::Builder* thisBld = mBuilder;

    thisBld->coordinateScale = builder->coordinateScale;
    thisBld->heightScale = builder->heightScale;
    thisBld->lowerLimitScale = builder->lowerLimitScale;
    thisBld->upperLimitScale = builder->upperLimitScale;
    thisBld->depthNoiseScaleX = builder->depthNoiseScaleX;
    thisBld->depthNoiseScaleZ = builder->depthNoiseScaleZ;
    thisBld->depthNoiseScaleExponent = builder->depthNoiseScaleExponent;
    thisBld->mainNoiseScaleX = builder->mainNoiseScaleX;
    thisBld->mainNoiseScaleY = builder->mainNoiseScaleY;
    thisBld->mainNoiseScaleZ = builder->mainNoiseScaleZ;
    thisBld->baseSize = builder->baseSize;
    thisBld->stretchY = builder->stretchY;
    thisBld->biomeDepthWeight = builder->biomeDepthWeight;
    thisBld->biomeDepthOffset = builder->biomeDepthOffset;
    thisBld->biomeScaleWeight = builder->biomeScaleWeight;
    thisBld->biomeScaleOffset = builder->biomeScaleOffset;
    thisBld->seaLevel = builder->seaLevel;
    thisBld->useCaves = builder->useCaves;
    thisBld->useDungeons = builder->useDungeons;
    thisBld->dungeonChance = builder->dungeonChance;
    thisBld->byte_4C = builder->byte_4C;
    thisBld->byte_4D = builder->byte_4D;
    thisBld->byte_4E = builder->byte_4E;
    thisBld->byte_4F = builder->byte_4F;
    thisBld->byte_50 = builder->byte_50;
    thisBld->byte_51 = builder->byte_51;
    thisBld->byte_52 = builder->byte_52;
    thisBld->useWaterLakes = builder->useWaterLakes;
    thisBld->waterLakeChance = builder->waterLakeChance;
    thisBld->useLavaLakes = builder->useLavaLakes;
    thisBld->lavaLakeChance = builder->lavaLakeChance;
    thisBld->useLavaOceans = builder->useLavaOceans;
    thisBld->fixedBiome = builder->fixedBiome;
    thisBld->biomeSize = builder->biomeSize;
    thisBld->riverSize = builder->riverSize;
    thisBld->dirtSize = builder->dirtSize;
    thisBld->dirtCount = builder->dirtCount;
    thisBld->dirtMinHeight = builder->dirtMinHeight;
    thisBld->dirtMaxHeight = builder->dirtMaxHeight;
    thisBld->gravelSize = builder->gravelSize;
    thisBld->gravelCount = builder->gravelCount;
    thisBld->gravelMinHeight = builder->gravelMinHeight;
    thisBld->gravelMaxHeight = builder->gravelMaxHeight;
    thisBld->graniteSize = builder->graniteSize;
    thisBld->graniteCount = builder->graniteCount;
    thisBld->graniteMinHeight = builder->graniteMinHeight;
    thisBld->graniteMaxHeight = builder->graniteMaxHeight;
    thisBld->dioriteSize = builder->dioriteSize;
    thisBld->dioriteCount = builder->dioriteCount;
    thisBld->dioriteMinHeight = builder->dioriteMinHeight;
    thisBld->dioriteMaxHeight = builder->dioriteMaxHeight;
    thisBld->andesiteSize = builder->andesiteSize;
    thisBld->andesiteCount = builder->andesiteCount;
    thisBld->andesiteMinHeight = builder->andesiteMinHeight;
    thisBld->andesiteMaxHeight = builder->andesiteMaxHeight;
    thisBld->coalSize = builder->coalSize;
    thisBld->coalCount = builder->coalCount;
    thisBld->coalMinHeight = builder->coalMinHeight;
    thisBld->coalMaxHeight = builder->coalMaxHeight;
    thisBld->ironSize = builder->ironSize;
    thisBld->ironCount = builder->ironCount;
    thisBld->ironMinHeight = builder->ironMinHeight;
    thisBld->ironMaxHeight = builder->ironMaxHeight;
    thisBld->goldSize = builder->goldSize;
    thisBld->goldCount = builder->goldCount;
    thisBld->goldMinHeight = builder->goldMinHeight;
    thisBld->goldMaxHeight = builder->goldMaxHeight;
    thisBld->redstoneSize = builder->redstoneSize;
    thisBld->redstoneCount = builder->redstoneCount;
    thisBld->redstoneMinHeight = builder->redstoneMinHeight;
    thisBld->redstoneMaxHeight = builder->redstoneMaxHeight;
    thisBld->diamondSize = builder->diamondSize;
    thisBld->diamondCount = builder->diamondCount;
    thisBld->diamondMinHeight = builder->diamondMinHeight;
    thisBld->diamondMaxHeight = builder->diamondMaxHeight;
    thisBld->lapisSize = builder->lapisSize;
    thisBld->lapisCount = builder->lapisCount;
    thisBld->lapisCenterHeight = builder->lapisCenterHeight;
    thisBld->lapisSpread = builder->lapisSpread;
}
