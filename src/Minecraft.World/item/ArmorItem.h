#include "Minecraft.World/item/Item.h"
class ArmorItem : public Item {
public:
    class ArmorMaterial;
    ArmorItem(ArmorMaterial const*, int, const EquipmentSlot*);

    const EquipmentSlot* mEquipmentSlot;
    int mDefenseForSlot;
    float mToughness;
    int dword90;
    const ArmorMaterial* mArmorMaterial;
};