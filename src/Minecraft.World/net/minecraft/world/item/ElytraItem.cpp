#include "net/minecraft/world/item/ElytraItem.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/entity/EquipmentSlot.h"
#include "net/minecraft/world/entity/mob/Mob.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/item/BehaviorRegistry.h"
#include "net/minecraft/world/item/InteractionResultHolder.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/Items.h"
#include "types.h"

DispenseItemBehavior* elytraDispenseBehavior
    = nullptr;  // TODO: replace that with correct dispense behavior later

ElytraItem::ElytraItem() {
    this->mMaxStackSize = 1;
    this->setMaxDamage(432);

    this->addProperty(ResourceLocation(L"broken"), new ElytraItem_ItemPropertyFunction());

    BehaviorRegistry::sInstance.add(this, elytraDispenseBehavior);
}

bool ElytraItem::isFlyEnabled(not_null_ptr<ItemInstance> item) {
    return item->getDamageValue() < item->getMaxDamage() - 1;
}

int ElytraItem::GetUseTooltip(const ItemToolTipDataHolder& data) {
    if (data.idk == 2) {
        return 0xFFFFFFFF;
    } else {
        return StringIDs::Equip;
    }
    // Wonder if that was one liner or not
}

ElytraItem::~ElytraItem() {}

bool ElytraItem::TestUse(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand) {
    return true;
}

InteractionResultHolder ElytraItem::use(Level*, std::shared_ptr<Player> player,
                                        InteractionHand::EInteractionHand hand) {
    not_null_ptr<ItemInstance> heldItem = player->getItemInHand(hand);
    EquipmentSlot* slot = Mob::getEquipmentSlotForItem(heldItem);

    not_null_ptr<ItemInstance> elo = player->getItemSlot(slot);
    player->setItemSlot(slot, heldItem->copy());
    heldItem->setCount(0);

    // funny that it has to be if statement
    if (elo->isEmpty()) {
        return InteractionResultHolder(InteractionResult::SUCCESS, heldItem);
    } else {
        return InteractionResultHolder(InteractionResult::SUCCESS, elo);
    }
}

bool ElytraItem::isValidRepairItem(not_null_ptr<ItemInstance> source, not_null_ptr<ItemInstance> repairItem) {
    return repairItem->getItem() == Items::LEATHER;
}

void ElytraItem::registerIcons(IconRegister* iconRegister) {
    Item::registerIcons(iconRegister);

    this->mBrokenElytraIcon = iconRegister->registerIcon(L"broken_elytra");
}

TextureAtlasSprite* ElytraItem::getLayerIcon(int usage, int) {
    if (this->getMaxDamage() - 1 > usage)
        return this->mDefaultIcon;
    else
        return this->mBrokenElytraIcon;
}

TextureAtlasSprite* ElytraItem::getIcon(not_null_ptr<ItemInstance> item) {
    if (this->isFlyEnabled(item))
        return this->mDefaultIcon;
    else
        return this->mBrokenElytraIcon;
}

int ElytraItem::GetArmorType() {
    return 2;
}
