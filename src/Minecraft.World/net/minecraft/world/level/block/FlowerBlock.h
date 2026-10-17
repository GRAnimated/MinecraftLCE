#pragma once

#include "Bush.h"
#include "net/minecraft/world/level/block/BonemealableBlock.h"
#include <string>

class FlowerBlock : public Bush, public BonemealableBlock {
public:
    class FlowerCategory {
    public:
        FlowerBlock* getBlock();
    };
    class FlowerCategoryPredicate;
    class Flower {
    public:
        static Flower* YELLOW_FLOWER;
        static Flower* RED_FLOWER;
        static Flower* RED_MUSHROOM;
        static Flower* BROWN_MUSHROOM;
        static Flower* OXEYE_DAISY;
        static Flower* BLUE_ORCHID;
        static Flower* HOUSTONIA;
        static Flower* RED_TULIP;
        static Flower* ORANGE_TULIP;
        static Flower* WHITE_TULIP;
        static Flower* PINK_TULIP;
        static Flower* FLOWERS[10];

        enum EFlower {};

        Flower(FlowerBlock::FlowerCategory*, int, const std::wstring&, int, int, const std::wstring&,
               FlowerBlock::Flower::EFlower);

        void* m_field0;
        FlowerCategory* getCategory() const;
        int getData();
        int getNameId();
        int getDescriptionId();

        int m_field8;
        int m_field12;
        int m_data;
    };

    virtual FlowerBlock::FlowerCategory* getFlowerCategory() = 0;
    virtual Property* getFlowerProperty();

    Property* m_flowerProperty;
};
