#pragma once

#include "net/minecraft/world/level/block/Block.h"

class StoneBrickBlock : public Block {
public:
    StoneBrickBlock();

    static void blockStaticCtor();

    class Variant : public StringRepresentable {
    public:
        static inline Variant* DEFAULT;
    };

    static inline EnumProperty<Variant*>* VARIANT;
};
