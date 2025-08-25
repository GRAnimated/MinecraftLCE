#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/world/PlayerUID.h"
#include "net/minecraft/world/item/ComplexItem.h"
#include "types.h"

class MapItemSavedData;

class MapItem : public ComplexItem {
public:
    static not_null_ptr<ItemInstance> setupNewMap(PlayerUID, Level*, int, double, double, unsigned char, bool,
                                                  bool);
    static void scaleMap(not_null_ptr<ItemInstance>, Level*, int);
    static void enableMapTracking(not_null_ptr<ItemInstance>, Level*);

    MapItem();

    std::shared_ptr<MapItemSavedData> getSavedData(int mapAux, Level* level);
    std::shared_ptr<MapItemSavedData> getSavedData(not_null_ptr<ItemInstance> itemInstance, Level* level);
    void update(Level*, std::shared_ptr<Entity>, std::shared_ptr<MapItemSavedData>);

    void inventoryTick(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<Entity>, int, bool) override;
    void onCraftedBy(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<Player>) override;
    void registerIcons(IconRegister*) override;
    bool hasMultipleSpriteLayers() override;
    TextureAtlasSprite* getLayerIcon(int, int) override;
    std::shared_ptr<Packet> getUpdatePacket(not_null_ptr<ItemInstance>, Level*,
                                            std::shared_ptr<Player>) override;

    TextureAtlasSprite* MAP_FILLED_MARKINGS;
};
