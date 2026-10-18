#include "net/minecraft/world/level/biome/TheEndBiome.h"

#include <algorithm>

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/dimension/EndDragonFight.h"
#include "net/minecraft/world/level/dimension/TheEndDimension.h"
#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include "net/minecraft/world/level/levelgen/feature/SpikeFeature.h"

class EndPodiumFeature : public Feature {
public:
    EndPodiumFeature(bool active);
    bool place(Level*, Random&, const BlockPos&) override;

private:
    bool m_active;
};

class TheEndBiomeDecorator : public BiomeDecorator {
public:
    TheEndBiomeDecorator();
    ~TheEndBiomeDecorator() override;
    void decorate(Biome*, Level*, Random&) override;
    static const int SPIKES[8][7];

private:
    SpikeFeature* m_spike;
    Feature* m_podium;
};

inline TheEndBiomeDecorator::~TheEndBiomeDecorator() = default;

TheEndBiomeDecorator::TheEndBiomeDecorator() {
    m_spike = new SpikeFeature;
    m_podium = new EndPodiumFeature(false);
}

// Chunk origins, centers, radii, height offsets and guarded flags from the Switch table.
const int TheEndBiomeDecorator::SPIKES[8][7]
    = {{32, -16, 40, 0, 2, 12, 0},   {16, 16, 28, 28, 2, 15, 0},   {-16, 32, 0, 40, 2, 18, 0},
       {-32, 16, -28, 28, 3, 21, 0}, {-48, -16, -40, 0, 3, 24, 0}, {-32, -32, -28, -28, 3, 27, 0},
       {-16, -48, 0, -40, 4, 30, 1}, {16, -32, 28, -28, 4, 33, 1}};

extern BlockPos endTerrainSpawn;

void TheEndBiomeDecorator::decorate(Biome*, Level* level, Random& random) {
    decorateOres(level, random);
    for (unsigned long i = 0; i < 8; ++i) {
        if (m_origin.getX() == SPIKES[i][0] && m_origin.getZ() == SPIKES[i][1]) {
            m_spike->setSpike(new SpikeFeature::EndSpike(SPIKES[i][2], SPIKES[i][3], SPIKES[i][4],
                                                         SPIKES[i][5] + endTerrainSpawn.getY(),
                                                         i == 6 || i == 7));
            m_spike->place(level, random, BlockPos(SPIKES[i][2], endTerrainSpawn.getY(), SPIKES[i][3]));
        }
    }
    if (m_origin.getX() == 0 && m_origin.getZ() == 0) {
        if (TheEndDimension* dimension = dynamic_cast<TheEndDimension*>(level->m_dimension))
            dimension->getDragonFight()->createNewDragon();
    }
}

TheEndBiome::TheEndBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_hostileMobs.clear();
    m_passiveMobs.clear();
    m_chickens.clear();
    m_fieldD8.clear();
    m_aquaticMobs.clear();
    m_ambientMobs.clear();
    m_hostileMobs.push_back(new MobSpawnerData(eEnderMan, 10, 4, 4));
    m_grass
        = LegacyBlockData(3, Blocks::DIRT->convertBlockStateToLegacyData(Blocks::DIRT->defaultBlockState()));
    m_dirt
        = LegacyBlockData(3, Blocks::DIRT->convertBlockStateToLegacyData(Blocks::DIRT->defaultBlockState()));
    m_biomeDecorator = new TheEndBiomeDecorator;
}

int TheEndBiome::getBaseClass() {
    return _THE_END;
}
bool TheEndBiome::isNatural() {
    return false;
}

unsigned int TheEndBiome::getSkyColor(float) {
    return Minecraft::GetInstance()->getColourTable()->getColour(Sky_Sky);
}

Vec3* TheEndBiome::getFogColor(float timeOfDay, float) const {
    int color = Minecraft::GetInstance()->getColourTable()->getColour(End_Fog_Colour);
    float cosine = Mth::cos(timeOfDay * 3.1415927f * 2.0f);
    float factor = std::min(std::max(cosine + cosine + 0.5f, 0.0f), 1.0f);
    float red = (color >> 16 & 255) / 255.0f;
    float green = (color >> 8 & 255) / 255.0f;
    float blue = (color & 255) / 255.0f;
    factor = factor * 0.0f + 0.15f;
    red *= factor;
    green *= factor;
    blue *= factor;
    return Vec3::newTemp(red, green, blue);
}
