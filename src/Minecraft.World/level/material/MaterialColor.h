#pragma once

class DyeColor;

enum eMinecraftColour {
    NONE = 161,
    GRASS = 162,
    SAND = 163,
    WOOL = 164,
    FIRE = 165,
    ICE = 166,
    METAL = 167,
    PLANT = 168,
    SNOW = 169,
    CLAY = 170,
    DIRT = 171,
    STONE = 172,
    WATER = 173,
    WOOD = 174,
    QUARTZ = 176,
    COLOR_ORANGE = 182,
    COLOR_MAGENTA = 183,
    COLOR_LIGHT_BLUE = 184,
    COLOR_YELLOW = 185,
    COLOR_LIGHT_GREEN = 186,
    COLOR_PINK = 187,
    COLOR_GRAY = 188,
    COLOR_LIGHT_GRAY = 189,
    COLOR_CYAN = 190,
    COLOR_PURPLE = 191,
    COLOR_BLUE = 192,
    COLOR_BROWN = 193,
    COLOR_GREEN = 194,
    COLOR_RED = 195,
    COLOR_BLACK = 196,
    GOLD = 177,
    DIAMOND = 178,
    LAPIS = 179,
    EMERALD = 175,
    PODZOL = 180,
    NETHER = 181,
    TERRACOTTA_WHITE = 197,
    TERRACOTTA_ORANGE = 198,
    TERRACOTTA_MAGENTA = 199,
    TERRACOTTA_LIGHT_BLUE = 200,
    TERRACOTTA_YELLOW = 201,
    TERRACOTTA_LIGHT_GREEN = 202,
    TERRACOTTA_PINK = 203,
    TERRACOTTA_GRAY = 204,
    TERRACOTTA_LIGHT_GRAY = 205,
    TERRACOTTA_CYAN = 206,
    TERRACOTTA_PURPLE = 207,
    TERRACOTTA_BLUE = 208,
    TERRACOTTA_BROWN = 209,
    TERRACOTTA_GREEN = 210,
    TERRACOTTA_RED = 211,
    TERRACOTTA_BLACK = 212,
};

class MaterialColor {
public:
    static MaterialColor** MATERIAL_COLORS;
    static MaterialColor* NONE;
    static MaterialColor* GRASS;
    static MaterialColor* SAND;
    static MaterialColor* WOOL;
    static MaterialColor* FIRE;
    static MaterialColor* ICE;
    static MaterialColor* METAL;
    static MaterialColor* PLANT;
    static MaterialColor* SNOW;
    static MaterialColor* CLAY;
    static MaterialColor* DIRT;
    static MaterialColor* STONE;
    static MaterialColor* WATER;
    static MaterialColor* WOOD;
    static MaterialColor* QUARTZ;
    static MaterialColor* COLOR_ORANGE;
    static MaterialColor* COLOR_MAGENTA;
    static MaterialColor* COLOR_LIGHT_BLUE;
    static MaterialColor* COLOR_YELLOW;
    static MaterialColor* COLOR_LIGHT_GREEN;
    static MaterialColor* COLOR_PINK;
    static MaterialColor* COLOR_GRAY;
    static MaterialColor* COLOR_LIGHT_GRAY;
    static MaterialColor* COLOR_CYAN;
    static MaterialColor* COLOR_PURPLE;
    static MaterialColor* COLOR_BLUE;
    static MaterialColor* COLOR_BROWN;
    static MaterialColor* COLOR_GREEN;
    static MaterialColor* COLOR_RED;
    static MaterialColor* COLOR_BLACK;
    static MaterialColor* GOLD;
    static MaterialColor* DIAMOND;
    static MaterialColor* LAPIS;
    static MaterialColor* EMERALD;
    static MaterialColor* PODZOL;
    static MaterialColor* NETHER;
    static MaterialColor* TERRACOTTA_WHITE;
    static MaterialColor* TERRACOTTA_ORANGE;
    static MaterialColor* TERRACOTTA_MAGENTA;
    static MaterialColor* TERRACOTTA_LIGHT_BLUE;
    static MaterialColor* TERRACOTTA_YELLOW;
    static MaterialColor* TERRACOTTA_LIGHT_GREEN;
    static MaterialColor* TERRACOTTA_PINK;
    static MaterialColor* TERRACOTTA_GRAY;
    static MaterialColor* TERRACOTTA_LIGHT_GRAY;
    static MaterialColor* TERRACOTTA_CYAN;
    static MaterialColor* TERRACOTTA_PURPLE;
    static MaterialColor* TERRACOTTA_BLUE;
    static MaterialColor* TERRACOTTA_BROWN;
    static MaterialColor* TERRACOTTA_GREEN;
    static MaterialColor* TERRACOTTA_RED;
    static MaterialColor* TERRACOTTA_BLACK;

    static void staticCtor();
    static void staticCtorAfterDyeColor();

    MaterialColor(int, eMinecraftColour);
    int calculateRGBColor(int) const;
    static void getDyeMaterial(DyeColor const*);

    eMinecraftColour mColor;
    int mID;
};