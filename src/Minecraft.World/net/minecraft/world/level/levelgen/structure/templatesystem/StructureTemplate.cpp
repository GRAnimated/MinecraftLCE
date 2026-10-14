#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureTemplate.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/world/level/block/Rotation.h"
#include "net/minecraft/world/phys/Vec3.h"

StructureTemplate::StructureTemplate() {
    m_size = BlockPos::zero;
    m_author.assign(L"?");
}

StructureTemplate::~StructureTemplate() {
    for (auto* block : m_blocks)
        delete block;
    for (auto* entity : m_entities)
        delete entity;
}

StructureTemplate::BlockInfo::BlockInfo(const BlockPos& pos, const BlockState* state, CompoundTag* tag) {
    m_pos = pos;
    m_state = state;
    m_tag = tag;
}
StructureTemplate::BlockInfo::~BlockInfo() {
    delete m_tag;
}

StructureTemplate::EntityInfo::EntityInfo(Vec3* pos, const BlockPos& blockPos, CompoundTag* tag) {
    m_pos = pos;
    m_blockPos = blockPos;
    m_tag = tag;
}
StructureTemplate::EntityInfo::~EntityInfo() {
    delete m_pos;
    delete m_tag;
}

BlockPos StructureTemplate::getSize() {
    return m_size;
}
BlockPos StructureTemplate::getSize(Rotation* rotation) {
    const auto type = rotation->getType();
    if ((type | 2) == 3)
        return BlockPos(m_size.getZ(), m_size.getY(), m_size.getX());
    return m_size;
}
