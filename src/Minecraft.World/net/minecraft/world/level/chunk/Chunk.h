#pragma once

#include <unordered_map>

#include "nn/os/os_MutexTypes.h"

#include "net/minecraft/world/IntKey.h"

class AABB;
class BlockEntity;
class BlockState;
class Chunk;
class Level;
class TargetAreaRuleDefinition;

typedef std::unordered_map<int, std::vector<std::shared_ptr<BlockEntity>>, IntKeyHash, IntKeyEq>
    BlockEntityMap;

struct ClipChunk {
    Chunk* m_chunk;
    int m_globalIndex;
    bool m_needsUpdate;
    float m_worldAabbMinX;
    float m_worldAabbMinY;
    float m_worldAabbMinZ;
    float m_worldAabbMaxX;
    float m_worldAabbMaxY;
    float m_worldAabbMaxZ;
    int m_centerX;
    int m_centerY;
    int m_centerZ;
    int m_34;
};

class Chunk {
public:
    static int updates;  // Name from b1.2_02

    Chunk(Level* level, BlockEntityMap& map, nn::os::MutexType& mutex, int x, int y, int z,
          ClipChunk* clipChunk);
    Chunk();

    void setPos(int x, int y, int z);
    void reset();
    void translateToPos();
    void makeCopyForRebuild(Chunk* chunk);
    void rebuild();
    void _delete();
    void clearDirty();

    // TODO: Define these!!!
    static unsigned char* getBlockMemory();
    static unsigned char* getBlockDataMemory();
    static const BlockState** getBlockStateMemory();

private:
    Level* m_level;
    int m_x;
    int m_y;
    int m_z;
    int m_14;
    int m_18;
    int m_1c;
    int m_renderX;
    int m_renderY;
    int m_renderZ;
    int m_centerX;
    int m_centerY;
    int m_centerZ;
    AABB* m_aabb;
    bool m_isInitalized;
    ClipChunk* m_clipChunk;
    int m_dword50;
    BlockEntityMap* m_blockEntityMap;
    nn::os::MutexType* m_mutex;
    bool m_isPositionSet;
};
