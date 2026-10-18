#include "net/minecraft/world/level/levelgen/feature/StructureFeature.h"

#include "com/mojang/nbt/ByteArrayTag.h"
#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/LevelType.h"
#include "net/minecraft/world/level/chunk/ChunkPos.h"
#include "net/minecraft/world/level/levelgen/structure/BoundingBox.h"
#include "net/minecraft/world/level/levelgen/structure/StructureFeatureIO.h"
#include "net/minecraft/world/level/levelgen/structure/StructurePiece.h"
#include "net/minecraft/world/level/levelgen/structure/StructureStart.h"
#include "net/minecraft/world/level/saveddata/StructureFeatureSavedData.h"
#include "net/minecraft/world/level/storage/LevelData.h"

StructureFeature::StructureFeature() {
    m_savedData = nullptr;
}

StructureFeature::~StructureFeature() {
    for (auto it = m_starts.begin(); it != m_starts.end(); ++it)
        delete it->second;
}

void StructureFeature::addFeature(Level* level, int sourceX, int sourceZ, int, int, ChunkPrimer*) {
    restoreSavedData(level);
    if (m_starts.find(ChunkPos::asLong(sourceX, sourceZ)) == m_starts.end()) {
        m_random.nextInt();
        if (isFeatureChunk(sourceX, sourceZ, level->getLevelData()->getGeneratorType() == LevelType::FLAT)) {
            StructureStart* start = createStructureStart(sourceX, sourceZ);
            m_starts[ChunkPos::asLong(sourceX, sourceZ)] = start;
            if (start->isValid())
                saveFeature(sourceX, sourceZ, start);
        }
    }
}

bool StructureFeature::postProcess(Level* level, Random& random, ChunkPos* chunk) {
    restoreSavedData(level);
    int x = chunk->m_x << 4;
    int z = chunk->m_z << 4;
    bool generated = false;
    for (auto it = m_starts.begin(); it != m_starts.end(); ++it) {
        StructureStart* start = it->second;
        if (start->isValid() && start->isValidForPostProcess(chunk)
            && start->getBoundingBox()->intersects(x, z, x + 15, z + 15)) {
            BoundingBox bounds(x, z, x + 15, z + 15);
            start->postProcess(level, random, &bounds);
            start->notifyPostProcessAt(chunk);
            if (start->isDirty())
                saveFeature(start->getChunkX(), start->getChunkZ(), start);
            generated = true;
        }
    }
    return generated;
}

bool StructureFeature::isIntersection(int x, int z) {
    restoreSavedData(m_level);
    for (auto it = m_starts.begin(); it != m_starts.end(); ++it) {
        StructureStart* start = it->second;
        if (start->isValid() && start->getBoundingBox()->intersects(x, z, x, z)) {
            auto* pieces = start->getPieces();
            for (auto piece = pieces->begin(); piece != pieces->end(); ++piece)
                if ((*piece)->getBoundingBox()->intersects(x, z, x, z))
                    return true;
        }
    }
    return false;
}

bool StructureFeature::isInsideFeature(const BlockPos& pos) {
    if (!m_level)
        return false;
    restoreSavedData(m_level);
    return getStructureAt(pos) != nullptr;
}

StructureStart* StructureFeature::getStructureAt(const BlockPos& pos) {
    for (auto it = m_starts.begin(); it != m_starts.end(); ++it) {
        StructureStart* start = it->second;
        if (start->isValid() && start->getBoundingBox()->isInside(pos)) {
            auto* pieces = start->getPieces();
            auto piece = pieces->begin();
            while (piece != pieces->end()) {
                if ((*piece)->getBoundingBox()->isInside(pos))
                    return start;
                ++piece;
            }
        }
    }
    return nullptr;
}

bool StructureFeature::isInsideBoundingFeature(Level* level, const BlockPos& pos) {
    restoreSavedData(level);
    for (auto it = m_starts.begin(); it != m_starts.end(); ++it) {
        StructureStart* start = it->second;
        if (start->isValid() && start->getBoundingBox()->isInside(pos))
            return true;
    }
    return false;
}

std::vector<BlockPos>* StructureFeature::getGuesstimatedFeaturePositions() {
    return nullptr;
}

void StructureFeature::restoreSavedData(Level* level) {
    if (level && !m_savedData) {
        m_savedData = std::dynamic_pointer_cast<StructureFeatureSavedData>(
            level->getSavedData(typeid(StructureFeatureSavedData), getFeatureName()));
        if (!m_savedData) {
            m_savedData
                = std::shared_ptr<StructureFeatureSavedData>(new StructureFeatureSavedData(getFeatureName()));
            level->setSavedData(getFeatureName(), m_savedData);
        } else {
            auto* tags = m_savedData->getFullTag()->getAllTags();
            for (auto it = tags->begin(); it != tags->end(); ++it) {
                Tag* tag = it->second;
                if (tag->getId() == Tag::TAG_Byte_Array) {
                    StructureStart* start
                        = StructureFeatureIO::loadStaticStart(static_cast<ByteArrayTag*>(tag), level);
                    if (start)
                        m_starts[ChunkPos::asLong(start->getChunkX(), start->getChunkZ())] = start;
                }
            }
        }
    }
}

void StructureFeature::saveFeature(int chunkX, int chunkZ, StructureStart* start) {
    m_savedData->putFeatureTag(start->createTag(chunkX, chunkZ), chunkX, chunkZ);
    m_savedData->setDirty();
    start->clearDirty();
}

BlockPos* StructureFeature::findNearestFeaturePositionBySpacing(Level* level, StructureFeature* feature,
                                                                const BlockPos& origin, int, int, int, bool,
                                                                int maxRadius, bool skipKnown) {
    int centerX = origin.getX() >> 4;
    int centerZ = origin.getZ() >> 4;
    int halfSize = level->getLevelData()->getXZSize() / 2;
    // The Switch's finite-world search visits successive chunk-square perimeters.
    for (int radius = 0; radius <= maxRadius; ++radius) {
        for (int dx = -radius; dx <= radius; ++dx) {
            bool edgeX = dx == -radius || dx == radius;
            for (int dz = -radius; dz <= radius; ++dz) {
                if (edgeX || dz == -radius || dz == radius) {
                    int x = centerX + dx;
                    int z = centerZ + dz;
                    if (feature->isFeatureChunk(x, z,
                                                level->getLevelData()->getGeneratorType() == LevelType::FLAT)
                        && x >= -halfSize && x <= halfSize && z >= -halfSize && z <= halfSize
                        && (!skipKnown || !level->isChunkGeneratedAt(x, z)))
                        return new BlockPos((x << 4) + 8, 64, (z << 4) + 8);
                }
            }
        }
    }
    return nullptr;
}
