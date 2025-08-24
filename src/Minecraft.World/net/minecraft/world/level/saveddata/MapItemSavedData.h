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

        std::shared_ptr<Player> mPlayer;
        bool mDirty;
        int mMinDirtyX;
        int mMinDirtyY;
        int mMaxDirtyX;
        int mMaxDirtyY;
        int mTick;
        int dword28;
        char gap2C[20];
        int mStep;
        bool byte44;
        MapItemSavedData* mSavedData;
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

    int mXCenter;
    int mZCenter;
    char mDimension;
    bool mTrackingPosition;
    bool mUnlimitedTracking;
    unsigned char mScale;
    arrayWithLength<uchar> mColors;
    std::vector<std::shared_ptr<HoldingPlayer>> mCarriedBy;
    std::unordered_map<std::shared_ptr<Player>, std::shared_ptr<HoldingPlayer>> mCarriedByPlayers;
    std::unordered_map<int, MapDecoration> mPlayerDecorations;
    long mLastTick;
    std::unordered_map<int, MapDecoration> mFrameDecorations;
};
