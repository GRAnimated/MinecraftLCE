#pragma once

#include "net/minecraft/core/BlockPos.h"
#include <string>
#include <vector>

class BlockState;
class CompoundTag;
class Rotation;
class Vec3;

class StructureTemplate {
public:
    struct BlockInfo {
        BlockInfo(const BlockPos&, const BlockState*, CompoundTag*);
        ~BlockInfo();
        BlockPos m_pos;
        const BlockState* m_state;  // Borrowed from the block-state registry.
        CompoundTag* m_tag;
    };
    struct EntityInfo {
        EntityInfo(Vec3*, const BlockPos&, CompoundTag*);
        ~EntityInfo();
        Vec3* m_pos;
        BlockPos m_blockPos;
        CompoundTag* m_tag;
    };

    StructureTemplate();
    virtual ~StructureTemplate();
    BlockPos getSize();
    BlockPos getSize(Rotation*);
    void loadTag(CompoundTag*);

    std::vector<const BlockState*> m_palette;
    std::vector<BlockInfo*> m_blocks;
    std::vector<EntityInfo*> m_entities;
    BlockPos m_size;
    std::wstring m_author;
};

static_assert(sizeof(StructureTemplate) == 0x78, "Original template allocation");
static_assert(sizeof(StructureTemplate::BlockInfo) == 0x20, "Original block record");
static_assert(sizeof(StructureTemplate::EntityInfo) == 0x20, "Original entity record");
