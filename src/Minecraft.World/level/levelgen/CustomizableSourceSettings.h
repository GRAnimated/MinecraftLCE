#pragma once

class SuperflatConfig;

class CustomizableSourceSettings {
public:
    struct Builder {
        Builder();
        void setDefaults();
        static Builder* fromString(SuperflatConfig* config);
        CustomizableSourceSettings* build();

        float coordinateScale;
        float heightScale;
        float lowerLimitScale;
        float upperLimitScale;
        float depthNoiseScaleX;
        float depthNoiseScaleZ;
        float depthNoiseScaleExponent;
        float mainNoiseScaleX;
        float mainNoiseScaleY;
        float mainNoiseScaleZ;
        float baseSize;
        float stretchY;
        float biomeDepthWeight;
        float biomeDepthOffset;
        float biomeScaleWeight;
        float biomeScaleOffset;
        int seaLevel;
        bool useCaves;
        bool useDungeons;
        int dungeonChance;
        bool byte_4C;
        bool byte_4D;
        bool byte_4E;
        bool byte_4F;
        bool byte_50;
        bool byte_51;
        bool byte_52;
        bool useWaterLakes;
        int waterLakeChance;
        bool useLavaLakes;
        int lavaLakeChance;
        bool useLavaOceans;
        int fixedBiome;
        int biomeSize;
        int riverSize;
        int dirtSize;
        int dirtCount;
        int dirtMinHeight;
        int dirtMaxHeight;
        int gravelSize;
        int gravelCount;
        int gravelMinHeight;
        int gravelMaxHeight;
        int graniteSize;
        int graniteCount;
        int graniteMinHeight;
        int graniteMaxHeight;
        int dioriteSize;
        int dioriteCount;
        int dioriteMinHeight;
        int dioriteMaxHeight;
        int andesiteSize;
        int andesiteCount;
        int andesiteMinHeight;
        int andesiteMaxHeight;
        int coalSize;
        int coalCount;
        int coalMinHeight;
        int coalMaxHeight;
        int ironSize;
        int ironCount;
        int ironMinHeight;
        int ironMaxHeight;
        int goldSize;
        int goldCount;
        int goldMinHeight;
        int goldMaxHeight;
        int redstoneSize;
        int redstoneCount;
        int redstoneMinHeight;
        int redstoneMaxHeight;
        int diamondSize;
        int diamondCount;
        int diamondMinHeight;
        int diamondMaxHeight;
        int lapisSize;
        int lapisCount;
        int lapisCenterHeight;
        int lapisSpread;
    };

    CustomizableSourceSettings(CustomizableSourceSettings::Builder* builder);

    Builder* mBuilder;
};