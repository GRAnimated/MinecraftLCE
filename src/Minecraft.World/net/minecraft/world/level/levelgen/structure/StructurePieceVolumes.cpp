#include "net/minecraft/world/level/levelgen/structure/StructurePiece.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/levelgen/structure/BoundingBox.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cmath>
#include <cstdlib>

const BlockState* StructurePiece::BlockSelector::getNext() {
    return m_next;
}

void StructurePiece::generateAirBox(Level* level, BoundingBox* bounds, int x0, int y0, int z0, int x1, int y1,
                                    int z1) {
    for (int y = y0; y <= y1; ++y)
        for (int x = x0; x <= x1; ++x)
            for (int z = z0; z <= z1; ++z)
                placeBlock(level, Blocks::AIR->defaultBlockState(), x, y, z, bounds);
}

void StructurePiece::generateBox(Level* level, BoundingBox* bounds, int x0, int y0, int z0, int x1, int y1,
                                 int z1, const BlockState* boundary, const BlockState* inside, bool skipAir) {
    for (int y = y0; y <= y1; ++y)
        for (int x = x0; x <= x1; ++x)
            for (int z = z0; z <= z1; ++z) {
                if (skipAir && getBlock(level, x, y, z, bounds)->getBlock()->getMaterial() == Material::AIR)
                    continue;
                if (y == y0 || y == y1 || x == x0 || x == x1 || z == z0 || z == z1)
                    placeBlock(level, boundary, x, y, z, bounds);
                else
                    placeBlock(level, inside, x, y, z, bounds);
            }
}

void StructurePiece::generateBox(Level* level, BoundingBox* bounds, BoundingBox* box,
                                 const BlockState* boundary, const BlockState* inside, bool skipAir) {
    generateBox(level, bounds, box->m_x0, box->m_y0, box->m_z0, box->m_x1, box->m_y1, box->m_z1, boundary,
                inside, skipAir);
}

void StructurePiece::generateBox(Level* level, BoundingBox* bounds, int x0, int y0, int z0, int x1, int y1,
                                 int z1, bool skipAir, Random& random, BlockSelector* selector) {
    for (int y = y0; y <= y1; ++y)
        for (int x = x0; x <= x1; ++x)
            for (int z = z0; z <= z1; ++z) {
                if (skipAir && getBlock(level, x, y, z, bounds)->getBlock()->getMaterial() == Material::AIR)
                    continue;
                selector->next(random, x, y, z,
                               y == y0 || y == y1 || x == x0 || x == x1 || z == z0 || z == z1);
                placeBlock(level, selector->getNext(), x, y, z, bounds);
            }
}

void StructurePiece::generateBox(Level* level, BoundingBox* bounds, BoundingBox* box, bool skipAir,
                                 Random& random, BlockSelector* selector) {
    generateBox(level, bounds, box->m_x0, box->m_y0, box->m_z0, box->m_x1, box->m_y1, box->m_z1, skipAir,
                random, selector);
}

void StructurePiece::generateMaybeBox(Level* level, BoundingBox* bounds, Random& random, float chance, int x0,
                                      int y0, int z0, int x1, int y1, int z1, const BlockState* boundary,
                                      const BlockState* inside, bool skipAir, int maxSkyBrightness) {
    for (int y = y0; y <= y1; ++y)
        for (int x = x0; x <= x1; ++x)
            for (int z = z0; z <= z1; ++z) {
                if (random.nextFloat() > chance)
                    continue;
                if (skipAir && getBlock(level, x, y, z, bounds)->getBlock()->getMaterial() == Material::AIR)
                    continue;
                if (maxSkyBrightness > 0 && getSkyBrightness(level, x, y, z, bounds) >= maxSkyBrightness)
                    continue;
                if (y == y0 || y == y1 || x == x0 || x == x1 || z == z0 || z == z1)
                    placeBlock(level, boundary, x, y, z, bounds);
                else
                    placeBlock(level, inside, x, y, z, bounds);
            }
}

void StructurePiece::maybeGenerateBlock(Level* level, BoundingBox* bounds, Random& random, float chance,
                                        int x, int y, int z, const BlockState* state) {
    if (random.nextFloat() < chance)
        placeBlock(level, state, x, y, z, bounds);
}

void StructurePiece::generateUpperHalfSphere(Level* level, BoundingBox* bounds, int x0, int y0, int z0,
                                             int x1, int y1, int z1, const BlockState* state, bool skipAir) {
    float width = x1 - x0 + 1;
    float height = y1 - y0 + 1;
    float depth = z1 - z0 + 1;
    float centerX = x0 + width / 2.0f;
    float centerZ = z0 + depth / 2.0f;
    for (int y = y0; y <= y1; ++y) {
        float dy = (y - y0) / height;
        for (int x = x0; x <= x1; ++x) {
            float dx = (x - centerX) / (width / 2.0f);
            for (int z = z0; z <= z1; ++z) {
                if (skipAir && getBlock(level, x, y, z, bounds)->getBlock()->getMaterial() == Material::AIR)
                    continue;
                float dz = (z - centerZ) / (depth / 2.0f);
                if (dx * dx + dy * dy + dz * dz <= 1.05f)
                    placeBlock(level, state, x, y, z, bounds);
            }
        }
    }
}

void StructurePiece::generateFullSphere(Level* level, BoundingBox* bounds, int centerX, int centerY,
                                        int centerZ, int radius, const BlockState* boundary,
                                        const BlockState* inside, bool skipNull) {
    for (int y = centerY - radius; y <= centerY + radius; ++y)
        for (int x = centerX - radius; x <= centerX + radius; ++x)
            for (int z = centerZ - radius; z <= centerZ + radius; ++z) {
                // This Switch helper tests for a null state, unlike the air-material filters above.
                if (skipNull && getBlock(level, x, y, z, bounds) == nullptr)
                    continue;
                float dx = std::abs(x - centerX) + 0.5f;
                float dy = std::abs(y - centerY) + 0.5f;
                float dz = std::abs(z - centerZ) + 0.5f;
                float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
                if (std::fabs(distance - radius) <= 0.5f)
                    placeBlock(level, boundary, x, y, z, bounds);
                if (radius - distance > 0.5f)
                    placeBlock(level, inside, x, y, z, bounds);
            }
}

void StructurePiece::generateAirColumnUp(Level* level, int x, int y, int z, BoundingBox* bounds) {
    BlockPos pos(getWorldX(x, z), getWorldY(y), getWorldZ(x, z));
    if (bounds->isInside(pos)) {
        while (!level->isEmptyBlock(pos) && pos.getY() < 255) {
            level->setBlock(pos, Blocks::AIR->defaultBlockState(), 2, false);
            pos = pos.above();
        }
    }
}

void StructurePiece::generateAirBoxUp(Level* level, int x0, int z0, int x1, int z1, int y,
                                      BoundingBox* bounds) {
    for (int x = x0; x < x1; ++x)
        for (int z = z0; z < z1; ++z)
            generateAirColumnUp(level, x, y, z, bounds);
}

void StructurePiece::fillColumnDown(Level* level, const BlockState* state, int x, int y, int z,
                                    BoundingBox* bounds) {
    int worldX = getWorldX(x, z);
    int worldY = getWorldY(y);
    int worldZ = getWorldZ(x, z);
    if (bounds->isInside(BlockPos(worldX, worldY, worldZ))) {
        while (
            (level->isEmptyBlock(BlockPos(worldX, worldY, worldZ))
             || level->getBlockState(BlockPos(worldX, worldY, worldZ))->getBlock()->getMaterial()->isLiquid())
            && worldY > 1) {
            level->setBlock(BlockPos(worldX, worldY, worldZ), state, 2, false);
            --worldY;
        }
    }
}

void StructurePiece::fillBoxDown(Level* level, const BlockState* state, int x0, int z0, int x1, int z1, int y,
                                 BoundingBox* bounds) {
    for (int x = x0; x < x1; ++x)
        for (int z = z0; z < z1; ++z)
            fillColumnDown(level, state, x, y, z, bounds);
}
