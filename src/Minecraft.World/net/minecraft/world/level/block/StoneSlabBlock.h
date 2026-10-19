#pragma once

#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"

class StoneSlabBlock : public Block {
public:
    /** Variant interface only; catalogue layout and construction remain unreconstructed.
     */
    class Variant : public StringRepresentable {
    public:
        static Variant* SANDSTONE;
    };

    static EnumProperty<Variant*>* VARIANT;
    static void blockStaticCtor();
};
