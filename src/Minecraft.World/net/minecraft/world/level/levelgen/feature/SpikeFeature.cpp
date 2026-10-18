#include "net/minecraft/world/level/levelgen/feature/SpikeFeature.h"

#include "net/minecraft/core/BlockPosIterator.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/entity/item/EnderCrystal.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/phys/AABB.h"
#include <cstdlib>

SpikeFeature::EndSpike::EndSpike(int centerX, int centerZ, int radius, int height, bool guarded)
    : m_centerX(centerX), m_centerZ(centerZ), m_radius(radius), m_height(height), m_guarded(guarded) {
    m_bounds
        = AABB::newPermanent(centerX - radius, 0, centerZ - radius, centerX + radius, 256, centerZ + radius);
}

void SpikeFeature::setSpike(EndSpike* spike) {
    m_spike = spike;
}

SpikeFeature::EndSpike::~EndSpike() {
    delete m_bounds;
}

int SpikeFeature::EndSpike::getCenterX() {
    return m_centerX;
}
int SpikeFeature::EndSpike::getCenterZ() {
    return m_centerZ;
}
int SpikeFeature::EndSpike::getRadius() {
    return m_radius;
}
int SpikeFeature::EndSpike::getHeight() {
    return m_height;
}
bool SpikeFeature::EndSpike::isGuarded() {
    return m_guarded;
}
AABB* SpikeFeature::EndSpike::getTopBoundingBox() {
    return m_bounds;
}

SpikeFeature::SpikeFeature()
    : Feature(false), m_crystalInvulnerable(false), m_spike(nullptr), m_beamTarget(nullptr) {}

SpikeFeature::~SpikeFeature() {
    delete m_beamTarget;
}

void SpikeFeature::setCrystalInvulnerable(bool invulnerable) {
    m_crystalInvulnerable = invulnerable;
}

void SpikeFeature::setCrystalBeamTarget(const BlockPos& target) {
    delete m_beamTarget;
    m_beamTarget = new BlockPos(target.getX(), target.getY(), target.getZ());
}

bool SpikeFeature::place(Level* level, Random& random, const BlockPos& pos) {
    if (!m_spike)
        return false;
    int radius = m_spike->getRadius();
    BlockPosIterator* iterator
        = BlockPos::between(BlockPos(pos.getX() - radius, 1, pos.getZ() - radius),
                            BlockPos(pos.getX() + radius, m_spike->getHeight() + 10, pos.getZ() + radius));
    while (iterator->hasNext()) {
        BlockPos candidate = *iterator->next();
        if (candidate.distSqr(pos.getX(), candidate.getY(), pos.getZ()) <= radius * radius + 1
            && candidate.getY() < m_spike->getHeight()) {
            setBlock(level, candidate, Blocks::OBSIDIAN->defaultBlockState());
        } else if (candidate.getY() > 65) {
            setBlock(level, candidate, Blocks::AIR->defaultBlockState());
        }
    }
    delete iterator;
    if (m_spike->isGuarded()) {
        for (int x = -2; x <= 2; ++x) {
            for (int z = -2; z <= 2; ++z) {
                if (abs(x) == 2 || abs(z) == 2) {
                    setBlock(level, BlockPos(pos.getX() + x, m_spike->getHeight(), pos.getZ() + z),
                             Blocks::IRON_BARS->defaultBlockState());
                    setBlock(level, BlockPos(pos.getX() + x, m_spike->getHeight() + 1, pos.getZ() + z),
                             Blocks::IRON_BARS->defaultBlockState());
                    setBlock(level, BlockPos(pos.getX() + x, m_spike->getHeight() + 2, pos.getZ() + z),
                             Blocks::IRON_BARS->defaultBlockState());
                }
                setBlock(level, BlockPos(pos.getX() + x, m_spike->getHeight() + 3, pos.getZ() + z),
                         Blocks::IRON_BARS->defaultBlockState());
            }
        }
    }
    std::shared_ptr<EnderCrystal> crystal(new EnderCrystal(level));
    if (m_beamTarget)
        crystal->setBeamTarget(new BlockPos(*m_beamTarget));
    else
        crystal->setBeamTarget(nullptr);
    crystal->setInvulnerable(m_crystalInvulnerable);
    crystal->moveTo(pos.getX() + 0.5f, m_spike->getHeight() + 1, pos.getZ() + 0.5f,
                    random.nextFloat() * 360.0f, 0);
    level->addEntity(crystal);
    setBlock(level, BlockPos(pos.getX(), m_spike->getHeight(), pos.getZ()),
             Blocks::BEDROCK->defaultBlockState());
    delete m_spike;
    m_spike = nullptr;
    return true;
}
