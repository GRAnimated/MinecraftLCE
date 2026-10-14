#pragma once

#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"

class DoublePlantBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static inline Variant* VARIANTS[6];
        static Variant* byData(int data) { return VARIANTS[static_cast<unsigned int>(data) > 5 ? 0 : data]; }
        int getNameId() { return m_nameId; }
        int getDescriptionId() { return m_descriptionId; }

        int m_data;
        std::wstring m_name;
        int m_nameId;
        int m_descriptionId;
    };

    DoublePlantBlock();

    static void blockStaticCtor();
};
