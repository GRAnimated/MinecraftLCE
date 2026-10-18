#pragma once

#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"

class WallBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static inline Variant* VARIANTS[2];
        static Variant* byData(int data) { return VARIANTS[static_cast<unsigned int>(data) > 1 ? 0 : data]; }
        int getNameId() { return m_nameId; }

        int m_data;
        std::wstring m_name;
        int m_nameId;
    };

    WallBlock(Block*);

    static void blockStaticCtor();
};
