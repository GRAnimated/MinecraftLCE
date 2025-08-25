#include "net/minecraft/world/level/saveddata/MapItemSavedData.h"

#include "NX/Platform.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/saveddata/maps/MapDecoration.h"
#include "net/minecraft/world/level/storage/LevelData.h"

#include <memory>
#include <unordered_map>
#include <vector>

std::shared_ptr<Packet> MapItemSavedData::getUpdatePacket(not_null_ptr<ItemInstance> item, Level* level,
                                                          std::shared_ptr<Player> player) {
    if (auto it = this->mCarriedByPlayers.find(player); it != this->mCarriedByPlayers.end()) {
        std::shared_ptr<HoldingPlayer> holdingPlayer = it->second;
        return holdingPlayer->nextUpdatePacket(item);
    }

    return nullptr;
}

void MapItemSavedData::addDecoration(const MapDecoration::Type* type, Level* level, int id, double worldX,
                                     double worldY, double worldZ, double rotation, bool idk) {
    int scaleFactor = 1 << this->mScale;
    float relX = (float)(worldX - this->mXCenter) / (float)scaleFactor;
    float relZ = (float)(worldZ - this->mZCenter) / (float)scaleFactor;

    char posX = (relX * 2.0f) + 0.5;
    char posZ = (relZ * 2.0f) + 0.5;
    char rot;
    char eee = 63;  // wtf? without this it won't match (won't produce the ifs as I want)

    bool isPlayer = type->isPlayer();
    std::unordered_map<int, MapDecoration>* targetMap
        = isPlayer ? &this->mPlayerDecorations : &this->mFrameDecorations;

    if (relX >= -63.0f && relZ >= -63.0f && relX <= 63.0f && relZ <= 63.0f) {
        rotation = rotation + (rotation < 0.0 ? -8.0 : 8.0);
        rot = rotation * 16.0 / 360.0;
        if (this->mDimension < 0) {
            int dayTicks = level->getLevelData()->getDayTime() / 10;
            rot = ((dayTicks * dayTicks * 34187121 + dayTicks * 121) >> 15) & 15;
        }
    } else {
        if (isPlayer) {
            if (Mth::abs(relX) < 320.0f && Mth::abs(relZ) < 320.0f) {
                type = &(
                    &MapDecoration::Type::PLAYER_WHITE)[type->getIcon() + 16];  // jump to OFF_LIMITS colors
            } else if (!this->mUnlimitedTracking) {
                targetMap->erase(id);
                return;
            }

            if (relX <= -63.0f) {
                posX = -128;
            }
            if (relZ <= -63.0f) {
                posZ = -128;
            }
            if (relX >= 63.0f) {
                posX = 127;
            }
            if (relZ >= 63.0f) {
                posZ = 127;
            }
            rot = 0;
        } else if (type == &(&MapDecoration::Type::PLAYER_WHITE)[4]) {
            type = &(&MapDecoration::Type::PLAYER_WHITE)[4];

            rot = 0;
            if (relX <= -63.0f) {
                posX = -128;
            }
            if (relZ <= -63.0f) {
                posZ = -128;
            }
            if (relX >= 63.0f) {
                posX = 127;
            }
            if (relZ >= 63.0f) {
                posZ = 127;
            }
        } else {
            targetMap->erase(id);
            return;
        }
    }

    MemSect(45);
    (*targetMap)[id] = MapDecoration(type, posX, posZ, rot, id, idk);
    MemSect(0);
}

std::vector<MapDecoration> MapItemSavedData::fjGetAllDecorations() {
    std::vector<MapDecoration> combined;
    appendDecorations(&combined, &this->mPlayerDecorations);
    appendDecorations(&combined, &this->mFrameDecorations);
    return combined;
}
