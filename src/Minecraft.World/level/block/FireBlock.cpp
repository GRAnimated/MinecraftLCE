#include "Minecraft.World/level/block/FireBlock.h"

#include "Minecraft.Core/ParticleTypes.h"
#include "Minecraft.Client/CMinecraftApp.h"
#include "Minecraft.Client/eGameHostOption.h"
#include "Minecraft.Client/renderer/texture/IconRegister.h"
#include "Minecraft.Server/MinecraftServer.h"
#include "Minecraft.Server/PlayerList.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/Difficulty.h"
#include "Minecraft.World/level/GameRules.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/PortalBlock.h"
#include "Minecraft.World/level/block/TntBlock.h"
#include "Minecraft.World/level/block/state/BlockStateDefinition.h"
#include "Minecraft.World/level/block/state/BooleanProperty.h"
#include "Minecraft.World/level/block/state/IntegerProperty.h"
#include "Minecraft.World/level/dimension/DimensionType.h"
#include "Minecraft.World/level/dimension/TheEndDimension.h"
#include "Minecraft.World/level/material/Material.h"
#include "Minecraft.World/level/material/MaterialColor.h"
#include "Minecraft.World/level/storage/LevelSource.h"
#include "Minecraft.World/phys/AABB.h"
#include "Minecraft.World/sounds/SoundEvents.h"
#include "Minecraft.World/sounds/SoundSource.h"
#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Core/Direction.h"

IntegerProperty* FireBlock::AGE = IntegerProperty::create(L"age", 0, 15);
BooleanProperty* FireBlock::NORTH = BooleanProperty::create(L"north");
BooleanProperty* FireBlock::EAST = BooleanProperty::create(L"east");
BooleanProperty* FireBlock::SOUTH = BooleanProperty::create(L"south");
BooleanProperty* FireBlock::WEST = BooleanProperty::create(L"west");
BooleanProperty* FireBlock::UP = BooleanProperty::create(L"up");

std::wstring fire_0 = L"fire_0";
std::wstring fire_1 = L"fire_1";

void FireBlock::staticCtor() {
    Blocks::FIRE->setFlammable(Blocks::PLANKS, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::DOUBLE_WOODEN_SLAB, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::WOODEN_SLAB, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::FENCE_GATE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::SPRUCE_FENCE_GATE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::BIRCH_FENCE_GATE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::JUNGLE_FENCE_GATE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::DARK_OAK_FENCE_GATE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::ACACIA_FENCE_GATE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::FENCE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::SPRUCE_FENCE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::BIRCH_FENCE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::JUNGLE_FENCE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::DARK_OAK_FENCE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::ACACIA_FENCE, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::OAK_STAIRS, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::BIRCH_STAIRS, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::SPRUCE_STAIRS, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::JUNGLE_STAIRS, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::ACACIA_STAIRS, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::DARK_OAK_STAIRS, 5, 20);
    Blocks::FIRE->setFlammable(Blocks::LOG, 5, 5);
    Blocks::FIRE->setFlammable(Blocks::LOG2, 5, 5);
    Blocks::FIRE->setFlammable(Blocks::LEAVES, 30, 60);
    Blocks::FIRE->setFlammable(Blocks::LEAVES2, 30, 60);
    Blocks::FIRE->setFlammable(Blocks::BOOKSHELF, 30, 20);
    Blocks::FIRE->setFlammable(Blocks::TNT, 15, 100);
    Blocks::FIRE->setFlammable(Blocks::TALLGRASS, 60, 100);
    Blocks::FIRE->setFlammable(Blocks::DOUBLE_PLANT, 60, 100);
    Blocks::FIRE->setFlammable(Blocks::YELLOW_FLOWER, 60, 100);
    Blocks::FIRE->setFlammable(Blocks::RED_FLOWER, 60, 100);
    Blocks::FIRE->setFlammable(Blocks::DEADBUSH, 60, 100);
    Blocks::FIRE->setFlammable(Blocks::WOOL, 30, 60);
    Blocks::FIRE->setFlammable(Blocks::VINE, 15, 100);
    Blocks::FIRE->setFlammable(Blocks::COAL_BLOCK, 5, 5);
    Blocks::FIRE->setFlammable(Blocks::HAY_BLOCK, 60, 20);
    Blocks::FIRE->setFlammable(Blocks::CARPET, 60, 20);
}

FireBlock::FireBlock() : Block(Material::FIRE) {
    DerivedInit();
    const BlockState* state = mBlockStateDefinition->any()
                                  ->setValue(AGE, 0)
                                  ->setValue(NORTH, false)
                                  ->setValue(EAST, false)
                                  ->setValue(SOUTH, false)
                                  ->setValue(WEST, false)
                                  ->setValue(UP, false);

    registerDefaultState(state);
    setTicking(true);

    memset(&mTexture, 0, 0x10);
}

MaterialColor* FireBlock::getMapColor(const BlockState* blockState, LevelSource* levelSource,
                                      const BlockPos& pos) {
    return MaterialColor::FIRE;
}

const BlockState* FireBlock::getBlockState(int data) {
    return defaultBlockState()->setValue(AGE, data);
}

int FireBlock::convertBlockStateToLegacyData(const BlockState* blockState) {
    return blockState->getValue<int>(AGE);
}

const BlockState* FireBlock::fillVirtualBlockStateProperties(const BlockState* blockState,
                                                             LevelSource* levelSource, const BlockPos& pos) {
    if (levelSource->getBlockState(pos.below())->isTopSolidBlocking()
        || Blocks::FIRE->canBurn(levelSource, pos.below())) {
        return defaultBlockState();
    }

    return blockState->setValue(NORTH, canBurn(levelSource, pos.north()))
        ->setValue(EAST, canBurn(levelSource, pos.east()))
        ->setValue(SOUTH, canBurn(levelSource, pos.south()))
        ->setValue(WEST, canBurn(levelSource, pos.west()))
        ->setValue(UP, canBurn(levelSource, pos.above()));
}

FireBlock::~FireBlock() {}

bool FireBlock::isCubeShaped(const BlockState* blockState) {
    return false;
}

RenderShape FireBlock::getRenderShape(const BlockState* blockState) {
    return RenderShape_FIRE;
}

int FireBlock::getBlockFaceShape(LevelSource* levelSource, const BlockState* blockState, const BlockPos& pos,
                                 const Direction* direction) {
    return 8;
}

AABB* FireBlock::getClipAABB(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos) {
    return AABB::sCrossShape;
}

bool FireBlock::isSolidRender(const BlockState* blockState) const {
    return false;
}

bool FireBlock::mayPick() {
    return false;
}

// NON_MATCHING: 89.29% https://decomp.me/scratch/MeKGO
void FireBlock::tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random* random) {
    if (!level->getGameRules()->getBoolean(0))
        return;

    if (!level->mIsLocal) {
        if (!MinecraftServer::getInstance()->getPlayers()->isTrackingBlock(pos, level->mDimension)) {
            level->addToTickNextTick(pos, this, 5 * getTickDelay(level));
            return;
        }
    }

    if (!mayPlace(level, pos)) {
        level->removeBlock(pos);
    }

    Block* belowBlock = level->getBlockState(pos.below())->getBlock();
    bool neverBurn = belowBlock == Blocks::NETHERRACK || belowBlock == Blocks::MAGMA;
    bool isEnd = dynamic_cast<TheEndDimension*>(level->mDimension);
    neverBurn = neverBurn && belowBlock == Blocks::BEDROCK && isEnd;

    int age = blockState->getValue<int>(AGE);

    if (!neverBurn && level->isRaining() && isNearRain(level, pos)) {
        level->removeBlock(pos);
        return;
    }

    if (!neverBurn && age < 15) {
        Property* ageProperty = AGE;
        int data = age + random->nextInt(3) / 2;
        const BlockState* state = blockState->setValue(ageProperty, data);
        level->setBlock(pos, state, 4, false);
    }

    level->addToTickNextTick(pos, this, random->nextInt(10) + getTickDelay(level));

    if (!neverBurn) {
        if (!isValidFireLocation(level, pos)) {
            if (!level->getBlockState(pos.below())->isTopSolidBlocking() || age > 3) {
                level->removeBlock(pos);
            }
            return;
        }

        if (!canBurn(level, pos.below())) {
            if (age == 15 && random->nextInt(4) == 0) {
                level->removeBlock(pos);
                return;
            }
        }
    }

    bool isHumidAt = level->isHumidAt(pos);
    int n3 = (isHumidAt) ? -50 : 0;
    checkBurnOut(level, pos.east(), 300 + n3, random, age);
    checkBurnOut(level, pos.west(), 300 + n3, random, age);
    checkBurnOut(level, pos.below(), 250 + n3, random, age);
    checkBurnOut(level, pos.above(), 250 + n3, random, age);
    checkBurnOut(level, pos.north(), 300 + n3, random, age);
    checkBurnOut(level, pos.south(), 300 + n3, random, age);

    if (!CConsoleMinecraftApp::sInstance.GetGameHostOption((eGameHostOption)14))
        return;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            for (int k = -1; k <= 4; ++k) {
                if (i == 0 && k == 0 && j == 0)
                    continue;

                int fireOddsThreshold = 100;
                if (k > 1) {
                    fireOddsThreshold += (k - 1) * 100;
                }

                BlockPos blockPos = pos.offset(i, k, j);
                int fireOdds = getFireOdds(level, blockPos);
                if (fireOdds <= 0)
                    continue;

                int fireChance = (fireOdds + 40 + level->getDifficulty()->getId() * 7) / (age + 30);
                if (isHumidAt) {
                    fireChance /= 2;
                }

                if (fireChance <= 0 || random->nextInt(fireOddsThreshold) > fireChance
                    || (level->isRaining() && isNearRain(level, blockPos))) {
                    continue;
                }

                int newAge = std::min(15, age + random->nextInt(5) / 4);
                level->setBlock(blockPos, defaultBlockState()->setValue(AGE, newAge), 3, false);
            }
        }
    }
}

void FireBlock::animateTick(const BlockState* blockState, Level* level, const BlockPos& pos, Random* random) {
    if (random->nextInt(24) == 0) {
        level->playLocalSound(pos.getX() + 0.5f, pos.getY() + 0.5f, pos.getZ() + 0.5f,
                              SoundEvents::FIRE_AMBIENT, SoundSource::BLOCKS, 1.0f + random->nextFloat(),
                              random->nextFloat() * 0.7f + 0.3f, false, 16.0f);
    }

    if (level->getBlockState(pos.below())->isTopSolidBlocking()
        || Blocks::FIRE->canBurn(level, pos.below())) {
        for (int i = 0; i < 3; ++i) {
            double x = pos.getX() + random->nextDouble();
            double y = pos.getY() + random->nextDouble() * 0.5 + 0.5;
            double z = pos.getZ() + random->nextDouble();
            level->addParticle(ParticleTypes::LARGE_SMOKE, x, y, z, 0, 0, 0, arrayWithLength<int>());
        }
        return;
    }

    if (Blocks::FIRE->canBurn(level, pos.west())) {
        for (int i = 0; i < 2; ++i) {
            double x = pos.getX() + random->nextDouble() * 0.1;
            double y = pos.getY() + random->nextDouble();
            double z = pos.getZ() + random->nextDouble();
            level->addParticle(ParticleTypes::LARGE_SMOKE, x, y, z, 0, 0, 0, arrayWithLength<int>());
        }
    }
    if (Blocks::FIRE->canBurn(level, pos.east())) {
        for (int i = 0; i < 2; ++i) {
            double x = pos.getX() + 1 - random->nextDouble() * 0.1;
            double y = pos.getY() + random->nextDouble();
            double z = pos.getZ() + random->nextDouble();
            level->addParticle(ParticleTypes::LARGE_SMOKE, x, y, z, 0, 0, 0, arrayWithLength<int>());
        }
    }
    if (Blocks::FIRE->canBurn(level, pos.north())) {
        for (int i = 0; i < 2; ++i) {
            double x = pos.getX() + random->nextDouble();
            double y = pos.getY() + random->nextDouble();
            double z = pos.getZ() + random->nextDouble() * 0.1;
            level->addParticle(ParticleTypes::LARGE_SMOKE, x, y, z, 0, 0, 0, arrayWithLength<int>());
        }
    }
    if (Blocks::FIRE->canBurn(level, pos.south())) {
        for (int i = 0; i < 2; ++i) {
            double x = pos.getX() + random->nextDouble();
            double y = pos.getY() + random->nextDouble();
            double z = pos.getZ() + 1 - random->nextDouble() * 0.1;
            level->addParticle(ParticleTypes::LARGE_SMOKE, x, y, z, 0, 0, 0, arrayWithLength<int>());
        }
    }
    if (Blocks::FIRE->canBurn(level, pos.above())) {
        for (int i = 0; i < 2; ++i) {
            double x = pos.getX() + random->nextDouble();
            double y = pos.getY() + 1 - random->nextDouble() * 0.1;
            double z = pos.getZ() + random->nextDouble();
            level->addParticle(ParticleTypes::LARGE_SMOKE, x, y, z, 0, 0, 0, arrayWithLength<int>());
        }
    }
}

void FireBlock::neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                                const BlockPos& pos2) {
    if (!level->getBlockState(pos.below())->isTopSolidBlocking()) {
        if (!isValidFireLocation(level, pos))
            level->removeBlock(pos);
    }
}

int FireBlock::getTickDelay(Level* level) {
    return 30;
}

void FireBlock::onPlace(Level* level, const BlockPos& pos, const BlockState* blockState) {
    if (level->mDimension->getType() == DimensionType::OVERWORLD
        || level->mDimension->getType() == DimensionType::NETHER) {
        if (static_cast<PortalBlock*>(Blocks::PORTAL)->trySpawnPortal(level, pos, true))
            return;
    }

    if (level->getBlockState(pos.below())->isTopSolidBlocking() || isValidFireLocation(level, pos)) {
        level->addToTickNextTick(pos, this, getTickDelay(level) + level->mRandom->nextInt(10));
    } else {
        level->removeBlock(pos);
    }
}

int FireBlock::getResourceCount(Random*) {
    return 0;
}

int FireBlock::getRenderLayer() {
    return 0;
}

bool FireBlock::mayPlace(Level* level, const BlockPos& pos) {
    if (level->getBlockState(pos.below())->isTopSolidBlocking())
        return true;
    else if (isValidFireLocation(level, pos))
        return true;
    return false;
}

bool FireBlock::canInstantlyTick() {
    return false;
}

void FireBlock::registerIcons(IconRegister* iconRegister) {
    mTexture[0] = iconRegister->registerIcon(fire_0);
    mTexture[1] = iconRegister->registerIcon(fire_1);
}

Texture* FireBlock::getTexture(const Direction* direction, const BlockState* blockState) {
    return mTexture[0];
}

// NON_MATCHING: There should be a central static array variable that gets overwritten by each of these
// functions
BlockStateDefinition* FireBlock::createBlockStateDefinition() {
    static const Property* blockProperties[] = {FireBlock::AGE,   FireBlock::NORTH, FireBlock::EAST,
                                                FireBlock::SOUTH, FireBlock::WEST,  FireBlock::UP};

    return new BlockStateDefinition(this, blockProperties);
}

void FireBlock::setFlammable(Block* block, int a3, int a4) {
    mFlameOdds[block] = a3;
    mBurnOdds[block] = a4;
}

bool FireBlock::canBurn(LevelSource* level, BlockPos const& pos) {
    return getFlameOdds(level->getBlockState(pos)->getBlock()) > 0;
}

bool FireBlock::isNearRain(Level* level, BlockPos const& pos) {
    return level->isRainingAt(pos) || level->isRainingAt(pos.west()) || level->isRainingAt(pos.east())
           || level->isRainingAt(pos.north()) || level->isRainingAt(pos.south());
}

void FireBlock::checkBurnOut(Level* level, BlockPos const& pos, int n, Random* random, int n2) {
    int n3 = getBurnOdd(level->getBlockState(pos)->getBlock());

    if (random->nextInt(n) < n3) {
        const BlockState* blockState = level->getBlockState(pos);

        if (random->nextInt(n2 + 10) < 5 && !level->isRainingAt(pos)
            && CConsoleMinecraftApp::sInstance.GetGameHostOption((eGameHostOption)14)) {
            int n4 = std::min(n2 + random->nextInt(5) / 4, 15);
            level->setBlock(pos, defaultBlockState()->setValue(AGE, n4), 3, false);
        } else {
            level->removeBlock(pos);
        }

        TntBlock* block = static_cast<TntBlock*>(blockState->getBlock());
        if (block == Blocks::TNT)
            block->destroy(level, pos, blockState->setValue(TntBlock::EXPLODE, true));
    }
}

bool FireBlock::isValidFireLocation(Level* level, BlockPos const& pos) {
    for (auto it = Direction::VALUES.begin(); it != Direction::VALUES.end(); ++it) {
        const Direction* direction = *it;
        BlockPos newPos = pos.relative(direction);
        if (canBurn(level, newPos))
            return true;
    }
    return false;
}

int FireBlock::getFireOdds(Level* level, const BlockPos& pos) {
    if (!level->isEmptyBlock(pos))
        return false;

    int n = 0;

    for (auto it = Direction::VALUES.begin(); it != Direction::VALUES.end(); ++it) {
        const Direction* direction = *it;
        Block* block = level->getBlockState(pos.relative(direction))->getBlock();
        n = std::max(getFlameOdds(block), n);
    }

    return n;
}

int FireBlock::getFlameOdds(Block* block) {
    auto it = mFlameOdds.find(block);
    if (it != mFlameOdds.end())
        return it->second;

    return 0;
}

int FireBlock::getBurnOdd(Block* block) {
    auto it = mBurnOdds.find(block);
    if (it != mBurnOdds.end())
        return it->second;

    return 0;
}

Texture* FireBlock::getTextureLayer(int offset) {
    return mTexture[offset];
}
