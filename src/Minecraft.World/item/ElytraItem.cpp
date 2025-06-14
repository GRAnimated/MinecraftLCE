#include "types.h"
#include "Minecraft.Client/renderer/texture/IconRegister.h"
#include "Minecraft.Client/resources/ResourceLocation.h"
#include "Minecraft.World/entity/mob/Mob.h"
#include "Minecraft.World/entity/player/Player.h"
#include "Minecraft.World/inventory/EquipmentSlot.h"
#include "Minecraft.World/item/BehaviorRegistry.h"
#include "Minecraft.World/item/ElytraItem.h"
#include "Minecraft.World/item/InteractionResultHolder.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/item/Items.h"

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
        return 0xAFD35F15;
    }
    // Wonder if that was one liner or not
}

ElytraItem::~ElytraItem() {}

bool ElytraItem::TestUse(Level*, const std::shared_ptr<Player>&, InteractionHand::EInteractionHand) {
    return true;
}

InteractionResultHolder ElytraItem::use(Level*, const std::shared_ptr<Player>& player,
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

bool ElytraItem::isValidRepairItem(const std::shared_ptr<ItemInstance>& source,
                                   const std::shared_ptr<ItemInstance>& repairItem) {
    return repairItem->getItem() == Items::LEATHER;
}

void ElytraItem::registerIcons(IconRegister* iconRegister) {
    Item::registerIcons(iconRegister);

    this->mBrokenElytraIcon = iconRegister->registerIcon(L"broken_elytra");
}

TextureAtlasSprite* ElytraItem::getLayerIcon(int usage, int, const std::shared_ptr<ItemInstance>&) {
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