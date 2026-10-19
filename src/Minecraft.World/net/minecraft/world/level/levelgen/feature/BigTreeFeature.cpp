#include "net/minecraft/world/level/levelgen/feature/BigTreeFeature.h"

#include "NX/Platform.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/LeafBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cmath>
#include <cstdlib>

// name guessed
BigTreeFeature::FoliageCoords::FoliageCoords(const BlockPos& pos, int branchBase)
    : BlockPos(pos.getX(), pos.getY(), pos.getZ()), m_branchBase(branchBase) {}

// name guessed
int BigTreeFeature::FoliageCoords::getBranchBase() {
    return m_branchBase;
}

// name guessed
// NON_MATCHING | score: 260 (lower is better)
BigTreeFeature::BigTreeFeature(bool update)
    : AbstractTreeFeature(update, 5, Blocks::LOG->defaultBlockState(), Blocks::LEAVES->defaultBlockState(),
                          false),
      m_height(0), m_trunkHeight(0) {
    m_origin = BlockPos::zero;
    m_heightAttenuation = 0.618;
    m_branchSlope = 0.381;
    m_scaleWidth = 1.0;
    m_leafDensity = 1.0;
    m_trunkWidth = 1;
    m_heightLimit = 12;
    m_foliageHeight = 4;
}

BigTreeFeature::~BigTreeFeature() = default;

// name guessed
void BigTreeFeature::init() {
    m_foliageHeight = 5;
}

// name guessed
// NON_MATCHING | score: 1120 (lower is better)
void BigTreeFeature::prepare() {
    m_trunkHeight = static_cast<int>(m_height * m_heightAttenuation);
    if (m_trunkHeight >= m_height)
        m_trunkHeight = m_height - 1;
    int count = static_cast<int>(1.382 + pow(m_leafDensity * m_height / 13.0, 2.0));
    if (count < 1)
        count = 1;
    int trunkTop = m_origin.getY() + m_trunkHeight;
    int layer = m_height - m_foliageHeight;
    m_foliage.clear();
    m_foliage.push_back(FoliageCoords(m_origin.above(layer), trunkTop));
    for (; layer >= 0; --layer) {
        float shape = treeShape(layer);
        if (shape < 0.0f)
            continue;
        for (int i = 0; i < count; ++i) {
            double radius = m_scaleWidth * static_cast<double>(shape)
                            * (static_cast<double>(m_random.nextFloat()) + 0.328);
            float angle = (m_random.nextFloat() * 2.0f) * Mth::PI;
            BlockPos foliage
                = m_origin.offset(radius * Mth::sin(angle) + 0.5, static_cast<double>(layer) - 1.0,
                                  radius * Mth::cos(angle) + 0.5);
            BlockPos clearanceTop = foliage.above(m_foliageHeight);
            if (checkLine(foliage, clearanceTop) != -1)
                continue;
            int dx = m_origin.getX() - foliage.getX();
            int dz = m_origin.getZ() - foliage.getZ();
            int foliageY = foliage.getY();
            float squared = static_cast<float>(dx * dx + dz * dz);
            float distance = sqrtf(squared);
            double branchY = foliageY - static_cast<double>(distance) * m_branchSlope;
            int baseY = branchY > trunkTop ? trunkTop : static_cast<int>(branchY);
            BlockPos branch(m_origin.getX(), baseY, m_origin.getZ());
            if (checkLine(branch, foliage) == -1)
                m_foliage.push_back(FoliageCoords(foliage, branch.getY()));
        }
    }
}

// name guessed
float BigTreeFeature::treeShape(int height) {
    if (height < m_height * 0.3f)
        return -1.0f;
    float half = m_height * 0.5f;
    float relative = half - height;
    float squared = half * half - relative * relative;
    float radius = sqrtf(squared);
    if (relative == 0.0f)
        radius = half;
    else if (fabsf(relative) >= half)
        return 0.0f;
    return radius * 0.5f;
}

// name guessed
int BigTreeFeature::checkLine(const BlockPos& start, const BlockPos& end) {
    BlockPos delta = end.offset(-start.getX(), -start.getY(), -start.getZ());
    int steps = getSteps(delta);
    int dx = delta.getX();
    int dy = delta.getY();
    int dz = delta.getZ();
    if (steps > 0) {
        float stepX = static_cast<float>(dx) / steps;
        float stepY = static_cast<float>(dy) / steps;
        float stepZ = static_cast<float>(dz) / steps;
        for (int i = 0; i <= steps; ++i) {
            BlockPos pos = start.offset(stepX * i + 0.5f, stepY * i + 0.5f, stepZ * i + 0.5f);
            Block* block = m_level->getBlockState(pos)->getBlock();
            if (!reinterpret_cast<AbstractTreeFeature*>(block)->isFree(block))
                return i;
        }
    }
    return -1;
}

// name guessed
void BigTreeFeature::crossection(const BlockPos& center, float radius, const BlockState* state) {
    int extent = static_cast<int>(radius + 0.618);
    for (int x = -extent; x <= extent; ++x) {
        for (int z = -extent; z <= extent; ++z) {
            if (pow(static_cast<double>(std::abs(x)) + 0.5, 2.0)
                    + pow(static_cast<double>(std::abs(z)) + 0.5, 2.0)
                <= static_cast<double>(radius * radius)) {
                BlockPos pos = center.offset(x, 0, z);
                Material* material = m_level->getBlockState(pos)->getMaterial();
                if (material == Material::AIR || material == Material::LEAVES)
                    setBlock(m_level, pos, state);
            }
        }
    }
}

// name guessed
// NON_MATCHING | score: 185 (lower is better)
float BigTreeFeature::foliageShape(int height) {
    if (height >= 0 && height < m_foliageHeight) {
        float radius = 2.0f;
        if (height != m_foliageHeight - 1 && height != 0)
            radius = 3.0f;
        return radius;
    }
    return -1.0f;
}

// name guessed
void BigTreeFeature::foliageCluster(const BlockPos& base) {
    for (int y = 0; y < m_foliageHeight; ++y) {
        BlockPos pos = base.above(y);
        float radius = foliageShape(y);
        const BlockState* state
            = Blocks::LEAVES->defaultBlockState()->setValue(LeafBlock::CHECK_DECAY, false);
        crossection(pos, radius, state);
    }
}

// name guessed
void BigTreeFeature::limb(const BlockPos& start, const BlockPos& end, Block* block) {
    BlockPos delta = end.offset(-start.getX(), -start.getY(), -start.getZ());
    int steps = getSteps(delta);
    int dx = delta.getX();
    int dy = delta.getY();
    int dz = delta.getZ();
    if (steps >= 0) {
        float stepX = static_cast<float>(dx) / steps;
        float stepY = static_cast<float>(dy) / steps;
        float stepZ = static_cast<float>(dz) / steps;
        for (int i = 0; i <= steps; ++i) {
            BlockPos pos = start.offset(stepX * i + 0.5f, stepY * i + 0.5f, stepZ * i + 0.5f);
            LogBlock::LogAxis* axis = getLogAxis(start, pos);
            setBlock(m_level, pos, block->defaultBlockState()->setValue(LogBlock::LOG_AXIS, axis));
        }
    }
}

// name guessed
int BigTreeFeature::getSteps(const BlockPos& delta) {
    int x = std::abs(delta.getX());
    int y = std::abs(delta.getY());
    int z = std::abs(delta.getZ());
    int maximum = y > x ? y : x;
    return z > x && z > y ? z : maximum;
}

// name guessed
LogBlock::LogAxis* BigTreeFeature::getLogAxis(const BlockPos& start, const BlockPos& end) {
    LogBlock::LogAxis* axis = LogBlock::LogAxis::Y;
    int x = std::abs(end.getX() - start.getX());
    int z = std::abs(end.getZ() - start.getZ());
    if (std::max(x, z) > 0) {
        if (x < z)
            axis = LogBlock::LogAxis::Z;
        else
            axis = LogBlock::LogAxis::X;
    }
    return axis;
}

// name guessed
void BigTreeFeature::makeFoliage() {
    for (auto it = m_foliage.begin(); it != m_foliage.end(); ++it)
        foliageCluster(*it);
}

// name guessed
bool BigTreeFeature::trimBranches(int height) {
    return height >= m_height * 0.2;
}

// name guessed
void BigTreeFeature::makeTrunk() {
    BlockPos top = m_origin.above(m_trunkHeight);
    Block* log = Blocks::LOG;
    limb(m_origin, top, log);
    if (m_trunkWidth == 2) {
        limb(m_origin.east(), top.east(), log);
        limb(m_origin.east().south(), top.east().south(), log);
        limb(m_origin.south(), top.south(), log);
    }
}

// name guessed
void BigTreeFeature::makeBranches() {
    for (auto it = m_foliage.begin(); it != m_foliage.end(); ++it) {
        FoliageCoords& foliage = *it;
        int baseY = foliage.getBranchBase();
        BlockPos start(m_origin.getX(), baseY, m_origin.getZ());
        if (start != foliage && trimBranches(baseY - m_origin.getY()))
            limb(start, foliage, Blocks::LOG);
    }
}

// name guessed
bool BigTreeFeature::checkLocation() {
    Block* ground = m_level->getBlockState(m_origin.below())->getBlock();
    if (ground != Blocks::DIRT && ground != Blocks::GRASS && ground != Blocks::FARMLAND)
        return false;
    int obstruction = checkLine(m_origin, m_origin.above(m_height - 1));
    if (obstruction == -1)
        return true;
    if (obstruction < 6)
        return false;
    m_height = obstruction;
    return true;
}

// name guessed
bool BigTreeFeature::place(Level* level, Random& random, const BlockPos& pos) {
    PIXBeginNamedEvent(0, "BigTreeFeature::place");
    m_level = level;
    m_origin = pos;
    m_random = Random(random.nextLong());
    if (m_height == 0)
        m_height = 5 + random.nextInt(m_heightLimit);
    if (!checkLocation()) {
        PIXEndNamedEvent();
        return false;
    }
    prepare();
    makeFoliage();
    makeTrunk();
    makeBranches();
    PIXEndNamedEvent();
    return true;
}
