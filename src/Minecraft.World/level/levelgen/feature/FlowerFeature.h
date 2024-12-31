#pragma once

#include <string>
#include "Minecraft.World/level/levelgen/feature/Feature.h"

// TODO: Move this to its own file when blocks start getting decomped
class FlowerBlock {
public:
    class FlowerCategory;
    class Flower {
    public:
        static Flower* YELLOW_FLOWER;
        static Flower* RED_FLOWER;
        static Flower* RED_MUSHROOM;
        static Flower* BROWN_MUSHROOM;

        enum EFlower {};

        Flower(FlowerBlock::FlowerCategory*, int, const std::wstring&, int, int, const std::wstring&, FlowerBlock::Flower::EFlower);

        void* field_0;
        int field_8;
    };
};

class FlowerFeature : public Feature {
public:
    FlowerFeature(FlowerBlock*, FlowerBlock::Flower*);

    virtual ~FlowerFeature() override;
    virtual bool place(Level* level, Random& random, const BlockPos& pos) override;

    void* field_10;
    void* field_18;
};
