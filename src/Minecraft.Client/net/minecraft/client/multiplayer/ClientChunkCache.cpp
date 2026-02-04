#include "Minecraft.Client/net/minecraft/client/multiplayer/ClientChunkCache.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/dimension/Dimension.h"
#include "net/minecraft/world/level/dimension/DimensionType.h"
#include "net/minecraft/world/level/levelgen/ChunkPrimer.h"
#include "net/minecraft/world/level/storage/LevelData.h"

// NON_MATCHING | Score: 16235 (lower is better)
ClientChunkCache::ClientChunkCache(Level* lvl) : m_chunkPos(ChunkPos(0, 0)) {
    this->unk3 = nullptr;
    this->unk9 = nullptr;
    this->unk10 = nullptr;
    this->unk10 = nullptr;
    this->unk11 = nullptr;
    this->unk12 = nullptr;
    this->unk13 = nullptr;
    this->unk14 = nullptr;
    this->unk16 = nullptr;
    this->unk17 = nullptr;
    this->unk18 = nullptr;
    this->unk19 = nullptr;
    this->unk20 = nullptr;
    this->unk21 = nullptr;

    int bounds;

    int xzSize = lvl->mDimension->getXZSize();
    if (xzSize >= 0)
        bounds = xzSize;
    else
        bounds = xzSize + 1;

    this->m_xzSize2 = xzSize;
    this->unk27 = bounds >> 1;
    this->mXZSize = xzSize;

    this->unk28 = new char[xzSize * xzSize];
    memset(this->unk28, 0, this->m_xzSize2 * this->m_xzSize2);

    this->m_emptyChunk = new EmptyLevelChunk(lvl, 0, 0);
    this->unk1 = nullptr;
    this->unk4 = 0;
    this->unk2 = nullptr;

    if (lvl->mDimension->getType() == DimensionType::OVERWORLD) {
        arrayWithLength<unsigned char> blocks = arrayWithLength<unsigned char>(0x8000u, true);
        arrayWithLength<unsigned char> data = arrayWithLength<unsigned char>(0x4000u, true);

        LevelData* dat = lvl->getLevelData();
        if (dat->getGeneratorType() == LevelType::FLAT) {  // If flat world
            for (int x = 0; x != 16; ++x)                  // from 0 to 16 chunk coords x
            {
                for (int y = 0; y != 128; ++y)  // from 0 to 128 chunk coords y (old height limit)
                {
                    if (y == 3)  // if y is 3, which is the grass layer height on a superflat world
                    {
                        for (int z = 0; z != 16; z++)  // from 0 to 16 chunk coords z
                        {
                            blocks[y | (x << 11) | (z << 7)] = Blocks::GRASS->getId();  // place a grass block
                        }
                    } else if (y > 2)  // if y is larger than 2, but not 3, we are above the topmost layer of
                                       // the superflat world
                    {
                        for (int z = 0; z != 16; z++) {            // from 0 to 16 chunk coords z
                            blocks[y | (x << 11) | (z << 7)] = 0;  // place an air block
                        }
                    } else  // otherwise, y is below the grass layer
                    {
                        for (int z = 0; z != 16; z++)  // from 0 to 16 chunk coords z
                        {
                            blocks[y | (x << 11) | (z << 7)] = Blocks::DIRT->getId();  // place a dirt block
                        }
                    }
                }
            }
        } else {  // otherwise, we're in a normal generator (e.g. Default, Large Biomes)
            for (int z = 0; z != 16; ++z)  // from 0 to 16 chunk coords z
            {
                for (int y = 0; y != 128; ++y)  // from 0 to 128 chunk coords y (old height limit)
                {
                    for (int x = 0; x != 16; ++x)  // from 0 to 16 chunk coords x
                    {
                        int sl = lvl->getSeaLevel();  // get sea level
                        int id;

                        // TODO can't get this to look neat without mismatching
                        Block* blk = Blocks::STONE;  // default block is stone

                        // if we are above 10 blocks below sea level, set the block to water, then check if y
                        // is higher than sea level if it is, we will fall through to set ID to 0, which is
                        // AIR otherwise, blk is now water, so we will fall through and get the ID of our
                        // water block
                        if (y > sl - 10 && (blk = Blocks::WATER, y >= sl))
                            id = 0;  // set block to air
                        else
                            id = blk->getId();  // set block to Water, if between sea level and 10 blocks
                                                // below sea level, otherwise Stone.

                        blocks[y | (z << 11) | (x << 7)] = id;  // set the ID in the array
                    }
                }
            }
        }

        ChunkPrimer primer = ChunkPrimer(false, blocks, data);
        this->m_waterChunk = new WaterLevelChunk(lvl, &primer, 0, 0);

        delete blocks.data;
        delete data.data;

        // sets skylight
        if (dat->getGeneratorType() == LevelType::FLAT) {
            for (int x = 0; x != 16; x++) {       // from 0 to 16 chunk coords x
                for (int y = 0; y != 128; y++) {  // from 0 to 128 chunk coords y (old world height)
                    if (y
                        >= 3) {  // if y is bigger or equal to 3, which is any block at or above the top block
                        for (int z = 0; z != 16; z++) {  // from 0 to 16 chunk coords z
                            m_waterChunk->setLevelChunkBrightness(LightLayer::SKY, x, y, z,
                                                                  15);  // set light level to 16
                        }
                    }
                }
            }
        } else {
            for (int x = 0; x != 16; x++) {          // from 0 to 16 chunk coords x
                for (int y = 0; y != 128; y++) {     // from 0 to 128 chunk coords y (old world height)
                    for (int z = 0; z != 16; z++) {  // from 0 to 16 chunk coords z
                        int brightness = 2;          // underwater/in-block brightness

                        if (y >= lvl->getSeaLevel() - 1)  // if we are above the sea level minus 1
                            brightness = 15;              // set our brightness to max, as this is skylight

                        m_waterChunk->setLevelChunkBrightness(LightLayer::SKY, x, y, z,
                                                              brightness);  // set the brightness
                    }
                }
            }
        }
    } else {
        this->m_waterChunk = nullptr;  // no need for a water chunk when not in the overworld
    }

    this->m_level = lvl;
    this->m_dimension = lvl->mDimension;

    this->unk15 = new char[8 * (this->m_xzSize2 * this->m_xzSize2)];
    memset(this->unk15, 0, 8 * (this->m_xzSize2 * this->m_xzSize2));

    InitializeCriticalSectionAndSpinCount(&this->m_mutex, 0);
}
