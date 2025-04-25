#include "Minecraft.World/enchantment/categories/WearableCategory.h"
#include "Minecraft.World/inventory/EquipmentSlot.h"
#include "Minecraft.World/item/ArmorItem.h"
#include "Minecraft.World/item/BlockItem.h"
#include "Minecraft.World/item/ElytraItem.h"
#include "Minecraft.World/item/SkullItem.h"
#include "Minecraft.World/level/block/Block.h"
#include "Minecraft.World/level/block/PumpkinBlock.h"

const WearableCategory* WearableCategory::sWearableCategory = new WearableCategory();

// it's matching but ugly af
bool WearableCategory::canEnchant(Item* item) const {
    if (!item)
        return false;
    BlockItem* blockItem = dynamic_cast<BlockItem*>(item);
    bool cipa = blockItem && dynamic_cast<PumpkinBlock*>(blockItem->getBlock());
    if (dynamic_cast<ArmorItem*>(item))
        return true;
    if (dynamic_cast<ElytraItem*>(item))
        return true;
    if (dynamic_cast<SkullItem*>(item))
        return true;
    return cipa;
}