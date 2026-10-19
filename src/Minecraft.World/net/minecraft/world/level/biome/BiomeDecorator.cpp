#include "net/minecraft/world/level/biome/BiomeDecorator.h"

#include "NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/Bush.h"
#include "net/minecraft/world/level/block/StoneBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/levelgen/CustomizableSourceSettings.h"
#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"
#include "net/minecraft/world/level/levelgen/feature/BushFeature.h"
#include "net/minecraft/world/level/levelgen/feature/CactusFeature.h"
#include "net/minecraft/world/level/levelgen/feature/ClayFeature.h"
#include "net/minecraft/world/level/levelgen/feature/DeadBushFeature.h"
#include "net/minecraft/world/level/levelgen/feature/FlowerFeature.h"
#include "net/minecraft/world/level/levelgen/feature/HugeMushroomFeature.h"
#include "net/minecraft/world/level/levelgen/feature/OreFeature.h"
#include "net/minecraft/world/level/levelgen/feature/PumpkinFeature.h"
#include "net/minecraft/world/level/levelgen/feature/ReedsFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SandFeature.h"
#include "net/minecraft/world/level/levelgen/feature/SpringFeature.h"
#include "net/minecraft/world/level/levelgen/feature/WaterlilyFeature.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/storage/LevelData.h"

BiomeDecorator::BiomeDecorator() {
    m_clay = new ClayFeature(4);
    m_sand = new SandFeature(Blocks::SAND, 7);
    m_gravelPatch = new SandFeature(Blocks::GRAVEL, 6);
    m_dirt = nullptr;
    m_gravel = nullptr;
    m_granite = nullptr;
    m_diorite = nullptr;
    m_andesite = nullptr;
    m_coal = nullptr;
    m_iron = nullptr;
    m_gold = nullptr;
    m_redstone = nullptr;
    m_diamond = nullptr;
    m_lapis = nullptr;
    m_flowers = new FlowerFeature(static_cast<FlowerBlock*>(Blocks::YELLOW_FLOWER),
                                  FlowerBlock::Flower::YELLOW_FLOWER);
    m_brownMushrooms = new BushFeature(static_cast<Bush*>(Blocks::BROWN_MUSHROOM));
    m_redMushrooms = new BushFeature(static_cast<Bush*>(Blocks::RED_MUSHROOM));
    m_hugeMushrooms = new HugeMushroomFeature;
    m_reeds = new ReedsFeature();
    m_cactus = new CactusFeature();
    m_waterlilies = new WaterlilyFeature();
    m_waterlilyCount = 0;
    m_treeCount = 0;
    m_extraTreeChance = 0.1f;
    m_flowerCount = 2;
    m_grassCount = 1;
    m_deadBushCount = 0;
    m_mushroomCount = 0;
    m_reedCount = 0;
    m_cactusCount = 0;
    m_gravelPatchCount = 1;
    m_sandCount = 3;
    m_clayCount = 1;
    m_hugeMushroomCount = 0;
    m_generateLiquids = true;
    m_decorating = false;
    m_settings = nullptr;
}

BiomeDecorator::~BiomeDecorator() {
    delete m_clay;
    delete m_sand;
    delete m_gravelPatch;
    delete m_dirt;
    delete m_gravel;
    delete m_granite;
    delete m_diorite;
    delete m_andesite;
    delete m_coal;
    delete m_iron;
    delete m_gold;
    delete m_redstone;
    delete m_diamond;
    delete m_lapis;
    delete m_flowers;
    delete m_brownMushrooms;
    delete m_redMushrooms;
    delete m_hugeMushrooms;
    delete m_reeds;
    delete m_cactus;
    delete m_waterlilies;
    delete m_settings;
}

void BiomeDecorator::decorate(Level* level, Random& random, Biome* biome, const BlockPos& pos) {
    delete m_settings;
    CustomizableSourceSettings::Builder* builder
        = CustomizableSourceSettings::Builder::fromString(level->getLevelData()->getGeneratorOptions());
    m_settings = builder->build();
    m_origin = pos;
    delete m_dirt;
    delete m_gravel;
    delete m_granite;
    delete m_diorite;
    delete m_andesite;
    delete m_coal;
    delete m_iron;
    delete m_gold;
    delete m_redstone;
    delete m_diamond;
    delete m_lapis;
    m_dirt = new OreFeature(Blocks::DIRT->defaultBlockState(), m_settings->m_dirtSize);
    m_gravel = new OreFeature(Blocks::GRAVEL->defaultBlockState(), m_settings->m_gravelSize);
    m_granite = new OreFeature(
        Blocks::STONE->defaultBlockState()->setValue(StoneBlock::VARIANT, StoneBlock::Variant::GRANITE),
        m_settings->m_graniteSize);
    m_diorite = new OreFeature(
        Blocks::STONE->defaultBlockState()->setValue(StoneBlock::VARIANT, StoneBlock::Variant::DIORITE),
        m_settings->m_dioriteSize);
    m_andesite = new OreFeature(
        Blocks::STONE->defaultBlockState()->setValue(StoneBlock::VARIANT, StoneBlock::Variant::ANDESITE),
        m_settings->m_andesiteSize);
    m_coal = new OreFeature(Blocks::COAL_ORE->defaultBlockState(), m_settings->m_coalSize);
    m_iron = new OreFeature(Blocks::IRON_ORE->defaultBlockState(), m_settings->m_ironSize);
    m_gold = new OreFeature(Blocks::GOLD_ORE->defaultBlockState(), m_settings->m_goldSize);
    m_redstone = new OreFeature(Blocks::REDSTONE_ORE->defaultBlockState(), m_settings->m_redstoneSize);
    m_diamond = new OreFeature(Blocks::DIAMOND_ORE->defaultBlockState(), m_settings->m_diamondSize);
    m_lapis = new OreFeature(Blocks::LAPIS_ORE->defaultBlockState(), m_settings->m_lapisSize);
    decorate(biome, level, random);
    m_decorating = false;
    delete builder;
}

void BiomeDecorator::decorateOres(Level* level, Random& random) {
    Level::setInstaTick(true);
    decorateDepthSpan(level, random, m_settings->m_dirtCount, m_dirt, m_settings->m_dirtMinHeight,
                      m_settings->m_dirtMaxHeight);
    decorateDepthSpan(level, random, m_settings->m_gravelCount, m_gravel, m_settings->m_gravelMinHeight,
                      m_settings->m_gravelMaxHeight);
    decorateDepthSpan(level, random, m_settings->m_dioriteCount, m_diorite, m_settings->m_dioriteMinHeight,
                      m_settings->m_dioriteMaxHeight);
    decorateDepthSpan(level, random, m_settings->m_graniteCount, m_granite, m_settings->m_graniteMinHeight,
                      m_settings->m_graniteMaxHeight);
    decorateDepthSpan(level, random, m_settings->m_andesiteCount, m_andesite, m_settings->m_andesiteMinHeight,
                      m_settings->m_andesiteMaxHeight);
    decorateDepthSpan(level, random, m_settings->m_coalCount, m_coal, m_settings->m_coalMinHeight,
                      m_settings->m_coalMaxHeight);
    decorateDepthSpan(level, random, m_settings->m_ironCount, m_iron, m_settings->m_ironMinHeight,
                      m_settings->m_ironMaxHeight);
    decorateDepthSpan(level, random, m_settings->m_goldCount, m_gold, m_settings->m_goldMinHeight,
                      m_settings->m_goldMaxHeight);
    decorateDepthSpan(level, random, m_settings->m_redstoneCount, m_redstone, m_settings->m_redstoneMinHeight,
                      m_settings->m_redstoneMaxHeight);
    decorateDepthSpan(level, random, m_settings->m_diamondCount, m_diamond, m_settings->m_diamondMinHeight,
                      m_settings->m_diamondMaxHeight);
    decorateDepthAverage(level, random, m_settings->m_lapisCount, m_lapis, m_settings->m_lapisCenterHeight,
                         m_settings->m_lapisSpread);
    Level::setInstaTick(false);
}

// name guessed
void BiomeDecorator::decorateDepthSpan(Level* level, Random& random, int count, Feature* feature,
                                       int minHeight, int maxHeight) {
    if (maxHeight < minHeight) {
        int height = minHeight;
        minHeight = maxHeight;
        maxHeight = height;
    } else if (maxHeight == minHeight) {
        if (maxHeight < 255)
            ++maxHeight;
        else
            --minHeight;
    }
    int x = m_origin.getX();
    int z = m_origin.getZ();
    MutableBlockPos pos(0, 0, 0);
    for (int i = 0; i < count; ++i) {
        int px = random.nextInt(16) + x;
        int py = random.nextInt(maxHeight - minHeight) + minHeight;
        int pz = random.nextInt(16) + z;
        pos.set(px, py, pz);
        feature->place(level, random, pos);
    }
}

// name guessed
void BiomeDecorator::decorateDepthAverage(Level* level, Random& random, int count, Feature* feature,
                                          int center, int spread) {
    int x = m_origin.getX();
    int z = m_origin.getZ();
    MutableBlockPos pos(0, 0, 0);
    for (int i = 0; i < count; ++i) {
        int px = random.nextInt(16) + x;
        int py = random.nextInt(spread) + random.nextInt(spread) + center - spread;
        int pz = random.nextInt(16) + z;
        pos.set(px, py, pz);
        feature->place(level, random, pos);
    }
}

void BiomeDecorator::decorate(Biome* biome, Level* level, Random& random) {
    PIXBeginNamedEvent(0.0f, "Decorate ores");
    decorateOres(level, random);
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0f, "Decorate sand/clay/gravel");
    for (int i = 0; i < m_sandCount; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        m_sand->place(level, random, level->getTopSolidBlockPos(m_origin.offset(x, 0, z)));
    }
    for (int i = 0; i < m_clayCount; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        m_clay->place(level, random, level->getTopSolidBlockPos(m_origin.offset(x, 0, z)));
    }
    for (int i = 0; i < m_gravelPatchCount; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        m_gravelPatch->place(level, random, level->getTopSolidBlockPos(m_origin.offset(x, 0, z)));
    }
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0f, "Decorate forests");
    int treeCount = m_treeCount;
    if (random.nextFloat() < m_extraTreeChance)
        ++treeCount;
    for (int i = 0; i < treeCount; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        AbstractTreeFeature* tree = static_cast<AbstractTreeFeature*>(biome->getTreeFeature(random));
        tree->init();
        BlockPos pos = level->getHeightmapPos(m_origin.offset(x, 0, z));
        if (tree->place(level, random, pos))
            tree->postPlaceTree(level, random, pos);
        delete tree;
    }
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0f, "Decorate mushrooms/flowers/grass");
    for (int i = 0; i < m_hugeMushroomCount; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        m_hugeMushrooms->place(level, random, level->getHeightmapPos(m_origin.offset(x, 0, z)));
    }
    for (int i = 0; i < m_flowerCount; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY() + 32;
        if (height > 0) {
            int y = random.nextInt(height);
            BlockPos pos = m_origin.offset(x, y, z);
            FlowerBlock::Flower* flower = biome->getRandomFlower(random, &pos);
            FlowerBlock* block = flower->getCategory()->getBlock();
            if (block->getMaterial() != Material::AIR) {
                m_flowers->setFlower(block, flower);
                m_flowers->place(level, random, pos);
            }
        }
    }
    for (int i = 0; i < m_grassCount; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY();
        if (height > 0) {
            int y = random.nextInt(height * 2);
            MemSect(50);
            Feature* grass = biome->getGrassFeature(random);
            MemSect(0);
            grass->place(level, random, m_origin.offset(x, y, z));
            delete grass;
        }
    }
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0f, "Decorate bush/waterlily/mushroom/reeds/pumpkins/cactuses");
    if (m_deadBushCount > 0) {
        Feature* bush = new DeadBushFeature(Blocks::DEADBUSH);
        for (int i = 0; i < m_deadBushCount; ++i) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY();
            if (height > 0) {
                int y = random.nextInt(height * 2);
                bush->place(level, random, m_origin.offset(x, y, z));
            }
        }
        delete bush;
    }
    for (int i = 0; i < m_waterlilyCount; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY();
        if (height > 0) {
            int y = random.nextInt(height * 2);
            BlockPos pos = m_origin.offset(x, y, z);
            while (pos.getY() > 0) {
                BlockPos below = pos.below();
                if (!level->isEmptyBlock(below))
                    break;
                pos = below;
            }
            m_waterlilies->place(level, random, pos);
        }
    }
    for (int i = 0; i < m_mushroomCount; ++i) {
        if (random.nextInt(4) == 0) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            BlockPos pos = level->getHeightmapPos(m_origin.offset(x, 0, z));
            m_brownMushrooms->place(level, random, pos);
        }
        if (random.nextInt(8) == 0) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY();
            if (height > 0) {
                int y = random.nextInt(height * 2);
                BlockPos pos = m_origin.offset(x, y, z);
                m_redMushrooms->place(level, random, pos);
            }
        }
    }
    if (random.nextInt(4) == 0) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY();
        if (height > 0) {
            int y = random.nextInt(height * 2);
            m_brownMushrooms->place(level, random, m_origin.offset(x, y, z));
        }
    }
    if (random.nextInt(8) == 0) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY();
        if (height > 0) {
            int y = random.nextInt(height * 2);
            m_redMushrooms->place(level, random, m_origin.offset(x, y, z));
        }
    }
    for (int i = 0; i < m_reedCount; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY();
        if (height > 0) {
            int y = random.nextInt(height * 2);
            m_reeds->place(level, random, m_origin.offset(x, y, z));
        }
    }
    for (int i = 0; i < 10; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY();
        if (height > 0) {
            int y = random.nextInt(height * 2);
            m_reeds->place(level, random, m_origin.offset(x, y, z));
        }
    }
    if (random.nextInt(32) == 0) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY();
        if (height > 0) {
            int y = random.nextInt(height * 2);
            PumpkinFeature* pumpkin = new PumpkinFeature();
            pumpkin->place(level, random, m_origin.offset(x, y, z));
            delete pumpkin;
        }
    }
    for (int i = 0; i < m_cactusCount; ++i) {
        int x = random.nextInt(16) + 8;
        int z = random.nextInt(16) + 8;
        int height = level->getHeightmapPos(m_origin.offset(x, 0, z)).getY();
        if (height > 0) {
            int y = random.nextInt(height * 2);
            m_cactus->place(level, random, m_origin.offset(x, y, z));
        }
    }
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0f, "Decorate liquids");
    if (m_generateLiquids) {
        Feature* water = new SpringFeature(Blocks::FLOWING_WATER);
        for (int i = 0; i < 50; ++i) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            int maxY = random.nextInt(120) + 8;
            if (maxY > 0) {
                int y = random.nextInt(maxY);
                BlockPos pos = m_origin.offset(x, y, z);
                water->place(level, random, pos);
            }
        }
        delete water;
        Feature* lava = new SpringFeature(Blocks::FLOWING_LAVA);
        for (int i = 0; i < 20; ++i) {
            int x = random.nextInt(16) + 8;
            int z = random.nextInt(16) + 8;
            int y = random.nextInt(random.nextInt(random.nextInt(112) + 8) + 8);
            BlockPos pos = m_origin.offset(x, y, z);
            lava->place(level, random, pos);
        }
        delete lava;
    }
    PIXEndNamedEvent();
}
