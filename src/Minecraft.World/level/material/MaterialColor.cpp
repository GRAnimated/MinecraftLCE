#include "Minecraft.World/level/material/MaterialColor.h"

MaterialColor::MaterialColor(int id, eMinecraftColour color) : mColor(color), mID(id) {
    MATERIAL_COLORS[id] = this;
}

void MaterialColor::staticCtor() {
    MATERIAL_COLORS = new MaterialColor*[64];
    NONE = new MaterialColor(0, eMinecraftColour::NONE);
    GRASS = new MaterialColor(1, eMinecraftColour::GRASS);
    SAND = new MaterialColor(2, eMinecraftColour::SAND);
    WOOL = new MaterialColor(3, eMinecraftColour::WOOL);
    FIRE = new MaterialColor(4, eMinecraftColour::FIRE);
    ICE = new MaterialColor(5, eMinecraftColour::ICE);
    METAL = new MaterialColor(6, eMinecraftColour::METAL);
    PLANT = new MaterialColor(7, eMinecraftColour::PLANT);
    SNOW = new MaterialColor(8, eMinecraftColour::SNOW);
    CLAY = new MaterialColor(9, eMinecraftColour::CLAY);
    DIRT = new MaterialColor(10, eMinecraftColour::DIRT);
    STONE = new MaterialColor(11, eMinecraftColour::STONE);
    WATER = new MaterialColor(12, eMinecraftColour::WATER);
    WOOD = new MaterialColor(13, eMinecraftColour::WOOD);
    QUARTZ = new MaterialColor(14, eMinecraftColour::QUARTZ);
    COLOR_ORANGE = new MaterialColor(15, eMinecraftColour::COLOR_ORANGE);
    COLOR_MAGENTA = new MaterialColor(16, eMinecraftColour::COLOR_MAGENTA);
    COLOR_LIGHT_BLUE = new MaterialColor(17, eMinecraftColour::COLOR_LIGHT_BLUE);
    COLOR_YELLOW = new MaterialColor(18, eMinecraftColour::COLOR_YELLOW);
    COLOR_LIGHT_GREEN = new MaterialColor(19, eMinecraftColour::COLOR_LIGHT_GREEN);
    COLOR_PINK = new MaterialColor(20, eMinecraftColour::COLOR_PINK);
    COLOR_GRAY = new MaterialColor(21, eMinecraftColour::COLOR_GRAY);
    COLOR_LIGHT_GRAY = new MaterialColor(22, eMinecraftColour::COLOR_LIGHT_GRAY);
    COLOR_CYAN = new MaterialColor(23, eMinecraftColour::COLOR_CYAN);
    COLOR_PURPLE = new MaterialColor(24, eMinecraftColour::COLOR_PURPLE);
    COLOR_BLUE = new MaterialColor(25, eMinecraftColour::COLOR_BLUE);
    COLOR_BROWN = new MaterialColor(26, eMinecraftColour::COLOR_BROWN);
    COLOR_GREEN = new MaterialColor(27, eMinecraftColour::COLOR_GREEN);
    COLOR_RED = new MaterialColor(28, eMinecraftColour::COLOR_RED);
    COLOR_BLACK = new MaterialColor(29, eMinecraftColour::COLOR_BLACK);
    GOLD = new MaterialColor(30, eMinecraftColour::GOLD);
    DIAMOND = new MaterialColor(31, eMinecraftColour::DIAMOND);
    LAPIS = new MaterialColor(32, eMinecraftColour::LAPIS);
    EMERALD = new MaterialColor(33, eMinecraftColour::EMERALD);
    PODZOL = new MaterialColor(34, eMinecraftColour::PODZOL);
    NETHER = new MaterialColor(35, eMinecraftColour::NETHER);
    TERRACOTTA_WHITE = new MaterialColor(36, eMinecraftColour::TERRACOTTA_WHITE);
    TERRACOTTA_ORANGE = new MaterialColor(37, eMinecraftColour::TERRACOTTA_ORANGE);
    TERRACOTTA_MAGENTA = new MaterialColor(38, eMinecraftColour::TERRACOTTA_MAGENTA);
    TERRACOTTA_LIGHT_BLUE = new MaterialColor(39, eMinecraftColour::TERRACOTTA_LIGHT_BLUE);
    TERRACOTTA_YELLOW = new MaterialColor(40, eMinecraftColour::TERRACOTTA_YELLOW);
    TERRACOTTA_LIGHT_GREEN = new MaterialColor(41, eMinecraftColour::TERRACOTTA_LIGHT_GREEN);
    TERRACOTTA_PINK = new MaterialColor(42, eMinecraftColour::TERRACOTTA_PINK);
    TERRACOTTA_GRAY = new MaterialColor(43, eMinecraftColour::TERRACOTTA_GRAY);
    TERRACOTTA_LIGHT_GRAY = new MaterialColor(44, eMinecraftColour::TERRACOTTA_LIGHT_GRAY);
    TERRACOTTA_CYAN = new MaterialColor(45, eMinecraftColour::TERRACOTTA_CYAN);
    TERRACOTTA_PURPLE = new MaterialColor(46, eMinecraftColour::TERRACOTTA_PURPLE);
    TERRACOTTA_BLUE = new MaterialColor(47, eMinecraftColour::TERRACOTTA_BLUE);
    TERRACOTTA_BROWN = new MaterialColor(48, eMinecraftColour::TERRACOTTA_BROWN);
    TERRACOTTA_GREEN = new MaterialColor(49, eMinecraftColour::TERRACOTTA_GREEN);
    TERRACOTTA_RED = new MaterialColor(50, eMinecraftColour::TERRACOTTA_RED);
    TERRACOTTA_BLACK = new MaterialColor(51, eMinecraftColour::TERRACOTTA_BLACK);
}

int MaterialColor::calculateRGBColor(int colorIntensity) const {
    int rgbIntensity = 220;
    if (colorIntensity == 3) {
        rgbIntensity = 135;
    }
    if (colorIntensity == 2) {
        rgbIntensity = 255;
    }
    if (colorIntensity == 1) {
        rgbIntensity = 220;
    }
    if (colorIntensity == 0) {
        rgbIntensity = 180;
    }

    return 0xFF000000 | (((mColor & 0xFF0000) >> 16) * rgbIntensity / 255) << 16 | (((mColor & 0xFF00) >> 8) * rgbIntensity / 255) << 8 | (mColor & 0xFF) * rgbIntensity / 255;
}
