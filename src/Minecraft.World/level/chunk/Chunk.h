#pragma once

#include <unordered_map>

#include "nn/os/os_MutexTypes.h"

class AABB;
class BlockEntity;
class BlockState;
class Chunk;
class Level;
class TargetAreaRuleDefinition;

struct IntKeyHash {
    // NON_MATCHING
    std::size_t operator()(int key) const noexcept { return std::hash<int>{}(key); }
};

struct IntKeyEq {
    // NON_MATCHING
    bool operator()(int lhs, int rhs) const noexcept { return lhs == rhs; }
};

typedef std::unordered_map<int, std::vector<std::shared_ptr<BlockEntity>>, IntKeyHash, IntKeyEq>
    BlockEntityMap;

struct ClipChunk {
    Chunk* mChunk;
    int mGlobalIndex;
    bool mNeedsUpdate;
    float mWorldAabbMinX;
    float mWorldAabbMinY;
    float mWorldAabbMinZ;
    float mWorldAabbMaxX;
    float mWorldAabbMaxY;
    float mWorldAabbMaxZ;
    int mCenterX;
    int mCenterY;
    int mCenterZ;
    int _34;
};

class Chunk {
public:
    static int updates;  // Name from b1.2_01

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
    Level* mLevel;
    int mX;
    int mY;
    int mZ;
    int _14;
    int _18;
    int _1c;
    int mRenderX;
    int mRenderY;
    int mRenderZ;
    int mCenterX;
    int mCenterY;
    int mCenterZ;
    AABB* mAABB;
    bool mIsInitalized;
    ClipChunk* mClipChunk;
    int dword_50;
    BlockEntityMap* mBlockEntityMap;
    nn::os::MutexType* mMutex;
    bool mIsPositionSet;
};
