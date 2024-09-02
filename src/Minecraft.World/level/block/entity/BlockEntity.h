#pragma once

#include <memory>
#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Nbt/CompoundTag.h"
#include "types.h"

class Level;
class Block;
class Rotation;
class Mirror;

class BlockEntity : public std::enable_shared_from_this<BlockEntity> {
public:
    BlockEntity();
    virtual ~BlockEntity();
    virtual Level* getLevel();
    virtual void setLevel(Level*);
    virtual bool hasLevel();
    virtual void load(CompoundTag*);
    virtual void save(CompoundTag*);
    virtual void tick();
    virtual void setLevelForLoading(Level*);
    virtual int getData();
    virtual void setData(int);
    virtual void setChanged();
    virtual double distanceToSqr(double, double, double);
    virtual void getViewDistance();
    virtual BlockPos getBlockPos();
    virtual Block* getBlock();
    virtual void getUpdatePacket();
    virtual void getUpdateTag();
    virtual void getUpdateTagForPistonMovement();
    virtual bool isRemoved();
    virtual void setRemoved();
    virtual void clearRemoved();
    virtual void triggerEvent(int, int);
    virtual void clearCache();
    virtual void setPosition(BlockPos const&);
    virtual void onlyOpCanSetNbt();
    virtual void getDisplayName();
    virtual void rotate(Rotation*);
    virtual void mirror(Mirror*);

    void saveMetadata(CompoundTag*);

    bool mIsRemoved;
    bool field_19;
    Level* mLevel;
    BlockPos mPos;
    int mData;
    Block* mBlock;
};

ASSERT_SIZEOF(BlockEntity, 0x40)