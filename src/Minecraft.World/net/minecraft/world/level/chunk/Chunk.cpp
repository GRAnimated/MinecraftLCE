#include "net/minecraft/world/level/chunk/Chunk.h"

#include "NX/Platform.h"
#include "NX/Render/RendererCore.h"
#include "com/mojang/blaze3d/platform/GlStateManager.h"
#include "com/mojang/blaze3d/vertex/BufferBuilder.h"
#include "com/mojang/blaze3d/vertex/Tesselator.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/renderer/BlockRenderer.h"
#include "net/minecraft/client/renderer/LevelRenderer.h"
#include "net/minecraft/client/renderer/blockentity/BlockEntityRenderDispatcher.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/entity/BlockEntity.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"
#include "net/minecraft/world/level/gamemode/minigames/glide/GlideRingGenerator.h"
#include "net/minecraft/world/level/gamemode/minigames/glide/rules/TargetAreaRuleDefinition.h"
#include "net/minecraft/world/level/storage/Region.h"
#include "net/minecraft/world/phys/AABB.h"
#include "net/minecraft/world/phys/Vec3.h"

Chunk::Chunk(Level* level, BlockEntityMap& map, nn::os::MutexType& mutex, int x, int y, int z,
             ClipChunk* clipChunk) {
    mBlockEntityMap = &map;
    mMutex = &mutex;
    clipChunk->mNeedsUpdate = false;
    mLevel = level;
    mAABB = nullptr;
    dword_50 = 0;
    mIsPositionSet = false;
    mClipChunk = clipChunk;
    clipChunk->mChunk = this;

    setPos(x, y, z);
    mIsInitalized = true;
}

Chunk::Chunk() {
    mIsInitalized = false;
}

void Chunk::setPos(int x, int y, int z) {
    if (!mIsPositionSet || mX != x || mY != y || mZ != z) {
        reset();

        mX = x;
        mY = y;
        mZ = z;
        mCenterX = x + 8;
        mCenterY = y + 8;
        mCenterZ = z + 8;
        mClipChunk->mCenterX = mCenterX;
        mClipChunk->mCenterY = mCenterY;
        mClipChunk->mCenterZ = mCenterZ;
        mClipChunk->mGlobalIndex = LevelRenderer::getGlobalIndexForChunk(x, y, z, mLevel);
        AABB* aabb = mAABB;
        _1c = 0;
        mRenderX = x;
        mRenderY = y;
        mRenderZ = z;
        _14 = 0;
        _18 = 0;
        if (!aabb) {
            mAABB = AABB::newPermanent(-6.0, -6.0, -6.0, 22.0, 22.0, 22.0);
        }
        mClipChunk->mWorldAabbMinX = mAABB->min.x + x;
        mClipChunk->mWorldAabbMinY = mAABB->min.y + y;
        mClipChunk->mWorldAabbMinZ = mAABB->min.z + z;
        mClipChunk->mWorldAabbMaxX = mAABB->max.x + x;
        mClipChunk->mWorldAabbMaxY = mAABB->max.y + y;
        mClipChunk->mWorldAabbMaxZ = mAABB->max.z + z;

        mIsPositionSet = true;

        EnterCriticalSection(&LevelRenderer::sInstance->mMutex);

        if (LevelRenderer::sInstance->incGlobalChunkRefCount(x, y, z, mLevel) == 1) {
            LevelRenderer::sInstance->setGlobalChunkFlag(x, y, z, mLevel, 2, 0);
            PIXSetMarkerDeprecated(0.0f, "Non-stack event pushed");
        }

        LeaveCriticalSection(&LevelRenderer::sInstance->mMutex);
    }
}

void Chunk::reset() {
    if (mIsPositionSet) {
        EnterCriticalSection(&LevelRenderer::sInstance->mMutex);
        unsigned char dec = LevelRenderer::sInstance->decGlobalChunkRefCount(mX, mY, mZ, mLevel);
        mIsPositionSet = false;
        if (!dec) {
            int index = LevelRenderer::sInstance->getGlobalIndexForChunk(mX, mY, mZ, mLevel);
            if (index >= 0) {
                int offset = 3 * index + LevelRenderer::sInstance->_100;
                Renderer* renderer = Renderer::sInstance;
                renderer->CBuffClear(offset);
                renderer->CBuffClear(offset + 1);
                renderer->CBuffClear(offset + 2);
                LevelRenderer::sInstance->setGlobalChunkFlags(mX, mY, mZ, mLevel, 0);
            }
        }
        LeaveCriticalSection(&LevelRenderer::sInstance->mMutex);
    }
    mClipChunk->mNeedsUpdate = 0;
}

void Chunk::translateToPos() {
    GlStateManager::translatef(mRenderX, mRenderY, mRenderZ);
}

void Chunk::makeCopyForRebuild(Chunk* chunk) {
    mLevel = chunk->mLevel;
    mX = chunk->mX;
    mY = chunk->mY;
    mZ = chunk->mZ;
    _14 = chunk->_14;
    _18 = chunk->_18;
    _1c = chunk->_1c;
    mRenderX = chunk->mRenderX;
    mRenderY = chunk->mRenderY;
    mRenderZ = chunk->mRenderZ;
    mCenterX = chunk->mCenterX;
    mCenterY = chunk->mCenterY;
    mCenterZ = chunk->mCenterZ;
    mAABB = chunk->mAABB;
    mClipChunk = chunk->mClipChunk;
    dword_50 = chunk->dword_50;
    mBlockEntityMap = chunk->mBlockEntityMap;
    mMutex = chunk->mMutex;
}

// The game stores blocks in two arrays, one for Y0-127 and one for Y128-255
const int DATA_SLICE = 128;
const int CHUNK_SIZE = 16;
const int WORLD_HEIGHT = 256;

const int AIR = 0;
const int STONE = 1;
const int DIRT = 3;
const int BEDROCK = 7;
const int SKIP = 255;

// NON_MATCHING: 93.43%, https://decomp.me/scratch/Kc2zB
void Chunk::rebuild() {
    PIXBeginNamedEvent(0.0f, "Rebuilding chunk %d, %d, %d", mX, mY, mZ);
    PIXBeginNamedEvent(0.0f, "Rebuild section A");

    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();

    updates++;  // Name from b1.2_02

    int x0 = mX;
    int y0 = mY;
    int z0 = mZ;
    int x1 = x0 + CHUNK_SIZE;
    int y1 = y0 + CHUNK_SIZE;
    int z1 = z0 + CHUNK_SIZE;

    LevelChunk::touchedSky = false;  // Name from b1.2_02

    std::vector<std::shared_ptr<BlockEntity>> currentBlockEntities;

    int globalIndex = LevelRenderer::sInstance->getGlobalIndexForChunk(mX, mY, mZ, mLevel);
    if (globalIndex < 0)
        return;

    int unk = LevelRenderer::sInstance->_100;

    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0f, "Rebuild section B");

    // Retrieve the cached block data
    unsigned char* blockMemory = Chunk::getBlockMemory();
    unsigned char* blockDataMemory = Chunk::getBlockDataMemory();
    const BlockState** blockStateMemory = Chunk::getBlockStateMemory();

    // 16x16x256 - full chunk, IDs stored as bytes (0-255)
    arrayWithLength<unsigned char> blocks(blockMemory, 0x10000);

    // The metadata for chunks are nibbles (0-15), so the size here is blocks / 2
    arrayWithLength<unsigned char> blockData(blockDataMemory, 0x8000);

    // Position of the chunk
    BlockPos origin(mX, mY, mZ);

    int start = y0 / 4;
    int end_start = y1 / 4;

    int startIndexY = y0 < 4 ? 0 : start - 1;
    int endIndexY = y1 > WORLD_HEIGHT - 1 ? WORLD_HEIGHT / 4 : end_start + 1;

    // Gets the correct 16x16x16 region of blocks from the chunk
    mLevel->getChunkAt(origin)->getBlockDataRange(blocks, startIndexY, endIndexY);

    int startY_data = y0 <= 0 ? 0 : y0 - 1;
    int endY_Data = y1 + 1 < WORLD_HEIGHT ? y1 + 1 : WORLD_HEIGHT;

    // Gets the correct 16x16x16 region of metadata from the chunk
    mLevel->getChunkAt(origin)->getDataDataRange(blockData, startY_data, endY_Data);

    Region* region = new Region(mLevel, {x0 - 1, y0 - 1, z0 - 1}, {x1 + 1, y1 + 1, z1 + 1}, true);
    region->setCachedBlocksAndData(blockMemory, blockDataMemory, mX >> 4, mY >> 4, mZ >> 4, blockStateMemory);

    PIXBeginNamedEvent(0.0f, "Creating BlockRenderer\n");
    BlockRenderer* blockRenderer = new BlockRenderer(region, mX, mY, mZ, blockMemory);
    PIXEndNamedEvent();

    bool isEmpty = true;

    for (int curY = y0; curY < y1; curY++) {
        for (int curZ = 0; curZ < 16; curZ++) {
            for (int curX = 0; curX < 16; curX++) {
                int y = curY;
                int offset = 0;

                // If y > 128, get the data from the other array
                if (y >= DATA_SLICE) {
                    y -= DATA_SLICE;
                    offset = 0x8000;
                }

                // WHY do I have to add 0 to curX??
                unsigned char id = blockMemory[offset + ((curX + 0) << 11 | curZ << 7 | y)];

                if (id != AIR)
                    isEmpty = false;

                // Skip rendering blocks above the world height
                if (curY == WORLD_HEIGHT - 1)
                    continue;
                // Skip rendering blocks on the side of the chunk
                if (curX == 0 || curX == CHUNK_SIZE - 1)
                    continue;
                if (curZ == 0 || curZ == CHUNK_SIZE - 1)
                    continue;

                // Special case for the edge of the world:
                // Since the edge of the world is a single chunk, it seems like the game can't treat culling
                // the same for them. So, the game checks for any of the block IDs are used in them, and
                // forcibly culls the hidden sides.
                if (id != STONE && id != DIRT && id != BEDROCK && id != SKIP)
                    continue;
                unsigned char idNegX = blockMemory[offset + (((curX - 1) << 11) | curZ << 7 | y)];
                if (idNegX != STONE && idNegX != DIRT && idNegX != BEDROCK && idNegX != SKIP)
                    continue;
                unsigned char idPosX = blockMemory[offset + (((curX + 1) << 11) | curZ << 7 | y)];
                if (idPosX != STONE && idPosX != DIRT && idPosX != BEDROCK && idPosX != SKIP)
                    continue;
                unsigned char idNegZ = blockMemory[offset + ((curX << 11) | ((curZ - 1) << 7) | y)];
                if (idNegZ != STONE && idNegZ != DIRT && idNegZ != BEDROCK && idNegZ != SKIP)
                    continue;
                unsigned char idPosZ = blockMemory[offset + ((curX << 11) | ((curZ + 1) << 7) | y)];
                if (idPosZ != STONE && idPosZ != DIRT && idPosZ != BEDROCK && idPosZ != SKIP)
                    continue;

                if (curY > 0) {
                    int below = curY - 1;
                    int belowOffset = 0;
                    if (below >= DATA_SLICE) {
                        below -= DATA_SLICE;
                        belowOffset = 0x8000;
                    }

                    unsigned char idNegY = blockMemory[belowOffset + (curX << 11 | curZ << 7 | below)];
                    if (idNegY != STONE && idNegY != DIRT && idNegY != BEDROCK && idNegY != SKIP)
                        continue;
                }

                int above = curY + 1;
                int aboveOffset = 0;
                if (above >= DATA_SLICE) {
                    above -= DATA_SLICE;
                    aboveOffset = 0x8000;
                }

                unsigned char idPosY = blockMemory[aboveOffset + (curX << 11 | curZ << 7 | above)];
                if (idPosY != STONE && idPosY != DIRT && idPosY != BEDROCK && idPosY != SKIP)
                    continue;

                // (?) fact check me on this:
                // If the block is stone, dirt, bedrock, or skipped on every side, we should skip this block
                blockMemory[offset + (curX << 11 | curZ << 7 | y)] = SKIP;
            }
        }
    }

    std::vector<BlockPos> glideRingPositions;
    std::vector<GlideRingGenerator::eGlideRingSize> glideRingSizes;

    // The Glide minigame has boost areas where the game creates fake blocks to cover them.
    if (Minecraft::InMiniGame(EMiniGameId::GLIDE, 0)) {
        LevelRuleset* gameRules = CConsoleMinecraftApp::sInstance.getGameRuleDefinitions();
        std::vector<TargetAreaRuleDefinition*> ringsInArea;

        AABB* chunkBounds = AABB::newTemp(x0, y0, z0, x1, y1, z1);

        if (gameRules)
            gameRules->getRingsWithinArea(&ringsInArea, chunkBounds);

        for (auto it = ringsInArea.begin(); it != ringsInArea.end(); ++it) {
            TargetAreaRuleDefinition* def = *it;
            std::vector<BlockPos> ringBlockPositions;

            const AABB* test = def->getArea();
            GlideRingGenerator::eGlideRingSize test2 = def->getSize();

            GlideRingGenerator::BuildRing(ringBlockPositions, test, test2);

            for (auto it2 = ringBlockPositions.begin(); it2 != ringBlockPositions.end(); ++it2) {
                const BlockPos& blockPos = *it2;
                Vec3* vec3 = Vec3::newTemp(blockPos.getX(), blockPos.getY(), blockPos.getZ());

                if (chunkBounds->containsIncludingLowerBound(vec3)) {
                    glideRingPositions.push_back(blockPos);
                    glideRingSizes.push_back((*it)->getSize());
                }
            }
        }

        // Skip rendering the inside of the boost areas
        for (auto it = glideRingPositions.begin(); it != glideRingPositions.end(); ++it) {
            const BlockPos& blockPos = *it;
            int ringY = blockPos.getY();

            if (ringY >= 0 && ringY < WORLD_HEIGHT) {
                int yOffset = 0;
                if (ringY >= DATA_SLICE) {
                    ringY -= DATA_SLICE;
                    yOffset = 0x8000;
                }
                int ringX = blockPos.getX() - x0;
                int ringZ = blockPos.getZ() - z0;

                blockMemory[yOffset + ((ringX << 11) | ((ringZ) << 7) | ringY)] = 255;
            }
        }
    }

    int baseRenderLayerIdx = globalIndex + unk;

    PIXEndNamedEvent();

    // If the chunk is empty, we can clear its buffer and remove the block entities.
    if (isEmpty && glideRingPositions.empty()) {
        Renderer* renderer = Renderer::sInstance;

        for (int i = 0; i < 3; i++) {
            LevelRenderer::sInstance->setGlobalChunkFlag(mX, mY, mZ, mLevel, 4, i);
            renderer->CBuffClear(baseRenderLayerIdx + i);
        }

        int globalChunkIndex = LevelRenderer::sInstance->getGlobalIndexForChunk(mX, mY, mZ, mLevel);

        EnterCriticalSection(mMutex);
        auto it = mBlockEntityMap->find(globalChunkIndex);

        if (it != mBlockEntityMap->end()) {
            for (auto entityIterator = it->second.begin(); entityIterator != it->second.end();
                 entityIterator++) {
                (*entityIterator)->setRenderRemoveStage(1);
            }
        }

        LeaveCriticalSection(mMutex);

        delete region;
        delete blockRenderer;

        PIXEndNamedEvent();

        return;
    }

    PIXBeginNamedEvent(0.0f, "Rebuild section C");

    // TODO: Find out how to create these magic numbers
    BufferBuilder::Bounds bounds;
    bounds.bounds[0] = -6.0f;
    bounds.bounds[1] = -6.0f;
    bounds.bounds[2] = -6.0f;
    bounds.bounds[3] = 22.0f;
    bounds.bounds[4] = 22.0f;
    bounds.bounds[5] = 22.0f;

    MutableBlockPos currentPos(0, 0, 0);

    Renderer* renderer = Renderer::sInstance;

    // Loop through the chunk's render layers. Some blocks have higher priority than others
    // If we're at the block's layer, tesselate it.
    for (int layer = 0; layer < 3; layer++) {
        bool renderNextLayer = false;
        bool rendered = false;
        bool started = false;

        // Tesselate glide boost areas
        if (layer == 1) {
            started = true;
            GlStateManager::newList(baseRenderLayerIdx + layer, 0);
            GlStateManager::pushMatrix();
            GlStateManager::depthMask(true);
            builder->useCompactVertices(true);
            translateToPos();
            builder->begin();
            builder->offset(-mX, -mY, -mZ);

            for (size_t i = 0; i < glideRingPositions.size(); i++) {
                PIXBeginNamedEvent(0.0f, "Tesselate in world");
                blockRenderer->setLightOverride(0x7FFFFFFF);
                blockRenderer->tesselateInWorldFixedTexture(
                    Blocks::STAINED_GLASS->defaultBlockState(), glideRingPositions.at(i),
                    GlideRingGenerator::getIcon(glideRingSizes.at(i)));
                blockRenderer->clearLightOverride();

                rendered = true;

                PIXEndNamedEvent();
            }
        }

        // Tesselate blocks/block entities
        for (int curZ = z0; curZ < z1; curZ++) {
            for (int curX = x0; curX < x1; curX++) {
                for (int curY = y0; curY < y1; curY++) {
                    int yOffset = 0;
                    int yIndex = curY;
                    if (yIndex >= DATA_SLICE) {
                        yIndex -= DATA_SLICE;
                        yOffset = 0x8000;
                    }

                    // Get the ID of the current block
                    unsigned char id
                        = blockMemory[yOffset + (((curX - x0) << 11) | ((curZ - z0) << 7) | yIndex)];

                    if (id == AIR || id == SKIP)
                        continue;

                    if (!started) {
                        started = true;
                        GlStateManager::newList(baseRenderLayerIdx + layer, 0);
                        GlStateManager::pushMatrix();
                        GlStateManager::depthMask(true);
                        builder->useCompactVertices(true);
                        translateToPos();
                        builder->begin();
                        builder->offset(-mX, -mY, -mZ);
                    }

                    currentPos.set(curX, curY, curZ);

                    Block* block = Block::byId(id);

                    // Setup block entities for rendering
                    if (layer == 0 && block->isBlockEntity()) {
                        std::shared_ptr<BlockEntity> blockEntity = region->getBlockEntity(currentPos);
                        if (BlockEntityRenderDispatcher::sInstance->hasRenderer(blockEntity)) {
                            currentBlockEntities.push_back(blockEntity);
                        }
                    }

                    int blockRenderLayer = block->getRenderLayer();

                    // Tesselate blocks
                    if (blockRenderLayer > layer) {
                        renderNextLayer = true;
                    } else if (blockRenderLayer == layer) {
                        PIXBeginNamedEvent(0.0f, "Tesselate in world");
                        rendered |= blockRenderer->tesselateInWorld(region->getBlockState(currentPos),
                                                                    currentPos, nullptr, nullptr);
                        PIXEndNamedEvent();
                    }
                }
            }
        }

        if (started) {
            builder->end();
            bounds.addBounds(builder->mBounds);
            GlStateManager::popMatrix();
            GlStateManager::endList(0);
            builder->useCompactVertices(false);
            builder->offset(0.0f, 0.0f, 0.0f);
        } else {
            rendered = false;
        }

        // If the chunk is done rendering, we can clear its global chunk flag, otherwise set it and clear the
        // layer.
        if (rendered) {
            LevelRenderer::sInstance->clearGlobalChunkFlag(mX, mY, mZ, mLevel, 4, layer);
        } else {
            LevelRenderer::sInstance->setGlobalChunkFlag(mX, mY, mZ, mLevel, 4, layer);
            renderer->CBuffClear(baseRenderLayerIdx + layer);
        }

        if (layer == 0 && !renderNextLayer) {
            LevelRenderer::sInstance->setGlobalChunkFlag(mX, mY, mZ, mLevel, 24, 0);
            renderer->CBuffClear(baseRenderLayerIdx + 1);
            renderer->CBuffClear(baseRenderLayerIdx + 2);
            break;
        }

        if (layer == 1 && !renderNextLayer) {
            LevelRenderer::sInstance->setGlobalChunkFlag(mX, mY, mZ, mLevel, 16, 0);
            renderer->CBuffClear(baseRenderLayerIdx + 2);
            break;
        }
    }

    if (mAABB) {
        mAABB->set(bounds.bounds[0], bounds.bounds[1], bounds.bounds[2], bounds.bounds[3], bounds.bounds[4],
                   bounds.bounds[5]);
    }

    delete blockRenderer;
    delete region;

    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0f, "Rebuild section D");

    int index = LevelRenderer::sInstance->getGlobalIndexForChunk(mX, mY, mZ, mLevel);

    EnterCriticalSection(mMutex);

    // Render block entities
    if (currentBlockEntities.size()) {
        auto it = mBlockEntityMap->find(index);
        if (it == mBlockEntityMap->end()) {
            for (size_t i = 0; i < currentBlockEntities.size(); i++) {
                currentBlockEntities[i]->shouldRemoveForRender();  // Unused check
                (*mBlockEntityMap)[index].push_back(currentBlockEntities[i]);
            }
        } else {
            auto& blockEntities = it->second;

            for (auto entity = blockEntities.begin(); entity != blockEntities.end(); entity++) {
                (*entity)->setRenderRemoveStage(1);
            }

            for (size_t i = 0; i < currentBlockEntities.size(); i++) {
                auto entity = std::find(blockEntities.begin(), blockEntities.end(), currentBlockEntities[i]);
                if (entity == blockEntities.end()) {
                    (*mBlockEntityMap)[index].push_back(currentBlockEntities[i]);
                } else {
                    (*entity)->setRenderRemoveStage(0);
                }
            }
        }
    } else {
        auto it = mBlockEntityMap->find(index);

        if (it != mBlockEntityMap->end()) {
            for (auto entityIterator = it->second.begin(); entityIterator != it->second.end();
                 entityIterator++) {
                (*entityIterator)->setRenderRemoveStage(1);
            }
        }
    }

    LeaveCriticalSection(mMutex);
    PIXEndNamedEvent();

    // Mark the chunk ready to rebuild again
    LevelRenderer::sInstance->setGlobalChunkFlag(mX, mY, mZ, mLevel, 1, 0);

    PIXEndNamedEvent();
}

void Chunk::_delete() {
    reset();
    mLevel = nullptr;
}

void Chunk::clearDirty() {
    LevelRenderer::sInstance->clearGlobalChunkFlag(mX, mY, mZ, mLevel, 2, 0);
}
