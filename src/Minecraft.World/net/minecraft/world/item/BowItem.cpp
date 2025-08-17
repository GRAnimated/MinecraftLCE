#include "net/minecraft/world/item/BowItem.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/entity/player/MultiplayerLocalPlayer.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/inventory/Inventory.h"
#include "net/minecraft/world/item/InteractionResultHolder.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/Items.h"
#include "types.h"
#include <cstring>
#include <memory>

BowItem::BowItem() : Item() {
    this->mMaxStackSize = 1;
    this->setMaxDamage(384);

    memset(this->mBowIcons, 0, 3 * sizeof(TextureAtlasSprite*));  // sizeof because readability

    this->addProperty(ResourceLocation(L"pull"),
                      (const ItemPropertyFunction*)new BowItem_Pull_ItemPropertyFunction());

    this->addProperty(ResourceLocation(L"pulling"),
                      (const ItemPropertyFunction*)new BowItem_Pulling_ItemPropertyFunction());
}

int BowItem::GetUseTooltip(const ItemToolTipDataHolder& data) {
    if (!data.mPlayer->mAbilities.mIsInstabuild && !data.mPlayer->mInventory->hasResource(Items::ARROW)
        && !data.mPlayer->mInventory->hasResource(Items::TIPPED_ARROW)) {
        return 0xFFFFFFFF;
    }
    if (data.mPlayer->isUsingItem())
        return StringIDs::Release;
    return StringIDs::DrawDraw;
}

InteractionResultHolder BowItem::use(Level* level, std::shared_ptr<Player> player,
                                     InteractionHand::EInteractionHand hand) {
    return this->fjUseWithProjectile(level, player, hand, this->findProjectile(player));
}

int BowItem::getUseAnimation(not_null_ptr<ItemInstance>) {
    return 4;
}

int BowItem::getUseDuration(not_null_ptr<ItemInstance>) {
    return 72000;
}

void BowItem::releaseUsing(not_null_ptr<ItemInstance> item, Level* level, std::shared_ptr<LivingEntity> user,
                           int remainingTicks) {
    if (user->isType(ePlayer)) {
        std::shared_ptr<Player> player = std::static_pointer_cast<Player>(user);
        not_null_ptr<ItemInstance> projectile = this->findProjectile(player);
        this->fjReleaseUsingWithProjectile(item, level, player, remainingTicks, projectile);
    }
}

int BowItem::getEnchantmentValue() {
    return 1;
}

std::wstring BowItem::BOW_ICON_NAMES[3] = {L"bow_pull_0", L"bow_pull_1", L"bow_pull_2"};

void BowItem::registerIcons(IconRegister* iconReg) {
    Item::registerIcons(iconReg);

    this->mBowIcons[0] = iconReg->registerIcon(BOW_ICON_NAMES[0]);
    this->mBowIcons[1] = iconReg->registerIcon(BOW_ICON_NAMES[1]);
    this->mBowIcons[2] = iconReg->registerIcon(BOW_ICON_NAMES[2]);
}

int BowItem::GetOverrideCount() {
    return 0;
}

int BowItem::GetOverrideCountColour() {
    return Item::GetOverrideCountColour();
}

TextureAtlasSprite* BowItem::GetOverrideCountIcon(not_null_ptr<ItemInstance> item) {
    if (Minecraft::GetInstance()->mLocalPlayer->getUseItem() == item) {
        int ticksUsingItem = Minecraft::GetInstance()->mLocalPlayer->getTicksUsingItem();
        if (ticksUsingItem >= BowItem::GetMaxBowDuration() - 2)
            return Items::BOW->getDrawnIcon(2);

        if (ticksUsingItem > (2 * BowItem::GetMaxBowDuration()) / 3)
            return Items::BOW->getDrawnIcon(1);

        if (ticksUsingItem > 0)
            return Items::BOW->getDrawnIcon(0);
    }

    return Item::GetOverrideCountIcon(item);
}

InteractionResultHolder BowItem::fjUseWithProjectile(Level* level, std::shared_ptr<Player> player,
                                                     InteractionHand::EInteractionHand hand,
                                                     not_null_ptr<ItemInstance> item) {
    not_null_ptr<ItemInstance> itemInHand = player->getItemInHand(hand);
    bool isEmpty = item->isEmpty();
    if (player->mAbilities.mIsInstabuild || !isEmpty) {
        player->startUsingItem(hand);
        return InteractionResultHolder(InteractionResult::SUCCESS, itemInHand);
    } else {
        // shame on 4J, I've spent too much time to figure out they've done this shit down below
        return isEmpty ? InteractionResultHolder(InteractionResult::FAIL, itemInHand) :
                         InteractionResultHolder(InteractionResult::PASS, itemInHand);
    }
}

TextureAtlasSprite* BowItem::getDrawnIcon(int id) {
    return this->mBowIcons[id];
}

int BowItem::GetMaxBowDuration() {
    return Minecraft::GetInstance()->GetMiniGame()->HasFeatureArrowCanKnockback() ? 10 : 20;
}
