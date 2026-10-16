#include "net/minecraft/world/level/biome/Biome.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/block/SandBlock.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"

extern const float gFreezingTemperature;

Biome::LegacyBlockData Biome::STONE(1, 0);
Biome::LegacyBlockData Biome::AIR(0, 0);
Biome::LegacyBlockData Biome::BEDROCK(7, 0);
Biome::LegacyBlockData Biome::GRAVEL(13, 0);
Biome::LegacyBlockData Biome::RED_SANDSTONE(179, 0);
Biome::LegacyBlockData Biome::SANDSTONE(24, 0);
Biome::LegacyBlockData Biome::ICE(79, 0);
Biome::LegacyBlockData Biome::WATER(9, 0);

void Biome::buildSurfaceAt(Level* level, Random& random, ChunkPrimer* primer, int x, int z, double noise) {
    buildSurfaceAtDefault(level, random, primer, x, z, noise);
}

// Surface data uses the original lower 128-layer primer indexing and sea level 63.
void Biome::buildSurfaceAtDefault(Level*, Random& random, ChunkPrimer* primer, int x, int z, double noise) {
    PIXBeginNamedEvent(0.0f, "Biome::buildSurfaceAtDefault");
    LegacyBlockData surface = m_grass;
    LegacyBlockData filler = m_dirt;
    LevelGenerationOptions* options = CConsoleMinecraftApp::sInstance.getLevelGenerationOptions();
    if (options)
        options->getBiomeOverride(m_biomeId, &filler, &surface);
    int depth = static_cast<int>(noise / 3.0 + 3.0 + random.nextDouble() * 0.25);
    MutableBlockPos pos(0, 0, 0);
    int remaining = -1;
    for (int y = 127; y >= 0; --y) {
        int index = ((x & 15) << 7) | ((z & 15) << 11) | y;
        if (y <= random.nextInt(2) + 1) {
            primer->setBlockAndData(index, BEDROCK.m_id, BEDROCK.m_data);
            continue;
        }
        int block = primer->getBlockId(index);
        if (block == 0) {
            remaining = -1;
        } else if (block == 1) {
            if (remaining == -1) {
                if (depth <= 0) {
                    surface = AIR;
                    filler = STONE;
                } else if (y >= 59 && y <= 64) {
                    surface = m_grass;
                    filler = m_dirt;
                    if (options)
                        options->getBiomeOverride(m_biomeId, &filler, &surface);
                }
                if (y < 63 && surface.m_id == 0) {
                    pos.set(x, y, z);
                    if (getTemperature(&pos) < gFreezingTemperature)
                        surface = ICE;
                    else
                        surface = WATER;
                }
                if (y >= 62) {
                    primer->setBlockAndData(index, surface.m_id, surface.m_data);
                } else if (y < 56 - depth) {
                    surface = AIR;
                    filler = STONE;
                    primer->setBlockAndData(index, GRAVEL.m_id, GRAVEL.m_data);
                } else {
                    primer->setBlockAndData(index, filler.m_id, filler.m_data);
                }
                remaining = depth;
            } else if (remaining > 0) {
                primer->setBlockAndData(index, filler.m_id, filler.m_data);
                --remaining;
                if (remaining == 0) {
                    // Retain the original constant-zero branch state for matching.
                    remaining = 0;
                    if (depth > 1 && filler.m_id == 12) {
                        remaining = random.nextInt(4) + (y - 63 < 0 ? 0 : y - 63);
                        filler
                            = filler.m_data == SandBlock::Variant::RED->getData() ? RED_SANDSTONE : SANDSTONE;
                    }
                }
            }
        }
    }
    PIXEndNamedEvent();
}
