#include "net/minecraft/world/level/block/entity/BlockEntity.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/client/resources/IdMapper.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
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
    m_level = nullptr;
    m_pos = BlockPos::zero;
    m_isRemoved = false;
    m_data = -1;
    m_field19 = false;
    m_block = nullptr;
}

BlockEntity::~BlockEntity() {}

Level* BlockEntity::getLevel() {
    return m_level;
}

void BlockEntity::setLevel(Level* level) {
    m_level = level;
}

bool BlockEntity::hasLevel() {
    return m_level != nullptr;
}

void BlockEntity::load(CompoundTag* tag) {
    m_pos = BlockPos(tag->getInt(L"x"), tag->getInt(L"y"), tag->getInt(L"z"));
}

void BlockEntity::save(CompoundTag* tag) {
    saveMetadata(tag);
}

CompoundTag* BlockEntity::saveMetadata(CompoundTag* tag) {
    ResourceLocation location = ResourceLocation::Registry.getKey(GetType());

    tag->putString(L"id", location.toString());
    tag->putInt(L"x", m_pos.getX());
    tag->putInt(L"y", m_pos.getY());
    tag->putInt(L"z", m_pos.getZ());

    return tag;
}

void BlockEntity::tick() {}

void BlockEntity::setLevelForLoading(Level*) {}

int BlockEntity::getData() {
    int data = m_data;
    if (data != -1)
        return data;

    const BlockState* state = m_level->getBlockState(m_pos);
    Block* block = state->getBlock();
    m_data = block->convertBlockStateToLegacyData(state);
    return m_data;
}

void BlockEntity::setData(int data) {
    m_data = data;
}

void BlockEntity::setChanged() {
    if (!m_level)
        return;

    const BlockState* state = m_level->getBlockState(m_pos);
    Block* block = state->getBlock();
    m_data = block->convertBlockStateToLegacyData(state);

    m_level->blockEntityChanged(m_pos, std::enable_shared_from_this<BlockEntity>::shared_from_this());

    if (getBlock() != Blocks::AIR) {
        m_level->updateNeighbourForOutputSignal(m_pos, getBlock());
    }
}

double BlockEntity::distanceToSqr(double x, double y, double z) {
    double distX = m_pos.getX() + 0.5 - x;
    double distY = m_pos.getY() + 0.5 - y;
    double distZ = m_pos.getZ() + 0.5 - z;
    return (distX * distX) + (distY * distY) + (distZ * distZ);
}

double BlockEntity::getViewDistance() {
    return 4096.0f;
}

BlockPos BlockEntity::getBlockPos() {
    return m_pos;
}

Block* BlockEntity::getBlock() {
    if (m_block)
        return m_block;

    if (!m_level)
        return nullptr;

    const BlockState* state = m_level->getBlockState(m_pos);
    m_block = state->getBlock();
    return m_block;
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
    return m_isRemoved;
}

void BlockEntity::setRemoved() {
    m_isRemoved = true;
}

void BlockEntity::clearRemoved() {
    m_isRemoved = false;
}

void BlockEntity::clearCache() {
    m_block = nullptr;
    m_data = -1;
}

void BlockEntity::setPosition(const BlockPos& pos) {
    m_pos = pos;
}

bool BlockEntity::onlyOpCanSetNbt() {
    return false;
}

std::wstring BlockEntity::getDisplayName() {
    return L"";
}

void BlockEntity::rotate(Rotation*) {}

void BlockEntity::mirror(Mirror*) {}
