#include "net/minecraft/world/level/chunk/Chunk.h"

#include "NX/Platform.h"
#include "NX/Render/RendererCore.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/renderer/BlockRenderer.h"
#include "net/minecraft/client/renderer/LevelRenderer.h"
#include "net/minecraft/client/renderer/blockentity/BlockEntityRenderDispatcher.h"
#include "net/minecraft/client/renderer/platform/GlStateManager.h"
#include "net/minecraft/client/renderer/vertex/BufferBuilder.h"
#include "net/minecraft/client/renderer/vertex/Tesselator.h"
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
    m_blockEntityMap = &map;
    m_mutex = &mutex;
    clipChunk->m_needsUpdate = false;
    m_level = level;
    m_aabb = nullptr;
    m_dword50 = 0;
    m_isPositionSet = false;
    m_clipChunk = clipChunk;
    clipChunk->m_chunk = this;

    setPos(x, y, z);
    m_isInitalized = true;
}

Chunk::Chunk() {
    m_isInitalized = false;
}

void Chunk::setPos(int x, int y, int z) {
    if (!m_isPositionSet || m_x != x || m_y != y || m_z != z) {
        reset();

        m_x = x;
        m_y = y;
        m_z = z;
        m_centerX = x + 8;
        m_centerY = y + 8;
        m_centerZ = z + 8;
        m_clipChunk->m_centerX = m_centerX;
        m_clipChunk->m_centerY = m_centerY;
        m_clipChunk->m_centerZ = m_centerZ;
        m_clipChunk->m_globalIndex = LevelRenderer::getGlobalIndexForChunk(x, y, z, m_level);
        AABB* aabb = m_aabb;
        m_1c = 0;
        m_renderX = x;
        m_renderY = y;
        m_renderZ = z;
        m_14 = 0;
        m_18 = 0;
        if (!aabb) {
            m_aabb = AABB::newPermanent(-6.0, -6.0, -6.0, 22.0, 22.0, 22.0);
        }
        m_clipChunk->m_worldAabbMinX = m_aabb->m_inX + x;
        m_clipChunk->m_worldAabbMinY = m_aabb->m_inY + y;
        m_clipChunk->m_worldAabbMinZ = m_aabb->m_inZ + z;
        m_clipChunk->m_worldAabbMaxX = m_aabb->m_axX + x;
        m_clipChunk->m_worldAabbMaxY = m_aabb->m_axY + y;
        m_clipChunk->m_worldAabbMaxZ = m_aabb->m_axZ + z;

        m_isPositionSet = true;

        EnterCriticalSection(&LevelRenderer::sInstance->m_mutex);

        if (LevelRenderer::sInstance->incGlobalChunkRefCount(x, y, z, m_level) == 1) {
            LevelRenderer::sInstance->setGlobalChunkFlag(x, y, z, m_level, 2, 0);
            PIXSetMarkerDeprecated(0.0f, "Non-stack event pushed");
        }

        LeaveCriticalSection(&LevelRenderer::sInstance->m_mutex);
    }
}

void Chunk::reset() {
    if (m_isPositionSet) {
        EnterCriticalSection(&LevelRenderer::sInstance->m_mutex);
        unsigned char dec = LevelRenderer::sInstance->decGlobalChunkRefCount(m_x, m_y, m_z, m_level);
        m_isPositionSet = false;
        if (!dec) {
            int index = LevelRenderer::sInstance->getGlobalIndexForChunk(m_x, m_y, m_z, m_level);
            if (index >= 0) {
                int offset = 3 * index + LevelRenderer::sInstance->m_100;
                Renderer* renderer = Renderer::sInstance;
                renderer->CBuffClear(offset);
                renderer->CBuffClear(offset + 1);
                renderer->CBuffClear(offset + 2);
                LevelRenderer::sInstance->setGlobalChunkFlags(m_x, m_y, m_z, m_level, 0);
            }
        }
        LeaveCriticalSection(&LevelRenderer::sInstance->m_mutex);
    }
    m_clipChunk->m_needsUpdate = 0;
}

void Chunk::translateToPos() {
    GlStateManager::translatef(m_renderX, m_renderY, m_renderZ);
}

void Chunk::makeCopyForRebuild(Chunk* chunk) {
    m_level = chunk->m_level;
    m_x = chunk->m_x;
    m_y = chunk->m_y;
    m_z = chunk->m_z;
    m_14 = chunk->m_14;
    m_18 = chunk->m_18;
    m_1c = chunk->m_1c;
    m_renderX = chunk->m_renderX;
    m_renderY = chunk->m_renderY;
    m_renderZ = chunk->m_renderZ;
    m_centerX = chunk->m_centerX;
    m_centerY = chunk->m_centerY;
    m_centerZ = chunk->m_centerZ;
    m_aabb = chunk->m_aabb;
    m_clipChunk = chunk->m_clipChunk;
    m_dword50 = chunk->m_dword50;
    m_blockEntityMap = chunk->m_blockEntityMap;
    m_mutex = chunk->m_mutex;
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
    PIXBeginNamedEvent(0.0f, "Rebuilding chunk %d, %d, %d", m_x, m_y, m_z);
    PIXBeginNamedEvent(0.0f, "Rebuild section A");

    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();

    updates++;  // Name from b1.2_02

    int x0 = m_x;
    int y0 = m_y;
    int z0 = m_z;
    int x1 = x0 + CHUNK_SIZE;
    int y1 = y0 + CHUNK_SIZE;
    int z1 = z0 + CHUNK_SIZE;

    LevelChunk::touchedSky = false;  // Name from b1.2_02

    std::vector<std::shared_ptr<BlockEntity>> currentBlockEntities;

    int globalIndex = LevelRenderer::sInstance->getGlobalIndexForChunk(m_x, m_y, m_z, m_level);
    if (globalIndex < 0)
        return;

    int unk = LevelRenderer::sInstance->m_100;

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
    BlockPos origin(m_x, m_y, m_z);

    int start = y0 / 4;
    int end_start = y1 / 4;

    int startIndexY = y0 < 4 ? 0 : start - 1;
    int endIndexY = y1 > WORLD_HEIGHT - 1 ? WORLD_HEIGHT / 4 : end_start + 1;

    // Gets the correct 16x16x16 region of blocks from the chunk
    m_level->getChunkAt(origin)->getBlockDataRange(blocks, startIndexY, endIndexY);

    int startY_data = y0 <= 0 ? 0 : y0 - 1;
    int endY_Data = y1 + 1 < WORLD_HEIGHT ? y1 + 1 : WORLD_HEIGHT;

    // Gets the correct 16x16x16 region of metadata from the chunk
    m_level->getChunkAt(origin)->getDataDataRange(blockData, startY_data, endY_Data);

    Region* region = new Region(m_level, {x0 - 1, y0 - 1, z0 - 1}, {x1 + 1, y1 + 1, z1 + 1}, true);
    region->setCachedBlocksAndData(blockMemory, blockDataMemory, m_x >> 4, m_y >> 4, m_z >> 4,
                                   blockStateMemory);

    PIXBeginNamedEvent(0.0f, "Creating BlockRenderer\n");
    BlockRenderer* blockRenderer = new BlockRenderer(region, m_x, m_y, m_z, blockMemory);
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
            LevelRenderer::sInstance->setGlobalChunkFlag(m_x, m_y, m_z, m_level, 4, i);
            renderer->CBuffClear(baseRenderLayerIdx + i);
        }

        int globalChunkIndex = LevelRenderer::sInstance->getGlobalIndexForChunk(m_x, m_y, m_z, m_level);

        EnterCriticalSection(m_mutex);
        auto it = m_blockEntityMap->find(globalChunkIndex);

        if (it != m_blockEntityMap->end()) {
            for (auto entityIterator = it->second.begin(); entityIterator != it->second.end();
                 entityIterator++) {
                (*entityIterator)->setRenderRemoveStage(1);
            }
        }

        LeaveCriticalSection(m_mutex);

        delete region;
        delete blockRenderer;

        PIXEndNamedEvent();

        return;
    }

    PIXBeginNamedEvent(0.0f, "Rebuild section C");

    // TODO: Find out how to create these magic numbers
    BufferBuilder::Bounds bounds;
    bounds.m_bounds[0] = -6.0f;
    bounds.m_bounds[1] = -6.0f;
    bounds.m_bounds[2] = -6.0f;
    bounds.m_bounds[3] = 22.0f;
    bounds.m_bounds[4] = 22.0f;
    bounds.m_bounds[5] = 22.0f;

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
            builder->offset(-m_x, -m_y, -m_z);

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
                        builder->offset(-m_x, -m_y, -m_z);
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
            bounds.addBounds(builder->m_bounds);
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
            LevelRenderer::sInstance->clearGlobalChunkFlag(m_x, m_y, m_z, m_level, 4, layer);
        } else {
            LevelRenderer::sInstance->setGlobalChunkFlag(m_x, m_y, m_z, m_level, 4, layer);
            renderer->CBuffClear(baseRenderLayerIdx + layer);
        }

        if (layer == 0 && !renderNextLayer) {
            LevelRenderer::sInstance->setGlobalChunkFlag(m_x, m_y, m_z, m_level, 24, 0);
            renderer->CBuffClear(baseRenderLayerIdx + 1);
            renderer->CBuffClear(baseRenderLayerIdx + 2);
            break;
        }

        if (layer == 1 && !renderNextLayer) {
            LevelRenderer::sInstance->setGlobalChunkFlag(m_x, m_y, m_z, m_level, 16, 0);
            renderer->CBuffClear(baseRenderLayerIdx + 2);
            break;
        }
    }

    if (m_aabb) {
        m_aabb->set(bounds.m_bounds[0], bounds.m_bounds[1], bounds.m_bounds[2], bounds.m_bounds[3],
                    bounds.m_bounds[4], bounds.m_bounds[5]);
    }

    delete blockRenderer;
    delete region;

    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0f, "Rebuild section D");

    int index = LevelRenderer::sInstance->getGlobalIndexForChunk(m_x, m_y, m_z, m_level);

    EnterCriticalSection(m_mutex);

    // Render block entities
    if (currentBlockEntities.size()) {
        auto it = m_blockEntityMap->find(index);
        if (it == m_blockEntityMap->end()) {
            for (size_t i = 0; i < currentBlockEntities.size(); i++) {
                currentBlockEntities[i]->shouldRemoveForRender();  // Unused check
                (*m_blockEntityMap)[index].push_back(currentBlockEntities[i]);
            }
        } else {
            auto& blockEntities = it->second;

            for (auto entity = blockEntities.begin(); entity != blockEntities.end(); entity++) {
                (*entity)->setRenderRemoveStage(1);
            }

            for (size_t i = 0; i < currentBlockEntities.size(); i++) {
                auto entity = std::find(blockEntities.begin(), blockEntities.end(), currentBlockEntities[i]);
                if (entity == blockEntities.end()) {
                    (*m_blockEntityMap)[index].push_back(currentBlockEntities[i]);
                } else {
                    (*entity)->setRenderRemoveStage(0);
                }
            }
        }
    } else {
        auto it = m_blockEntityMap->find(index);

        if (it != m_blockEntityMap->end()) {
            for (auto entityIterator = it->second.begin(); entityIterator != it->second.end();
                 entityIterator++) {
                (*entityIterator)->setRenderRemoveStage(1);
            }
        }
    }

    LeaveCriticalSection(m_mutex);
    PIXEndNamedEvent();

    // Mark the chunk ready to rebuild again
    LevelRenderer::sInstance->setGlobalChunkFlag(m_x, m_y, m_z, m_level, 1, 0);

    PIXEndNamedEvent();
}

void Chunk::_delete() {
    reset();
    m_level = nullptr;
}

void Chunk::clearDirty() {
    LevelRenderer::sInstance->clearGlobalChunkFlag(m_x, m_y, m_z, m_level, 2, 0);
}
