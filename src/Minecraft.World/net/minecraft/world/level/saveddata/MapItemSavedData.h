#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/saveddata/SavedData.h"
#include "net/minecraft/world/level/saveddata/maps/MapDecoration.h"
#include "types.h"
#include <memory>
#include <string>
#include <unordered_map>

class Player;
class ItemInstance;
class Packet;
class Level;

class MapItemSavedData : public SavedData {
public:
    class HoldingPlayer {
    public:
        std::shared_ptr<Packet> nextUpdatePacket(not_null_ptr<ItemInstance>);

        std::shared_ptr<Player> m_player;
        bool m_dirty;
        int m_minDirtyX;
        int m_minDirtyY;
        int m_maxDirtyX;
        int m_maxDirtyY;
        int m_tick;
        int m_dword28;
        char m_gap2C[20];
        int m_step;
        bool m_byte44;
        MapItemSavedData* m_savedData;
    };

    MapItemSavedData(const std::wstring&);

    ~MapItemSavedData() override;
    void load(CompoundTag*) override;
    void save(CompoundTag*) override;

    void tickCarriedBy(std::shared_ptr<Player> player, not_null_ptr<ItemInstance> item);
    void mergeInMapData(std::shared_ptr<MapItemSavedData> mapData);
    void setOrigin(double x, double z, int scale);
    std::shared_ptr<Packet> getUpdatePacket(not_null_ptr<ItemInstance> item, Level* level,
                                            std::shared_ptr<Player> player);
    std::shared_ptr<HoldingPlayer> getHoldingPlayer(std::shared_ptr<Player>);
    void addDecoration(const MapDecoration::Type*, Level*, int, double, double, double, double, bool);
    std::vector<MapDecoration> fjGetAllDecorations();

    static void appendDecorations(std::vector<MapDecoration>* out,
                                  std::unordered_map<int, MapDecoration>* in) {
        for (auto& pair : *in) {
            out->push_back(pair.second);
        }
    }

    int m_xCenter;
    int m_zCenter;
    char m_dimension;
    bool m_trackingPosition;
    bool m_unlimitedTracking;
    unsigned char m_scale;
    arrayWithLength<uchar> m_colors;
    std::vector<std::shared_ptr<HoldingPlayer>> m_carriedBy;
    std::unordered_map<std::shared_ptr<Player>, std::shared_ptr<HoldingPlayer>> m_carriedByPlayers;
    std::unordered_map<int, MapDecoration> m_playerDecorations;
    long m_lastTick;
    std::unordered_map<int, MapDecoration> m_frameDecorations;
};
