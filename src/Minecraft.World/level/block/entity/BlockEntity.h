#pragma once

#include <memory>
#include <unordered_map>
#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Core/IdMapper.h"
#include "Minecraft.Nbt/CompoundTag.h"
#include "Minecraft.Network/protocol/Packet.h"
#include "Minecraft.World/eINSTANCEOF.h"
#include "types.h"

class Level;
class Block;
class Rotation;
class Mirror;

class BlockEntity : public std::enable_shared_from_this<BlockEntity> {
public:
    using BlockEntityFunctor = BlockEntity* (*)();

    static std::unordered_map<std::wstring, BlockEntityFunctor, std::hash<std::wstring>, std::equal_to<std::wstring>, std::allocator<std::pair<const std::wstring, BlockEntityFunctor>>>
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
    virtual void setPosition(BlockPos const&);
    virtual bool onlyOpCanSetNbt();
    virtual std::wstring getDisplayName();
    virtual void rotate(Rotation*);
    virtual void mirror(Mirror*);

    CompoundTag* saveMetadata(CompoundTag*);

    bool mIsRemoved;
    bool field_19;
    Level* mLevel;
    BlockPos mPos;
    int mData;
    Block* mBlock;
};

ASSERT_SIZEOF(BlockEntity, 0x40)
