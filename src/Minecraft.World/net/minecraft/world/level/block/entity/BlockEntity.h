#pragma once

#include "types.h"
#include "net/minecraft/client/resources/IdMapper.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/nbt/CompoundTag.h"
#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include <memory>
#include <unordered_map>

class Level;
class Block;
class Rotation;
class Mirror;

class BlockEntity : public std::enable_shared_from_this<BlockEntity> {
public:
    using BlockEntityFunctor = BlockEntity* (*)();

    static std::unordered_map<std::wstring, BlockEntityFunctor, std::hash<std::wstring>,
                              std::equal_to<std::wstring>,
                              std::allocator<std::pair<const std::wstring, BlockEntityFunctor>>>
        blockEntityFactoryMap;

    static void Register(int, BlockEntityFunctor, eINSTANCEOF, std::wstring);

    BlockEntity();
    virtual eINSTANCEOF GetType();
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
    virtual double getViewDistance();
    virtual BlockPos getBlockPos();
    virtual Block* getBlock();
    virtual std::shared_ptr<Packet> getUpdatePacket();
    virtual CompoundTag* getUpdateTag();
    virtual CompoundTag* getUpdateTagForPistonMovement();
    virtual bool isRemoved();
    virtual void setRemoved();
    virtual void clearRemoved();
    virtual void triggerEvent(int, int);
    virtual void clearCache();
    virtual void setPosition(const BlockPos&);
    virtual bool onlyOpCanSetNbt();
    virtual std::wstring getDisplayName();
    virtual void rotate(Rotation*);
    virtual void mirror(Mirror*);

    CompoundTag* saveMetadata(CompoundTag*);

    void setRenderRemoveStage(unsigned char);
    bool shouldRemoveForRender() const { return mRenderFlag == 2; }

    bool mIsRemoved;
    bool field_19;
    u8 mRenderFlag;
    Level* mLevel;
    BlockPos mPos;
    int mData;
    Block* mBlock;
};

ASSERT_SIZEOF(BlockEntity, 0x40)
