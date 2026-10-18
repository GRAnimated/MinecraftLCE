#include "net/minecraft/world/level/levelgen/feature/OreFeature.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/StoneBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include <algorithm>
#include <cstring>

// NON_MATCHING: local predicate construction differs from the original static object.
OreFeature::OreFeature(const BlockState* state, int size) : Feature(false), m_ore(0, 0) {
    static const NaturalStonePredicate predicate;
    init(state, size, &predicate);
}

OreFeature::OreFeature(const BlockState* state, int size,
                       const Predicate<const Biome::LegacyBlockData&>* predicate)
    : Feature(false), m_ore(0, 0) {
    init(state, size, predicate);
}

OreFeature::NaturalStonePredicate::~NaturalStonePredicate() {}

void OreFeature::init(const BlockState* state, int size,
                      const Predicate<const Biome::LegacyBlockData&>* predicate) {
    int id = Block::getId(state->getBlock());
    int data = state->getBlock()->convertBlockStateToLegacyData(state);
    m_ore = Biome::LegacyBlockData(id, data);
    m_size = size;
    m_predicate = predicate;
}

// NON_MATCHING: guard and cached-ID addressing use a different instruction layout.
bool OreFeature::NaturalStonePredicate::apply(const Biome::LegacyBlockData& block) const {
    static int stoneId = Block::getId(Blocks::STONE);
    if (block.m_id == stoneId)
        return StoneBlock::Variant::VARIANTS[block.m_data]->isNatural();
    return false;
}

// NON_MATCHING: preserve the reference's fixed-point tests and visited-bit stepping.
bool OreFeature::place(Level* level, Random& random, const BlockPos& pos) {
    PIXBeginNamedEvent(0.0f, "Place Ore Feature");
    PIXBeginNamedEvent(0.0f, "Prep");
    float angle = random.nextFloat() * Mth::PI;
    double startX = float(pos.getX() + 8) + Mth::sin(angle) * float(m_size) * 0.125f;
    double endX = float(pos.getX() + 8) - Mth::sin(angle) * float(m_size) * 0.125f;
    double startZ = float(pos.getZ() + 8) + Mth::cos(angle) * float(m_size) * 0.125f;
    double endZ = float(pos.getZ() + 8) - Mth::cos(angle) * float(m_size) * 0.125f;
    double startY = pos.getY() + random.nextInt(3) - 2;
    double endY = pos.getY() + random.nextInt(3) - 2;
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0f, "Level generation options");
    double maximumRadius = (double(m_size) * 0.0625 + double(m_size) * 0.0625 + 1.0) * 0.5;
    int lowerX = Mth::floor(std::min(startX, endX) - maximumRadius);
    int lowerY = Mth::floor(std::min(startY, endY) - maximumRadius);
    int lowerZ = Mth::floor(std::min(startZ, endZ) - maximumRadius);
    int upperX = Mth::floor(std::max(startX, endX) + maximumRadius);
    int upperY = Mth::floor(std::max(startY, endY) + maximumRadius);
    int upperZ = Mth::floor(std::max(startZ, endZ) + maximumRadius);
    int height = upperY - lowerY + 1;
    int depth = upperZ - lowerZ + 1;
    unsigned char visited[2048];
    std::memset(visited, 0, ((upperX - lowerX + 1) * height * depth + 7) / 8);
    LevelGenerationOptions* options = nullptr;
    bool checkExclusions = false;
    if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()) {
        options = CConsoleMinecraftApp::sInstance.getLevelGenerationOptions();
        BlockPos lower(lowerX, lowerY, lowerZ);
        BlockPos upper(upperX, upperY, upperZ);
        checkExclusions = options->intersects(lower, upper);
    }
    PIXEndNamedEvent();

    int seaLevel = level->getSeaLevel();
    PIXBeginNamedEvent(0.0f, "Attempting %d placements", m_size);
    for (int step = 0; step <= m_size; step++) {
        float fraction = float(step) / float(m_size);
        double x = startX + (endX - startX) * double(fraction);
        double y = startY + (endY - startY) * double(fraction);
        double z = startZ + (endZ - startZ) * double(fraction);
        double size = random.nextDouble() * double(m_size) * 0.0625;
        double radius = (double(Mth::sin(fraction * Mth::PI) + 1.0f) * size + 1.0) * 0.5;
        int minX = Mth::floor(x - radius);
        int minY = Mth::floor(y - radius);
        int minZ = Mth::floor(z - radius);
        int maxX = Mth::floor(x + radius);
        int maxY = Mth::floor(y + radius);
        int maxZ = Mth::floor(z + radius);

        if (checkExclusions) {
            PIXBeginNamedEvent(0.0f, "Check intersects");
            BlockPos lower(minX, minY, minZ);
            BlockPos upper(maxX, maxY, maxZ);
            bool excluded = options->intersects(lower, upper);
            PIXEndNamedEvent();
            if (excluded)
                continue;
        }
        if (double(seaLevel) < startY) {
            PIXBeginNamedEvent(0.0f, "Early reject tests");
            bool aboveSurface
                = level->getHeightmap(minX, minZ) < minY && level->getHeightmap(maxX, minZ) < minY
                  && level->getHeightmap(minX, maxZ) < minY && level->getHeightmap(maxX, maxZ) < minY;
            PIXEndNamedEvent();
            if (aboveSurface)
                continue;
        }

        PIXBeginNamedEvent(0.0f, "Setting blocks");
        int radiusSquared = int(radius * radius * 65536.0);
        int dx = int((double(minX) + 0.5 - x) * 256.0);
        for (int ix = minX; ix <= maxX; ix++, dx += 256) {
            if (dx * dx >= radiusSquared)
                continue;
            int dy = int((double(minY) + 0.5 - y) * 256.0);
            for (int iy = minY; iy <= maxY; iy++, dy += 256) {
                int distanceXY = dx * dx + dy * dy;
                if (distanceXY >= radiusSquared)
                    continue;
                int index = ((ix - lowerX) * height + iy - lowerY) * depth + minZ - lowerZ;
                int dz = int((double(minZ) + 0.5 - z) * 256.0);
                for (int iz = minZ; iz <= maxZ; iz++, dz += 256) {
                    if (distanceXY + dz * dz < radiusSquared) {
                        unsigned char mask = 1 << (index & 7);
                        // The original skips advancing the bit index when it is already visited.
                        if (visited[index >> 3] & mask)
                            continue;
                        visited[index >> 3] |= mask;
                        PIXBeginNamedEvent(0.0f, "Applying");
                        int id = level->getBlockId(ix, iy, iz);
                        if (id != 0) {
                            Biome::LegacyBlockData block(id, level->getBlockData(ix, iy, iz));
                            if (m_predicate->apply(block))
                                level->setBlockAndData(ix, iy, iz, m_ore.m_id, m_ore.m_data, 0x34);
                        }
                        PIXEndNamedEvent();
                    }
                    index++;
                }
            }
        }
        PIXEndNamedEvent();
    }
    PIXEndNamedEvent();
    PIXEndNamedEvent();
    return true;
}
