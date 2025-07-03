#pragma once

#include <string>

class FlowerBlock {
public:
    class FlowerCategory;
    class FlowerCategoryPredicate;
    class Flower {
    public:
        static Flower* YELLOW_FLOWER;
        static Flower* RED_FLOWER;
        static Flower* RED_MUSHROOM;
        static Flower* BROWN_MUSHROOM;

        enum EFlower {};

        Flower(FlowerBlock::FlowerCategory*, int, const std::wstring&, int, int, const std::wstring&,
               FlowerBlock::Flower::EFlower);

        void* field_0;
        int field_8;
    };

    virtual FlowerBlock::FlowerCategory* getFlowerCategory() = 0;
    virtual void getFlowerProperty();
};
