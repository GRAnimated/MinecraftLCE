#include "net/minecraft/world/level/levelgen/feature/FlowerFeature.h"

#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/dimension/Dimension.h"

FlowerFeature::FlowerFeature(FlowerBlock* block, FlowerBlock::Flower* flower) : Feature(false) {
    setFlower(block, flower);
}

// name guessed: the setup routine at 0x71001843ac.
void FlowerFeature::setFlower(FlowerBlock* block, FlowerBlock::Flower* flower) {
    m_flower = block;
    const BlockState* state = block->defaultBlockState();
    m_state = state->setValue<FlowerBlock::Flower*>(block->getFlowerProperty(), flower);
}

bool FlowerFeature::place(Level* level, Random& random, const BlockPos& pos) {
    if (CConsoleMinecraftApp::sInstance.getLevelGenerationOptions()) {
        LevelGenerationOptions* options = CConsoleMinecraftApp::sInstance.getLevelGenerationOptions();
        BlockPos lower;
        BlockPos upper;
        lower = pos.offset(-8, -4, -8);
        upper = pos.offset(8, 4, 8);
        if (options->intersects(lower, upper))
            return false;
    }
    for (int i = 0; i < 64; ++i) {
        int dx = random.nextInt(8) - random.nextInt(8);
        int dy = random.nextInt(4) - random.nextInt(4);
        int dz = random.nextInt(8) - random.nextInt(8);
        BlockPos candidate = pos.offset(dx, dy, dz);
        if (level->isEmptyBlock(candidate) && (!level->m_dimension->isHasCeiling() || candidate.getY() < 127)
            && m_flower->canSurvive(level, candidate, m_state)) {
            level->setBlock(candidate, m_state, 2, false);
        }
    }
    return true;
}
