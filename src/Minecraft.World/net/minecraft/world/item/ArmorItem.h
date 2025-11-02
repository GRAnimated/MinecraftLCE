#pragma once

#include "net/minecraft/world/item/Item.h"

class ArmorItem : public Item {
public:
    class ArmorMaterial;
    ArmorItem(const ArmorMaterial*, int, const EquipmentSlot*);

    static void staticCtor();

    const EquipmentSlot* mEquipmentSlot;
    int mDefenseForSlot;
    float mToughness;
    int dword90;
    const ArmorMaterial* mArmorMaterial;
};
