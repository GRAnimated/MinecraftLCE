#include "net/minecraft/world/level/chunk/LevelChunk.h"

#include "net/minecraft/world/level/Level.h"

#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/entity/BlockEntity.h"
#include "net/minecraft/world/level/dimension/Dimension.h"

void LevelChunk::staticCtor() {
    InitializeCriticalSection(&LevelChunk::mMutex_710178c150);
    InitializeCriticalSection(&LevelChunk::mMutex_710178c170);
    InitializeCriticalSection(&LevelChunk::mMutex_710178c190);
}

void LevelChunk::tick(bool skipRecheckGaps) {
    if (this->m_tickSkylight && this->m_level->mDimension->isHasSkyLight() && !skipRecheckGaps) {
        PIXBeginNamedEvent(0.0, "Check for gaps");
        this->recheckGaps(this->m_level->mIsLocal);
        PIXEndNamedEvent();
    }

    this->unk11 = true;

    if (!this->m_hasPostProcessed && this->m_populatedFlags & FLAG_TERRAIN_POPULATED) {
        PIXBeginNamedEvent(0.0, "postProcess");
        this->postProcess();
        PIXEndNamedEvent();
    }

    PIXBeginNamedEvent(0.0, "Process block entities");
    while (!this->m_blockEntityPosTickQueue.empty()) {
        BlockPos pos = this->m_blockEntityPosTickQueue.front();
        this->m_blockEntityPosTickQueue.pop_front();

        if (this->getBlockEntity(pos, static_cast<EntityCreationType>(2)) == nullptr
            && this->getBlock(pos)->isBlockEntity()) {
            std::shared_ptr<BlockEntity> bl = this->createBlockEntity(pos);
            this->m_level->setBlockEntity(pos, bl);
            this->m_level->setBlocksDirty(pos, pos);
        }
    }
    PIXEndNamedEvent();
}

void LevelChunk::postProcess() {
    this->m_hasPostProcessed = true;
}

void LevelChunk::writeCompressedDataData(DataOutputStream* out) {
    m_dataDataLower->write(out);
    m_dataDataUpper->write(out);
}

bool LevelChunk::DECOMP_getUnknownField() {
    return unk8;
}

void LevelChunk::writeCompressedBlockData(DataOutputStream* out) {
    m_blockDataLower->write(out);
    m_blockDataUpper->write(out);
}

void LevelChunk::writeCompressedSkyLightData(DataOutputStream* out) {
    m_skyLightDataLower->write(out);
    m_skyLightDataUpper->write(out);
}

void LevelChunk::writeCompressedBlockLightData(DataOutputStream* out) {
    m_blockLightDataLower->write(out);
    m_blockLightDataUpper->write(out);
}

ChunkPos LevelChunk::getPos() {
    return ChunkPos(this->m_xPos, this->m_zPos);
}

bool LevelChunk::isTerrainPopulated() {
    return (this->m_populatedFlags >> 8 & 0xFF) >> 2 & 1;
}

Block* LevelChunk::GetBlock(CompressedBlockStorage* storage, int x, int y, int z) {
    const int y0 = y < 0 ? y + 127 : y;
    return Block::byId(storage->get(x, y - (y0 & 0xFFFFFF80), z) & 0xFF);
}
