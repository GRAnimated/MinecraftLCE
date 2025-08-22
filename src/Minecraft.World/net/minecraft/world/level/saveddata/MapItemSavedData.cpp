#include "net/minecraft/world/level/saveddata/MapItemSavedData.h"

#include <memory>

std::shared_ptr<Packet> MapItemSavedData::getUpdatePacket(not_null_ptr<ItemInstance> item, Level* level,
                                                          std::shared_ptr<Player> player) {
    if (auto it = this->mCarriedByPlayers.find(player); it != this->mCarriedByPlayers.end()) {
        std::shared_ptr<HoldingPlayer> holdingPlayer = it->second;
        return holdingPlayer->nextUpdatePacket(item);
    }

    return nullptr;
}
