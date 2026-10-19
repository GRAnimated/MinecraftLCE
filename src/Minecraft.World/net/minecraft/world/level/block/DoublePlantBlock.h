#pragma once

#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"

class DoublePlantBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static Variant* FERN;
        static Variant* GRASS;
        static Variant* SUNFLOWER;
        static Variant* SYRINGA;
        static Variant* ROSE;
        static Variant* PAEONIA;
        static inline Variant* VARIANTS[6];
        // name guessed
        static Variant* byData(int data) { return VARIANTS[static_cast<unsigned int>(data) > 5 ? 0 : data]; }
        // name guessed
        int getNameId() { return m_nameId; }
        // name guessed
        int getDescriptionId() { return m_descriptionId; }

        int m_data;
        std::wstring m_name;
        int m_nameId;
        int m_descriptionId;
    };

    DoublePlantBlock();
    void placeAt(Level*, const BlockPos&, Variant*, int);

    static void blockStaticCtor();
};
