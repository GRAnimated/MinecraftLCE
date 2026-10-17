#pragma once

#include "net/minecraft/world/item/Item.h"

class ArmorItem : public Item {
public:
    class ArmorMaterial {
    public:
        static const ArmorMaterial* LEATHER;
        static const ArmorMaterial* CHAIN;
        static const ArmorMaterial* IRON;
        static const ArmorMaterial* GOLD;
        static const ArmorMaterial* DIAMOND;
    };
    ArmorItem(const ArmorMaterial*, int, const EquipmentSlot*);

    static void staticCtor();

    const EquipmentSlot* m_equipmentSlot;
    int m_defenseForSlot;
    float m_toughness;
    int m_dword90;
    const ArmorMaterial* m_armorMaterial;
    void* m_unknownA0[2];
};
