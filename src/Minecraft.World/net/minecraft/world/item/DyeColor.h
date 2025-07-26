#pragma once

class DyeColor {
public:
    static const DyeColor* WHITE;
    static const DyeColor* ORANGE;
    static const DyeColor* MAGENTA;
    static const DyeColor* LIGHT_BLUE;
    static const DyeColor* YELLOW;
    static const DyeColor* LIME;
    static const DyeColor* PINK;
    static const DyeColor* GRAY;
    static const DyeColor* SILVER;
    static const DyeColor* CYAN;
    static const DyeColor* PURPLE;
    static const DyeColor* BLUE;
    static const DyeColor* BROWN;
    static const DyeColor* GREEN;
    static const DyeColor* RED;
    static const DyeColor* BLACK;

    int getBlockData() const;
    int getItemData() const;
};
