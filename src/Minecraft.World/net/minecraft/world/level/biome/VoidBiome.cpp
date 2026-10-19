#include "net/minecraft/world/level/biome/VoidBiome.h"

#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"

class VoidBiomeDecorator : public BiomeDecorator {
public:
    // name guessed
    VoidBiomeDecorator() = default;
    void decorate(Level*, Random&, Biome*, const BlockPos&) override;
};

// name guessed
VoidBiome::VoidBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_hostileMobs.clear();
    m_neutralMobs.clear();
    m_passiveMobs.clear();
    m_chickens.clear();
    m_aquaticMobs.clear();
    m_ambientMobs.clear();
    delete m_biomeDecorator;
    m_biomeDecorator = new VoidBiomeDecorator();
}

// name guessed
int VoidBiome::getBaseClass() {
    return _VOID;
}
// name guessed
bool VoidBiome::isAlwaysValidSpawn() {
    return true;
}

// name guessed
void VoidBiomeDecorator::decorate(Level* level, Random&, Biome*, const BlockPos& pos) {
    BlockPos spawn = level->getSharedSpawnPos();
    if (spawn.distSqr(pos.offset(8, spawn.getY(), 8)) > 1024.0)
        return;
    BlockPos lower(spawn.getX() - 16, spawn.getY() - 1, spawn.getZ() - 16);
    BlockPos upper(spawn.getX() + 16, spawn.getY() - 1, spawn.getZ() + 16);
    MutableBlockPos candidate(spawn.getX() - 16, spawn.getY() - 1, spawn.getZ() - 16);
    for (int z = pos.getZ(); z < pos.getZ() + 16; ++z) {
        for (int x = pos.getX(); x < pos.getX() + 16; ++x) {
            if (z >= lower.getZ() && z <= upper.getZ() && x >= lower.getX() && x <= upper.getX()) {
                candidate.set(x, candidate.getY(), z);
                if (x == spawn.getX() && spawn.getZ() == z)
                    level->setBlock(candidate, Blocks::COBBLESTONE->defaultBlockState(), 2, false);
                else
                    level->setBlock(candidate, Blocks::STONE->defaultBlockState(), 2, false);
            }
        }
    }
}
