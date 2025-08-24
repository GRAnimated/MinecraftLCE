#include "MapItem.h"
#include "NX/Platform.h"
#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/inventory/InventoryMenu.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/dimension/Dimension.h"
#include "net/minecraft/world/level/saveddata/MapItemSavedData.h"
#include "net/minecraft/world/level/storage/LevelData.h"
#include <memory>
#include <string>

MapItem::MapItem() : ComplexItem() {
    this->setStackedByData(true);
}

std::shared_ptr<MapItemSavedData> MapItem::getSavedData(not_null_ptr<ItemInstance> itemInstance,
                                                        Level* level) {
    return this->getSavedData(itemInstance->getAuxValue(), level);
}

// NON_MATCHING: the "map_" strings shit needs to get fixed
std::shared_ptr<MapItemSavedData> MapItem::getSavedData(int mapAux, Level* level) {
    MemSect(31);  // are they fucking crazy?????????
    // this shit below is 99% wrong too but I don't have a damn clue what's that pile of crap is
    // supposed to be
    std::wstring mapId = L"map_";
    mapId += std::to_wstring(mapAux);
    MemSect(0);

    std::shared_ptr<MapItemSavedData> savedData
        = std::static_pointer_cast<MapItemSavedData>(level->getSavedData(typeid(MapItemSavedData), mapId));

    if (!savedData && !level->mIsLocal) {
        mapId = L"map_" + std::to_wstring(mapAux);

        savedData = std::shared_ptr<MapItemSavedData>(new MapItemSavedData(mapId));
        savedData->mScale = 3;
        savedData->setOrigin(level->getLevelData()->getXSpawn(), level->getLevelData()->getZSpawn(),
                             savedData->mScale);
        savedData->mDimension = level->mDimension->getType()->getId();
        savedData->setDirty();
        level->setSavedData(mapId, savedData);
    }

    if (savedData) {
        if (savedData->mScale >= 5) {
            savedData->mScale = 4;
        }
    }

    return savedData;
}

// NON_MATCHING: this is completly random shit just to make MapItem::inventoryTick match
void MapItem::update(Level* level, std::shared_ptr<Entity> ent, std::shared_ptr<MapItemSavedData> savedData) {
    level->addEntity(ent);
    savedData = nullptr;
}

void MapItem::inventoryTick(not_null_ptr<ItemInstance> itemInstance, Level* level,
                            std::shared_ptr<Entity> ent, int slot, bool inHand) {
    if (!level->mIsLocal) {
        std::shared_ptr<MapItemSavedData> mapSavedData = this->getSavedData(itemInstance, level);
        if (ent->isType(ePlayer)) {
            std::shared_ptr<Player> player = std::static_pointer_cast<Player>(ent);
            int aux = level->getAuxValueForMap(player->getPlayerUID(), mapSavedData->mDimension,
                                               mapSavedData->mXCenter, mapSavedData->mZCenter,
                                               mapSavedData->mScale);
            if (aux != itemInstance->getAuxValue()) {
                std::shared_ptr<MapItemSavedData> mapDataAux = this->getSavedData(aux, level);

                mapDataAux->mXCenter = mapSavedData->mXCenter;
                mapDataAux->mZCenter = mapSavedData->mZCenter;
                mapDataAux->mScale = mapSavedData->mScale;
                mapDataAux->mDimension = mapSavedData->mDimension;
                mapDataAux->mTrackingPosition
                    = mapDataAux->mTrackingPosition ? true : mapSavedData->mTrackingPosition;

                itemInstance->setAuxValue(aux);

                mapDataAux->tickCarriedBy(player, itemInstance);
                mapDataAux->mergeInMapData(mapSavedData);
                player->mInventoryMenu->broadcastChanges();

                mapSavedData = mapDataAux;
            } else {
                mapSavedData->tickCarriedBy(player, itemInstance);
            }
        }
        if (inHand
            || (ent->isType(ePlayer)
                && std::static_pointer_cast<Player>(ent)->getOffhandItem() == itemInstance)) {
            this->update(level, ent, mapSavedData);
        }
    }
}

void MapItem::onCraftedBy(not_null_ptr<ItemInstance> itemInstance, Level* level,
                          std::shared_ptr<Player> player) {
    CompoundTag* tag = itemInstance->getTag();

    if (tag) {
        if (tag->contains(L"map_scale_direction", 99)) {
            scaleMap(itemInstance, level, tag->getInt(L"map_scale_direction"));
            tag->remove(L"map_scale_direction");
        } else if (tag->getBoolean(L"map_tracking_position")) {
            enableMapTracking(itemInstance, level);
            tag->remove(L"map_tracking_position");
        }
    }
}

void MapItem::registerIcons(IconRegister* iconReg) {
    this->MAP_FILLED_MARKINGS = iconReg->registerIcon(L"map_filled_markings");
}

bool MapItem::hasMultipleSpriteLayers() {
    return true;
}

TextureAtlasSprite* MapItem::getLayerIcon(int a2, int layer) {
    return layer == 1 ? this->MAP_FILLED_MARKINGS : Item::getLayerIcon(a2, layer);
}

// NON_MATCHING: fix that MapItemSavedData::getUpdatePacket impl is skipped while "optimising" and doesn't
// strip level arg being passed
std::shared_ptr<Packet> MapItem::getUpdatePacket(not_null_ptr<ItemInstance> itemInstance, Level* level,
                                                 std::shared_ptr<Player> player) {
    return this->getSavedData(itemInstance, level)->getUpdatePacket(itemInstance, level, player);
}
