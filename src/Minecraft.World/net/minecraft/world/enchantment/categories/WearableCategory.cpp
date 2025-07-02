#include "net/minecraft/world/enchantment/categories/WearableCategory.h"
#include "net/minecraft/world/entity/EquipmentSlot.h"
#include "net/minecraft/world/item/ArmorItem.h"
#include "net/minecraft/world/item/BlockItem.h"
#include "net/minecraft/world/item/ElytraItem.h"
#include "net/minecraft/world/item/SkullItem.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/PumpkinBlock.h"

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