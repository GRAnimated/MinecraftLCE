#include "net/minecraft/client/resources/IdMapper.h"
#include "net/minecraft/nbt/CompoundTag.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/entity/BlockEntity.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include <memory>

IdMapper<eINSTANCEOF> idMapper;

// NON_MATCHING: idMapper.addMapping should be a map push_back call
void BlockEntity::Register(int id, BlockEntityFunctor functor, eINSTANCEOF type, std::wstring name) {
    ResourceLocation location = ResourceLocation(name);
    std::wstring str = location.toString();

    blockEntityFactoryMap.insert({str, functor});
    idMapper.addMapping(type, id);

    location.Registry.registerMapping(id, location, type);
}

BlockEntity::BlockEntity() {
    mLevel = nullptr;
    mPos = BlockPos::zero;
    mIsRemoved = false;
    mData = -1;
    field_19 = false;
    mBlock = nullptr;
}

Level* BlockEntity::getLevel() {
    return mLevel;
}

void BlockEntity::setLevel(Level* level) {
    mLevel = level;
}

bool BlockEntity::hasLevel() {
    return mLevel != nullptr;
}

void BlockEntity::load(CompoundTag* tag) {
    mPos = BlockPos(tag->getInt(L"x"), tag->getInt(L"y"), tag->getInt(L"z"));
}

void BlockEntity::save(CompoundTag* tag) {
    saveMetadata(tag);
}

CompoundTag* BlockEntity::saveMetadata(CompoundTag* tag) {
    ResourceLocation location = ResourceLocation::Registry.getKey(GetType());

    tag->putString(L"id", location.toString());
    tag->putInt(L"x", mPos.getX());
    tag->putInt(L"y", mPos.getY());
    tag->putInt(L"z", mPos.getZ());

    return tag;
}

void BlockEntity::tick() {}

void BlockEntity::setLevelForLoading(Level*) {}

int BlockEntity::getData() {
    int data = mData;
    if (data != -1)
        return data;

    const BlockState* state = mLevel->getBlockState(mPos);
    Block* block = state->getBlock();
    mData = block->convertBlockStateToLegacyData(state);
    return mData;
}

void BlockEntity::setData(int data) {
    mData = data;
}

void BlockEntity::setChanged() {
    if (!mLevel)
        return;

    const BlockState* state = mLevel->getBlockState(mPos);
    Block* block = state->getBlock();
    mData = block->convertBlockStateToLegacyData(state);

    mLevel->blockEntityChanged(mPos, std::enable_shared_from_this<BlockEntity>::shared_from_this());

    if (getBlock() != Blocks::AIR) {
        mLevel->updateNeighbourForOutputSignal(mPos, getBlock());
    }
}

double BlockEntity::distanceToSqr(double x, double y, double z) {
    double distX = mPos.getX() + 0.5 - x;
    double distY = mPos.getY() + 0.5 - y;
    double distZ = mPos.getZ() + 0.5 - z;
    return (distX * distX) + (distY * distY) + (distZ * distZ);
}

double BlockEntity::getViewDistance() {
    return 4096.0f;
}

BlockPos BlockEntity::getBlockPos() {
    return mPos;
}

Block* BlockEntity::getBlock() {
    if (mBlock)
        return mBlock;

    if (!mLevel)
        return nullptr;

    const BlockState* state = mLevel->getBlockState(mPos);
    mBlock = state->getBlock();
    return mBlock;
}

std::shared_ptr<Packet> BlockEntity::getUpdatePacket() {
    return nullptr;
}

CompoundTag* BlockEntity::getUpdateTag() {
    CompoundTag* tag = new CompoundTag();
    return saveMetadata(tag);
}

CompoundTag* BlockEntity::getUpdateTagForPistonMovement() {
    return getUpdateTag();
}

bool BlockEntity::isRemoved() {
    return mIsRemoved;
}

void BlockEntity::setRemoved() {
    mIsRemoved = true;
}

void BlockEntity::clearRemoved() {
    mIsRemoved = false;
}

void BlockEntity::clearCache() {
    mBlock = nullptr;
    mData = -1;
}

void BlockEntity::setPosition(const BlockPos& pos) {
    mPos = pos;
}

bool BlockEntity::onlyOpCanSetNbt() {
    return false;
}

std::wstring BlockEntity::getDisplayName() {
    return L"";
}

void BlockEntity::rotate(Rotation*) {}

void BlockEntity::mirror(Mirror*) {}
