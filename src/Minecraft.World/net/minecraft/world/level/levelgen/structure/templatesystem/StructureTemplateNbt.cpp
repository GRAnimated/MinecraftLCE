#include "com/mojang/nbt/CompoundTag.h"
#include "com/mojang/nbt/ListTag.h"
#include "com/mojang/nbt/NbtUtils.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureTemplate.h"
#include "net/minecraft/world/phys/Vec3.h"

void StructureTemplate::loadTag(CompoundTag* tag) {
    for (auto* block : m_blocks)
        delete block;
    for (auto* entity : m_entities)
        delete entity;
    m_blocks.clear();
    m_entities.clear();
    m_palette.clear();

    ListTag* size = tag->getList(L"size", Tag::TAG_Int);
    int x = size->getInt(0);
    int y = size->getInt(1);
    int z = size->getInt(2);
    m_size = BlockPos(x, y, z);
    m_author = tag->getString(L"author");

    ListTag* palette = tag->getList(L"palette", Tag::TAG_Compound);
    for (int i = 0; i < static_cast<int>(palette->size()); ++i) {
        const BlockState* state = NbtUtils::readBlockState(palette->getCompound(i));
        m_palette.push_back(state);
    }

    ListTag* blocks = tag->getList(L"blocks", Tag::TAG_Compound);
    for (int i = 0; i < static_cast<int>(blocks->size()); ++i) {
        CompoundTag* block = blocks->getCompound(i);
        ListTag* pos = block->getList(L"pos", Tag::TAG_Int);
        x = pos->getInt(0);
        y = pos->getInt(1);
        z = pos->getInt(2);
        BlockPos blockPos(x, y, z);
        int index = block->getInt(L"state");
        const BlockState* state = static_cast<size_t>(index) < m_palette.size() ?
                                      m_palette[index] :
                                      Blocks::AIR->defaultBlockState();
        CompoundTag* nbt = block->contains(L"nbt") ? block->getCompound(L"nbt")->copy() : nullptr;
        BlockInfo* info = new BlockInfo(blockPos, state, nbt);
        m_blocks.push_back(info);
    }

    ListTag* entities = tag->getList(L"entities", Tag::TAG_Compound);
    for (int i = 0; i < static_cast<int>(entities->size()); ++i) {
        CompoundTag* entity = entities->getCompound(i);
        ListTag* pos = entity->getList(L"pos", Tag::TAG_Double);
        double px = pos->getDouble(0);
        double py = pos->getDouble(1);
        double pz = pos->getDouble(2);
        Vec3* entityPos = Vec3::newPermanent(px, py, pz);
        ListTag* blockPosTag = entity->getList(L"blockPos", Tag::TAG_Int);
        x = blockPosTag->getInt(0);
        y = blockPosTag->getInt(1);
        z = blockPosTag->getInt(2);
        BlockPos blockPos(x, y, z);
        if (entity->contains(L"nbt")) {
            CompoundTag* nbt = entity->getCompound(L"nbt")->copy();
            EntityInfo* info = new EntityInfo(entityPos, blockPos, nbt);
            m_entities.push_back(info);
        }
    }
}
