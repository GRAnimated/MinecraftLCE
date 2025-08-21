#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/saveddata/MapItemSavedData.h"
#include "net/minecraft/world/level/storage/LevelData.h"
#include <memory>

std::shared_ptr<Packet> MapItemSavedData::getUpdatePacket(not_null_ptr<ItemInstance> item, Level* level,
                                                          std::shared_ptr<Player> player) {
    if (auto it = this->mCarriedByPlayers.find(player); it != this->mCarriedByPlayers.end()) {
        std::shared_ptr<HoldingPlayer> holdingPlayer = it->second;
        return holdingPlayer->nextUpdatePacket(item);
    }

    return nullptr;
}
