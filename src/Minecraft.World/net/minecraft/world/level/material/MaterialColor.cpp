#include "net/minecraft/world/level/material/MaterialColor.h"

MaterialColor::MaterialColor(int id, eMinecraftColour color) : mColor(color), mID(id) {
    MATERIAL_COLORS[id] = this;
}

void MaterialColor::staticCtor() {
    MATERIAL_COLORS = new MaterialColor*[64];
    NONE = new MaterialColor(0, eMinecraftColour::Material_None);
    GRASS = new MaterialColor(1, eMinecraftColour::Material_Grass);
    SAND = new MaterialColor(2, eMinecraftColour::Material_Sand);
    WOOL = new MaterialColor(3, eMinecraftColour::Material_Cloth);
    FIRE = new MaterialColor(4, eMinecraftColour::Material_Fire);
    ICE = new MaterialColor(5, eMinecraftColour::Material_Ice);
    METAL = new MaterialColor(6, eMinecraftColour::Material_Metal);
    PLANT = new MaterialColor(7, eMinecraftColour::Material_Plant);
    SNOW = new MaterialColor(8, eMinecraftColour::Material_Snow);
    CLAY = new MaterialColor(9, eMinecraftColour::Material_Clay);
    DIRT = new MaterialColor(10, eMinecraftColour::Material_Dirt);
    STONE = new MaterialColor(11, eMinecraftColour::Material_Stone);
    WATER = new MaterialColor(12, eMinecraftColour::Material_Water);
    WOOD = new MaterialColor(13, eMinecraftColour::Material_Wood);
    QUARTZ = new MaterialColor(14, eMinecraftColour::Material_Quartz);
    COLOR_ORANGE = new MaterialColor(15, eMinecraftColour::Material_Color_Orange);
    COLOR_MAGENTA = new MaterialColor(16, eMinecraftColour::Material_Color_Magenta);
    COLOR_LIGHT_BLUE = new MaterialColor(17, eMinecraftColour::Material_Color_Light_Blue);
    COLOR_YELLOW = new MaterialColor(18, eMinecraftColour::Material_Color_Yellow);
    COLOR_LIGHT_GREEN = new MaterialColor(19, eMinecraftColour::Material_Color_Light_Green);
    COLOR_PINK = new MaterialColor(20, eMinecraftColour::Material_Color_Pink);
    COLOR_GRAY = new MaterialColor(21, eMinecraftColour::Material_Color_Grey);
    COLOR_LIGHT_GRAY = new MaterialColor(22, eMinecraftColour::Material_Color_Silver);
    COLOR_CYAN = new MaterialColor(23, eMinecraftColour::Material_Color_Cyan);
    COLOR_PURPLE = new MaterialColor(24, eMinecraftColour::Material_Color_Purple);
    COLOR_BLUE = new MaterialColor(25, eMinecraftColour::Material_Color_Blue);
    COLOR_BROWN = new MaterialColor(26, eMinecraftColour::Material_Color_Brown);
    COLOR_GREEN = new MaterialColor(27, eMinecraftColour::Material_Color_Green);
    COLOR_RED = new MaterialColor(28, eMinecraftColour::Material_Color_Red);
    COLOR_BLACK = new MaterialColor(29, eMinecraftColour::Material_Color_Black);
    GOLD = new MaterialColor(30, eMinecraftColour::Material_Gold);
    DIAMOND = new MaterialColor(31, eMinecraftColour::Material_Diamond);
    LAPIS = new MaterialColor(32, eMinecraftColour::Material_Lapis);
    EMERALD = new MaterialColor(33, eMinecraftColour::Material_Emerald);
    PODZOL = new MaterialColor(34, eMinecraftColour::Material_Podzol);
    NETHER = new MaterialColor(35, eMinecraftColour::Material_Nether);
    TERRACOTTA_WHITE = new MaterialColor(36, eMinecraftColour::Material_Terracotta_White);
    TERRACOTTA_ORANGE = new MaterialColor(37, eMinecraftColour::Material_Terracotta_Orange);
    TERRACOTTA_MAGENTA = new MaterialColor(38, eMinecraftColour::Material_Terracotta_Magenta);
    TERRACOTTA_LIGHT_BLUE = new MaterialColor(39, eMinecraftColour::Material_Terracotta_Light_Blue);
    TERRACOTTA_YELLOW = new MaterialColor(40, eMinecraftColour::Material_Terracotta_Yellow);
    TERRACOTTA_LIGHT_GREEN = new MaterialColor(41, eMinecraftColour::Material_Terracotta_Light_Green);
    TERRACOTTA_PINK = new MaterialColor(42, eMinecraftColour::Material_Terracotta_Pink);
    TERRACOTTA_GRAY = new MaterialColor(43, eMinecraftColour::Material_Terracotta_Grey);
    TERRACOTTA_LIGHT_GRAY = new MaterialColor(44, eMinecraftColour::Material_Terracotta_Silver);
    TERRACOTTA_CYAN = new MaterialColor(45, eMinecraftColour::Material_Terracotta_Cyan);
    TERRACOTTA_PURPLE = new MaterialColor(46, eMinecraftColour::Material_Terracotta_Purple);
    TERRACOTTA_BLUE = new MaterialColor(47, eMinecraftColour::Material_Terracotta_Blue);
    TERRACOTTA_BROWN = new MaterialColor(48, eMinecraftColour::Material_Terracotta_Brown);
    TERRACOTTA_GREEN = new MaterialColor(49, eMinecraftColour::Material_Terracotta_Green);
    TERRACOTTA_RED = new MaterialColor(50, eMinecraftColour::Material_Terracotta_Red);
    TERRACOTTA_BLACK = new MaterialColor(51, eMinecraftColour::Material_Terracotta_Black);
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

    return 0xFF000000 | (((mColor & 0xFF0000) >> 16) * rgbIntensity / 255) << 16
           | (((mColor & 0xFF00) >> 8) * rgbIntensity / 255) << 8 | (mColor & 0xFF) * rgbIntensity / 255;
}
