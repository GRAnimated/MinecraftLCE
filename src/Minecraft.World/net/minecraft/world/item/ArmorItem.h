#pragma once

#include "net/minecraft/world/item/Item.h"

class ArmorItem : public Item {
public:
    class ArmorMaterial;
    ArmorItem(const ArmorMaterial*, int, const EquipmentSlot*);

    static void staticCtor();

    const EquipmentSlot* m_equipmentSlot;
    int m_defenseForSlot;
    float m_toughness;
    int m_dword90;
    const ArmorMaterial* m_armorMaterial;
};
