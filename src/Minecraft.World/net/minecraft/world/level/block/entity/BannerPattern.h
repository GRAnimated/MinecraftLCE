#pragma once

#include <string>
#include <vector>

class ItemInstance;

class BannerPattern {
public:
    struct PatternGrid {
        explicit PatternGrid(std::wstring*);
        std::wstring* data;
        unsigned int length;
    };

    static void staticCtor();
    static std::vector<BannerPattern*> VALUES;
    static BannerPattern* BASE;
    static BannerPattern* BORDER;
    static BannerPattern* BRICKS;
    static BannerPattern* CIRCLE;
    static BannerPattern* CREEPER;
    static BannerPattern* CROSS;
    static BannerPattern* CURLY_BORDER;
    static BannerPattern* DIAGONAL_LEFT;
    static BannerPattern* DIAGONAL_RIGHT_MIRROR;
    static BannerPattern* DIAGONAL_LEFT_MIRROR;
    static BannerPattern* DIAGONAL_RIGHT;
    static BannerPattern* FLOWER;
    static BannerPattern* GRADIENT;
    static BannerPattern* GRADIENT_UP;
    static BannerPattern* HALF_HORIZONTAL;
    static BannerPattern* HALF_HORIZONTAL_MIRROR;
    static BannerPattern* HALF_VERTICAL;
    static BannerPattern* HALF_VERTICAL_MIRROR;
    static BannerPattern* MOJANG;
    static BannerPattern* RHOMBUS;
    static BannerPattern* SKULL;
    static BannerPattern* SMALL_STRIPES;
    static BannerPattern* SQUARE_BOTTOM_LEFT;
    static BannerPattern* SQUARE_BOTTOM_RIGHT;
    static BannerPattern* SQUARE_TOP_LEFT;
    static BannerPattern* SQUARE_TOP_RIGHT;
    static BannerPattern* STRAIGHT_CROSS;
    static BannerPattern* STRIPE_BOTTOM;
    static BannerPattern* STRIPE_CENTER;
    static BannerPattern* STRIPE_DOWNLEFT;
    static BannerPattern* STRIPE_DOWNRIGHT;
    static BannerPattern* STRIPE_LEFT;
    static BannerPattern* STRIPE_MIDDLE;
    static BannerPattern* STRIPE_RIGHT;
    static BannerPattern* STRIPE_TOP;
    static BannerPattern* TRIANGLE_BOTTOM;
    static BannerPattern* TRIANGLE_TOP;
    static BannerPattern* TRIANGLES_BOTTOM;
    static BannerPattern* TRIANGLES_TOP;

    BannerPattern(int, const std::wstring&, const unsigned char*, int);
    BannerPattern(int, const std::wstring&, ItemInstance*, const unsigned char*, int);
    BannerPattern(int, const std::wstring&, const std::wstring&, const std::wstring&, const std::wstring&,
                  const unsigned char*, int);
    void init(int, const std::wstring&, const unsigned char*, int);
    PatternGrid getPatternGrid();
    bool hasPattern();
    bool hasItem();
    ItemInstance* getItem();
    int getId();
    int getDescriptionId();

private:
    std::wstring m_shortName;
    std::wstring m_rows[3];
    ItemInstance* m_item;
    int m_id;
    int m_description;
    const unsigned char* m_textureKey;
};
