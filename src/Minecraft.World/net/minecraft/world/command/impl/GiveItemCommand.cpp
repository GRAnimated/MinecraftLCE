#include "net/minecraft/world/command/impl/GiveItemCommand.h"

#include "java/io/ByteArrayInputStream.h"
#include "java/io/DataInputStream.h"
#include "net/minecraft/sounds/SoundEvent.h"
#include "net/minecraft/sounds/SoundSource.h"
#include "net/minecraft/world/PlayerUID.h"
#include "net/minecraft/world/command/Command.h"
#include "net/minecraft/world/command/EGameCommand.h"
#include "net/minecraft/world/entity/CommandSender.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/item/ItemEntity.h"
#include "net/minecraft/world/entity/player/ServerPlayer.h"
#include "net/minecraft/world/inventory/Inventory.h"
#include "net/minecraft/world/inventory/InventoryMenu.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "types.h"
#include <memory>
#include <string>

GiveItemCommand::GiveItemCommand() : Command() {}

EGameCommand GiveItemCommand::getId() {
    return eGiveItemCommand;
}

int GiveItemCommand::getPermissionLevel() {
    return 2;
}

// NON_MATCHING: good luck matching this pile of crap, if statements hell
void GiveItemCommand::execute(std::shared_ptr<CommandSender> sender, arrayWithLength<uchar> input) {
    ByteArrayInputStream byteInputStream = ByteArrayInputStream(input);
    DataInputStream dataInputStream = DataInputStream(&byteInputStream);
    PlayerUID playerUID = dataInputStream.readPlayerUID();
    int id = dataInputStream.readInt();
    int count = dataInputStream.readInt();
    int aux = dataInputStream.readInt();
    std::wstring name = dataInputStream.readUTF();
    /*byteInputStream
        = ByteArrayInputStream(); */ // this doesn't exist on WiiU, i'm just guessing it does this... why? idk

    std::shared_ptr<ServerPlayer> player = this->getPlayer(playerUID);
    if (id < 1 || !player || !Item::byId(id))
        return;

    not_null_ptr<ItemInstance> item = new ItemInstance(Item::byId(id), count, aux);
    bool added = player->m_inventory->add(item);
    if (added) {
        player->m_level->playSound(
            nullptr, player->m_x, player->m_y, player->m_z, SoundEvent::ITEM_PICKUP, SoundSource::PLAYERS,
            0.2f,
            ((player->getRandom()->nextFloat() - player->getRandom()->nextFloat()) * 0.7f + 1.0f) * 2.0f,
            16.0f);
        player->m_inventoryMenu->broadcastChanges();
    }

    if (added && item->getCount() >= 1) {
        item->setCount(1);
        sender->setCommandStats((CommandStats::CommandStatType)3, count);
        std::shared_ptr<ItemEntity> itemEnt = player->drop(item, false);
        if (itemEnt)
            itemEnt->makeFakeItem();
    } else {
        sender->setCommandStats((CommandStats::CommandStatType)3, count - item->getCount());
        std::shared_ptr<ItemEntity> itemEnt = player->drop(item, false);
        if (itemEnt) {
            itemEnt->setNoPickUpDelay();
            itemEnt->setOwner(player->getName());
        }
    }

    std::wstring message;
    message += (L"commands.give.success");
    Command::logAdminAction(sender, (ClientboundChatPacket::EChatPacketMessage)0, &id, 1, &message, 2);
}
