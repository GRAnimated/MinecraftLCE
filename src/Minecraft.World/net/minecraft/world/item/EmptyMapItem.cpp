#include "EmptyMapItem.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/inventory/Inventory.h"
#include "net/minecraft/world/item/InteractionResultHolder.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/MapItem.h"
#include "net/minecraft/world/stats/GenericStats.h"
#include "types.h"

EmptyMapItem::EmptyMapItem() : ComplexItem() {}

InteractionResultHolder EmptyMapItem::use(Level* level, std::shared_ptr<Player> user,
                                          InteractionHand::EInteractionHand hand) {
    not_null_ptr<ItemInstance> currMapItem = user->getItemInHand(hand);
    not_null_ptr<ItemInstance> mapItem = MapItem::setupNewMap(user->getPlayerUID(), level, user->mDimensionId,
                                                              user->mX, user->mZ, 3, true, false);

    currMapItem->shrink(1);
    if (currMapItem->isEmpty()) {
        return InteractionResultHolder(InteractionResult::SUCCESS, mapItem);
    } else {
        if (!user->mInventory->add(mapItem->copy()))
            user->drop(mapItem, false);

        user->awardStat(GenericStats::getItemsUsedStat(this),
                        GenericStats::param_itemsUsed(user, currMapItem));
        return InteractionResultHolder(InteractionResult::SUCCESS, currMapItem);
    }
}

unsigned int EmptyMapItem::GetUseTooltip(const ItemToolTipDataHolder& toolTipDataHolder) {
    return StringIDs::Use_1;
}
