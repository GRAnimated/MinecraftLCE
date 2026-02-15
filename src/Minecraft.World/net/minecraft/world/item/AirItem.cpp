#include "net/minecraft/world/item/AirItem.h"
#include "net/minecraft/world/level/block/Block.h"

AirItem::AirItem(Block* block) : Item() {
    m_block = block;
}

unsigned int AirItem::getDescriptionId(not_null_ptr<ItemInstance> itemInstance) {
    return m_block->getDescriptionId(-1);
}

void AirItem::appendHoverText(not_null_ptr<ItemInstance> itemInstance, std::shared_ptr<Player> player,
                              void* htmlString, bool unk) {
    Item::appendHoverText(itemInstance, player, htmlString, unk);
    m_block->appendHoverText(itemInstance, player, (std::vector<HtmlString>*)htmlString, unk);
}
