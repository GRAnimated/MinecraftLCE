#include "net/minecraft/world/level/biome/Biome.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/FoliageColor.h"
#include "net/minecraft/world/level/GrassColor.h"
#include "net/minecraft/world/level/biome/BeachBiome.h"
#include "net/minecraft/world/level/biome/DesertBiome.h"
#include "net/minecraft/world/level/biome/ExtremeHillsBiome.h"
#include "net/minecraft/world/level/biome/ForestBiome.h"
#include "net/minecraft/world/level/biome/HellBiome.h"
#include "net/minecraft/world/level/biome/IceBiome.h"
#include "net/minecraft/world/level/biome/JungleBiome.h"
#include "net/minecraft/world/level/biome/MesaBiome.h"
#include "net/minecraft/world/level/biome/MushroomIslandBiome.h"
#include "net/minecraft/world/level/biome/MutatedForestBiome.h"
#include "net/minecraft/world/level/biome/MutatedSavannaBiome.h"
#include "net/minecraft/world/level/biome/OceanBiome.h"
#include "net/minecraft/world/level/biome/PlainsBiome.h"
#include "net/minecraft/world/level/biome/RiverBiome.h"
#include "net/minecraft/world/level/biome/SavannaBiome.h"
#include "net/minecraft/world/level/biome/StoneBeachBiome.h"
#include "net/minecraft/world/level/biome/SwampBiome.h"
#include "net/minecraft/world/level/biome/TaigaBiome.h"
#include "net/minecraft/world/level/biome/TheEndBiome.h"
#include "net/minecraft/world/level/biome/VoidBiome.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/levelgen/feature/FlowerFeature.h"
#include "net/minecraft/world/level/levelgen/synth/PerlinSimplexNoise.h"
#include "net/minecraft/world/level/material/MaterialColor.h"

Biome::BiomeProperties::BiomeProperties(const std::wstring& name) {
    mBiomeName = name;
    mDepth = 0.1f;
    mScale = 0.2f;
    mTemperature = 0.5f;
    mDownfall = 0.5f;
    mWaterColor = 0xFFFFFF;
    mIsSnow = false;
    mIsNotDry = true;
    mMutatedBiomeName = L"";
}

Biome::BiomeProperties* Biome::BiomeProperties::depth(float depth) {
    mDepth = depth;
    return this;
}

Biome::BiomeProperties* Biome::BiomeProperties::downfall(float downfall) {
    mDownfall = downfall;
    return this;
}

Biome::BiomeProperties* Biome::BiomeProperties::dry() {
    mIsNotDry = false;
    return this;
}

Biome::BiomeProperties* Biome::BiomeProperties::mutated(const std::wstring& mutatedName) {
    mMutatedBiomeName = mutatedName;
    return this;
}

Biome::BiomeProperties* Biome::BiomeProperties::scale(float scale) {
    mScale = scale;
    return this;
}

Biome::BiomeProperties* Biome::BiomeProperties::snow() {
    mIsSnow = true;
    return this;
}

Biome::BiomeProperties* Biome::BiomeProperties::temperature(float temperature) {
    mTemperature = temperature;
    return this;
}

Biome::BiomeProperties* Biome::BiomeProperties::waterColor(int waterColor) {
    mWaterColor = waterColor;
    return this;
}

Biome::Biome(Biome::EBiomeIDs biomeID, Biome::BiomeProperties* biomeProperties) : mBiomeID(biomeID) {
    mPreviewColor = Preview_Plains;

    mGrass.id = Blocks::GRASS->getId();
    mGrass.data = Blocks::GRASS->convertBlockStateToLegacyData(Blocks::GRASS->defaultBlockState());

    mDirt.id = Blocks::DIRT->getId();
    mDirt.data = Blocks::DIRT->convertBlockStateToLegacyData(Blocks::DIRT->defaultBlockState());

    mBiomeName = biomeProperties->mBiomeName;
    mDepth = biomeProperties->mDepth;
    mScale = biomeProperties->mScale;
    mTemperature = biomeProperties->mTemperature;
    mDownfall = biomeProperties->mDownfall;
    mIsSnow = biomeProperties->mIsSnow;
    mIsDry = biomeProperties->mIsNotDry;
    mMutatedBiomeName = biomeProperties->mMutatedBiomeName;

    delete biomeProperties;

    mWaterColor = NOTSET;
    Biome::BIOMES[biomeID] = this;
    mBiomeDecorator = createDecorator();

    mPassiveMobs.push_back(new Biome::MobSpawnerData(eSheep, 12, 4, 4));
    mPassiveMobs.push_back(new Biome::MobSpawnerData(ePig, 10, 4, 4));
    mChickens.push_back(new Biome::MobSpawnerData(eChicken, 10, 4, 4));
    mPassiveMobs.push_back(new Biome::MobSpawnerData(eCow, 8, 4, 4));
    mHostileMobs.push_back(new Biome::MobSpawnerData(eSpider, 100, 4, 4));
    mHostileMobs.push_back(new Biome::MobSpawnerData(eZombie, 95, 4, 4));
    mHostileMobs.push_back(new Biome::MobSpawnerData(eZombieVillager, 5, 1, 1));
    mHostileMobs.push_back(new Biome::MobSpawnerData(eSkeleton, 100, 4, 4));
    mHostileMobs.push_back(new Biome::MobSpawnerData(eCreeper, 100, 4, 4));
    if (biomeID != BiomeID_HELL && biomeID != BiomeID_THE_END)
        mNeutralMobs.push_back(new Biome::MobSpawnerData(eSlime, 100, 4, 4));
    mHostileMobs.push_back(new Biome::MobSpawnerData(eEnderMan, 10, 1, 4));
    mHostileMobs.push_back(new Biome::MobSpawnerData(eWitch, 5, 1, 1));
    mAquaticMobs.push_back(new Biome::MobSpawnerData(eSquid, 10, 4, 4));
    mAmbientMobs.push_back(new Biome::MobSpawnerData(eBat, 10, 8, 8));

    mNameId = -1;
}

Biome** Biome::getBiomes() {
    return BIOMES;
}

Biome* Biome::getBiome(int id) {
    return getBiome(id, nullptr);
}

Biome* Biome::getBiome(int id, Biome* biome) {
    if ((unsigned int)id > BiomeID_LIMIT)  // cast required for match
        return OCEAN;
    if (BIOMES[id])
        return BIOMES[id];
    return biome;
}

Block* Biome::getRandomFlower(Random& random, const BlockPos* pos) {
    if (random.nextInt(3) > 0)
        return (Block*)FlowerBlock::Flower::YELLOW_FLOWER;
    return (Block*)FlowerBlock::Flower::RED_FLOWER;
}

unsigned int Biome::getSkyColor(float timeOfDay) {
    if (Minecraft::GetInstance()->isUsingDefaultSkin()) {
        float f1 = Mth::clamp(timeOfDay / 3.0f, -1.0f, 1.0f);
        return Mth::hsvToRgb((f1 * -0.05f) + 0.62222f, (f1 * 0.1f) + 0.5f, 1.0f);
    }
    ColourTable* colourTable = Minecraft::GetInstance()->getColourTable();
    return colourTable->getColour(mSkyColor);
}

Biome* Biome::byId(int id) {
    return Biome::BIOMES[id];
}

bool Biome::hasSnow() {
    return isSnowCovered();
}

bool Biome::hasRain() {
    return !isSnowCovered() && mIsDry;
}

bool Biome::isHumid() {
    return getDownfall() > 0.85f;
}

float Biome::getCreatureProbability() {
    return 0.1f;
}

float Biome::getTemperature(const BlockPos* pos) {
    if (pos->getY() > 64) {
        float noise = TEMPERATURE_NOISE->getValue(pos->getX() * 0.125f, pos->getZ() * 0.125f) * 4.0;
        return getTemperature() + (noise + pos->getY() + -64.0f) * -0.05f / 30.0f;
    }
    return getTemperature();
}

unsigned int Biome::getGrassColor(const BlockPos* pos) {
    return GrassColor::get(Mth::clamp(getTemperature(pos), 0.0f, 1.0f),
                           Mth::clamp(getDownfall(), 0.0f, 1.0f));
}

unsigned int Biome::getFoliageColor(const BlockPos* pos) {
    return FoliageColor::get(Mth::clamp(getTemperature(pos), 0.0f, 1.0f),
                             Mth::clamp(getDownfall(), 0.0f, 1.0f));
}

void Biome::setGrassColor(const BlockPos* pos, unsigned int color) {
    double temperature = Mth::clamp(getTemperature(pos), 0.0f, 1.0f);
    double downfall = Mth::clamp(getDownfall(), 0.0f, 1.0f);
    GrassColor::set(temperature, downfall, color);
}

void Biome::setFoliageColor(const BlockPos* pos, unsigned int color) {
    double temperature = Mth::clamp(getTemperature(pos), 0.0f, 1.0f);
    double downfall = Mth::clamp(getDownfall(), 0.0f, 1.0f);
    FoliageColor::set(temperature, downfall, color);
}

int Biome::getTemperatureCategory() {
    float temperature = getTemperature();
    if (temperature < 0.2)
        return 1;
    if (temperature < 1.0f)
        return 2;
    return 3;
}

bool Biome::isAlwaysValidSpawn() {
    return false;
}

void Biome::getWaterColor() {
    Minecraft* minecraft = Minecraft::GetInstance();
    ColourTable* colourTable = minecraft->getColourTable();
    colourTable->getColour(mWaterColor);
}

Vec3* Biome::getFogColor(float a2, float a3) const {
    float v3 = Mth::cos(a2 * 3.1415927f * 2.0f);
    float v4 = std::min(std::max((v3 + v3) + 0.5f, 0.0f), 1.0f);

    unsigned int color = Minecraft::GetInstance()->getColourTable()->getColour(Default_Fog_Colour);

    float f1 = (color >> 16 & 0xFF) / 255.0f;
    float f2 = (color >> 8 & 0xFF) / 255.0f;
    float f3 = (color & 0xFF) / 255.0f;

    f1 *= (v4 * 0.94f) + 0.06f;
    f2 *= (v4 * 0.94f) + 0.06f;
    f3 *= (v4 * 0.91f) + 0.09f;

    return Vec3::newTemp(f1, f2, f3);
}

bool Biome::isFoggy() {
    return false;
}

bool Biome::isNatural() {
    return true;
}

bool Biome::isSnowCovered() {
    return mIsSnow;
}

Biome* Biome::setNameAndDescription(int name, int desc) {
    this->mNameId = name;
    this->mDescriptionId = desc;
    return this;
}

// does nothing on Switch
void Biome::generateColoursDebugOutput() {
    return;
}

// NON_MATCHING | Score: 5785 (lower is better)
// literally took me so many hours to get it finally partially completed (all registered, down to 99k score)
// but then I realized I had to make the last property of the BiomeProperties be set separately instead of
// chained
// ...or did I? Nope, just a waste of time...
// so then I figured out that I had to merge the BiomeProperties constructors directly into the Biome
// constructors... This got me down to like 70k iirc, which was closer but not close enough. then I saw that
// the wstring that gets assigned to the BiomeProperties constructor gets deleted after the var has been
// created but before the static Biome* has been set so that means I had to separate out the Biome's setters
// from the constructor init... and here I am, at 5785 score. -Dexrn
void Biome::staticCtor() {
    Biome::OCEAN = new OceanBiome(BiomeID_OCEAN, (new BiomeProperties(L"Ocean"))->depth(-1.0)->scale(0.1));

    Biome::OCEAN->setPreviewColor(Preview_Ocean)
        ->setNameAndDescription(StringIDs::Ocean, StringIDs::ATemperateBiomeWithLittleVegetationOrFeatures)
        ->setWaterSkyColor(Water_Ocean, Sky_Ocean);

    Biome::PLAINS = (new PlainsBiome(
        BiomeID_PLAINS, false,
        (new BiomeProperties(L"Plains"))->depth(0.125)->scale(0.05)->temperature(0.8)->downfall(0.4)));

    Biome::PLAINS->setPreviewColor(Preview_Plains)
        ->setNameAndDescription(StringIDs::Plains, StringIDs::ATemperateGrassLandBiomeWithFewTrees)
        ->setWaterSkyColor(Water_Plains, Sky_Plains);

    Biome::DESERT = (new DesertBiome(
        BiomeID_DESERT,
        (new BiomeProperties(L"Desert"))->depth(0.125)->scale(0.05)->temperature(2.0)->downfall(0.0)->dry()));

    Biome::DESERT->setPreviewColor(Preview_Desert)
        ->setNameAndDescription(StringIDs::Desert, StringIDs::AHotBiomeWithNoRainfallWithLittle)
        ->setWaterSkyColor(Water_Desert, Sky_Desert);

    Biome::EXTREME_HILLS = (new ExtremeHillsBiome(
        BiomeID_EXTREME_HILLS, ExtremeHillsBiome::DEFAULT,
        (new BiomeProperties(L"Extreme Hills"))->depth(1.0)->scale(0.5)->temperature(0.2)->downfall(0.3)));

    Biome::EXTREME_HILLS->setPreviewColor(Preview_ExtremeHills)
        ->setNameAndDescription(StringIDs::ExtremeHills,
                                StringIDs::AColdBiomeWithSparseVegetationLivestockWill)
        ->setWaterSkyColor(Water_ExtremeHills, Sky_ExtremeHills);

    Biome::FOREST = (new ForestBiome(BiomeID_FOREST, ForestBiome::DEFAULT,
                                     (new BiomeProperties(L"Forest"))->temperature(0.7)->downfall(0.8)));

    Biome::FOREST->setPreviewColor(Preview_Forest)
        ->setNameAndDescription(StringIDs::Forest, StringIDs::ATemperateWoodlandBiomeWithPlentifulFlowersAnd)
        ->setWaterSkyColor(Water_Forest, Sky_Forest);

    Biome::TAIGA = (new TaigaBiome(
        BiomeID_TAIGA, TaigaBiome::DEFAULT,
        (new BiomeProperties(L"Taiga"))->depth(0.2)->scale(0.2)->temperature(0.25)->downfall(0.8)));

    Biome::TAIGA->setPreviewColor(Preview_Taiga)
        ->setNameAndDescription(StringIDs::Taiga, StringIDs::AConiferousWoodlandBiomeVillagesCanBeFound)
        ->setWaterSkyColor(Water_Taiga, Sky_Taiga);

    Biome::SWAMP = (new SwampBiome(BiomeID_SWAMPLAND, (new BiomeProperties(L"Swampland"))
                                                          ->depth(-0.2)
                                                          ->scale(0.1)
                                                          ->temperature(0.8)
                                                          ->downfall(0.9)
                                                          ->waterColor(0xE0FFAE)));

    Biome::SWAMP->setPreviewColor(Preview_Swampland)
        ->setNameAndDescription(StringIDs::Swampland, StringIDs::ADankWetBiomeOfVariableTemperatureWitch)
        ->setWaterSkyColor(Water_Swampland, Sky_Swampland);

    Biome::RIVER = (new RiverBiome(BiomeID_RIVER, (new BiomeProperties(L"River"))->depth(-0.5)->scale(0.0)));

    Biome::RIVER->setPreviewColor(Preview_River)
        ->setNameAndDescription(StringIDs::River, StringIDs::ARiverMadeOfWaterBlocksRiversAre)
        ->setWaterSkyColor(Water_River, Sky_River);

    Biome::NETHER = (new HellBiome(BiomeID_HELL,
                                   (new BiomeProperties(L"Hell"))->temperature(2.0)->downfall(0.0)->dry()));

    Biome::NETHER->setPreviewColor(Preview_Hell)
        ->setNameAndDescription(StringIDs::Nether, StringIDs::AHotBiomeWithNoRainAndAn)
        ->setWaterSkyColor(Water_Hell, Sky_Hell);

    Biome::THE_END = (new TheEndBiome(BiomeID_THE_END, (new BiomeProperties(L"The End"))->dry()));

    Biome::THE_END->setPreviewColor(Preview_Sky)
        ->setNameAndDescription(StringIDs::End, StringIDs::AColdDesolateBiomeWithNoRainEndermen)
        ->setWaterSkyColor(Water_Sky, Sky_Sky);

    Biome::FROZEN_OCEAN = (new OceanBiome(BiomeID_FROZEN_OCEAN, (new BiomeProperties(L"FrozenOcean"))
                                                                    ->depth(-1.0)
                                                                    ->scale(0.1)
                                                                    ->temperature(0.0)
                                                                    ->downfall(0.5)
                                                                    ->snow()));

    Biome::FROZEN_OCEAN->setPreviewColor(Preview_FrozenOcean)
        ->setNameAndDescription(StringIDs::FrozenOcean,
                                StringIDs::ATemperateBiomeWithLittleVegetationOrFeatures)
        ->setWaterSkyColor(Water_FrozenOcean, Sky_FrozenOcean);

    Biome::FROZEN_RIVER = (new RiverBiome(BiomeID_FROZEN_RIVER, (new BiomeProperties(L"FrozenRiver"))
                                                                    ->depth(-0.5)
                                                                    ->scale(0.0)
                                                                    ->temperature(0.0)
                                                                    ->downfall(0.5)
                                                                    ->snow()));

    Biome::FROZEN_RIVER->setPreviewColor(Preview_FrozenRiver)
        ->setNameAndDescription(StringIDs::FrozenRiver, StringIDs::ARiverThatOnlySpawnsInIceFlats)
        ->setWaterSkyColor(Water_FrozenRiver, Sky_FrozenRiver);

    Biome::ICE_PLAINS = (new IceBiome(BiomeID_ICE_PLAINS, IceBiome::DEFAULT,
                                      (new BiomeProperties(L"Ice Plains"))
                                          ->depth(0.125)
                                          ->scale(0.05)
                                          ->temperature(0.0)
                                          ->downfall(0.5)
                                          ->snow()));

    Biome::ICE_PLAINS->setPreviewColor(Preview_IcePlains)
        ->setNameAndDescription(StringIDs::IceFlats, StringIDs::AnIcyBiomeWithLittleVegetationItWill)
        ->setWaterSkyColor(Water_IcePlains, Sky_IcePlains);

    Biome::ICE_MOUNTAINS = (new IceBiome(BiomeID_ICE_MOUNTAINS, IceBiome::DEFAULT,
                                         (new BiomeProperties(L"Ice Mountains"))
                                             ->depth(0.45)
                                             ->scale(0.3)
                                             ->temperature(0.0)
                                             ->downfall(0.5)
                                             ->snow()));

    Biome::ICE_MOUNTAINS->setPreviewColor(Preview_IceMountains)
        ->setNameAndDescription(StringIDs::IceMountains, StringIDs::HugeMountainsCoveredInIceLittleWillGrow)
        ->setWaterSkyColor(Water_IceMountains, Sky_IceMountains);

    Biome::MUSHROOM_ISLAND = (new MushroomIslandBiome(
        BiomeID_MUSHROOM_ISLAND,
        (new BiomeProperties(L"MushroomIsland"))->depth(0.2)->scale(0.3)->temperature(0.9)->downfall(1.0)));

    Biome::MUSHROOM_ISLAND->setPreviewColor(Preview_MushroomIsland)
        ->setNameAndDescription(StringIDs::MushroomIsland,
                                StringIDs::AnEccentricBiomePopulatedWithGiantMushroomsAnd)
        ->setWaterSkyColor(Water_MushroomIsland, Sky_MushroomIsland);

    Biome::MUSHROOM_ISLAND_SHORE = (new MushroomIslandBiome(BiomeID_MUSHROOM_ISLAND_SHORE,
                                                            (new BiomeProperties(L"MushroomIslandShore"))
                                                                ->depth(0.0)
                                                                ->scale(0.025)
                                                                ->temperature(0.9)
                                                                ->downfall(1.0)));

    Biome::MUSHROOM_ISLAND_SHORE->setPreviewColor(Preview_MushroomIslandShore)
        ->setNameAndDescription(StringIDs::MushroomIsland,
                                StringIDs::AnEccentricBiomePopulatedWithGiantMushroomsAnd)
        ->setWaterSkyColor(Water_MushroomIslandShore, Sky_MushroomIslandShore);

    Biome::BEACH = (new BeachBiome(
        BiomeID_BEACH,
        (new BiomeProperties(L"Beach"))->depth(0.0)->scale(0.025)->temperature(0.8)->downfall(0.4)));

    Biome::BEACH->setPreviewColor(Preview_Beach)
        ->setNameAndDescription(0xFD173BA, StringIDs::ASandyBiomeFoundAtEdgeOfOcean)
        ->setWaterSkyColor(Water_Beach, Sky_Beach);

    Biome::DESERT_HILLS = (new DesertBiome(BiomeID_DESERT_HILLS, (new BiomeProperties(L"DesertHills"))
                                                                     ->depth(0.45)
                                                                     ->scale(0.3)
                                                                     ->temperature(2.0)
                                                                     ->downfall(0.0)
                                                                     ->dry()));

    Biome::DESERT_HILLS->setPreviewColor(Preview_DesertHills)
        ->setNameAndDescription(StringIDs::Desert, StringIDs::AHotBiomeWithNoRainfallWithLittle)
        ->setWaterSkyColor(Water_DesertHills, Sky_DesertHills);

    Biome::FOREST_HILLS = (new ForestBiome(
        BiomeID_FOREST_HILLS, ForestBiome::DEFAULT,
        (new BiomeProperties(L"ForestHills"))->depth(0.45)->scale(0.3)->temperature(0.7)->downfall(0.8)));

    Biome::FOREST_HILLS->setPreviewColor(Preview_ForestHills)
        ->setNameAndDescription(StringIDs::Forest, StringIDs::ATemperateWoodlandBiomeWithPlentifulFlowersAnd)
        ->setWaterSkyColor(Water_ForestHills, Sky_ForestHills);

    Biome::TAIGA_HILLS = (new TaigaBiome(
        BiomeID_TAIGA_HILLS, TaigaBiome::DEFAULT,
        (new BiomeProperties(L"TaigaHills"))->temperature(0.25)->downfall(0.8)->depth(0.45)->scale(0.3)));

    Biome::TAIGA_HILLS->setPreviewColor(Preview_TaigaHills)
        ->setNameAndDescription(StringIDs::Taiga, StringIDs::AConiferousWoodlandBiomeVillagesCanBeFound)
        ->setWaterSkyColor(Water_TaigaHills, Sky_TaigaHills);

    Biome::EXTREME_HILLS_EDGE = (new ExtremeHillsBiome(BiomeID_EXTREME_HILLS_EDGE, ExtremeHillsBiome::EDGE,
                                                       (new BiomeProperties(L"Extreme Hills Edge"))
                                                           ->depth(0.8)
                                                           ->scale(0.3)
                                                           ->temperature(0.2)
                                                           ->downfall(0.3)));

    Biome::EXTREME_HILLS_EDGE->setPreviewColor(Preview_ExtremeHillsEdge)
        ->setNameAndDescription(StringIDs::ExtremeHills,
                                StringIDs::AColdBiomeWithSparseVegetationLivestockWill)
        ->setWaterSkyColor(Water_ExtremeHillsEdge, Sky_ExtremeHillsEdge);

    Biome::JUNGLE = (new JungleBiome(BiomeID_JUNGLE, JungleBiome::DEFAULT,
                                     (new BiomeProperties(L"Jungle"))->temperature(0.95)->downfall(0.9)));

    Biome::JUNGLE->setPreviewColor(Preview_Jungle)
        ->setNameAndDescription(StringIDs::Jungle, StringIDs::AWarmBiomeEncrustedWithDenseTallForest)
        ->setWaterSkyColor(Water_Jungle, Sky_Jungle);

    Biome::JUNGLE_HILLS = (new JungleBiome(
        BiomeID_JUNGLE_HILLS, JungleBiome::DEFAULT,
        (new BiomeProperties(L"JungleHills"))->depth(0.45)->scale(0.3)->temperature(0.95)->downfall(0.9)));

    Biome::JUNGLE_HILLS->setPreviewColor(Preview_JungleHills)
        ->setNameAndDescription(StringIDs::Jungle, StringIDs::AWarmBiomeEncrustedWithDenseTallForest)
        ->setWaterSkyColor(Water_JungleHills, Sky_JungleHills);

    Biome::JUNGLE_EDGE
        = (new JungleBiome(BiomeID_JUNGLE_EDGE, JungleBiome::EDGE,
                           (new BiomeProperties(L"JungleEdge"))->temperature(0.95)->downfall(0.8)));

    Biome::JUNGLE_EDGE->setPreviewColor(Preview_JungleEdge)
        ->setNameAndDescription(StringIDs::Jungle, StringIDs::AWarmBiomeEncrustedWithDenseTallForest)
        ->setWaterSkyColor(Water_JungleEdge, Sky_JungleEdge);

    Biome::DEEP_OCEAN
        = (new OceanBiome(BiomeID_DEEP_OCEAN, (new BiomeProperties(L"Deep Ocean"))->depth(-1.8)->scale(0.1)));

    Biome::DEEP_OCEAN->setPreviewColor(Preview_DeepOcean)
        ->setNameAndDescription(StringIDs::Ocean, StringIDs::ATemperateBiomeWithLittleVegetationOrFeatures)
        ->setWaterSkyColor(Water_DeepOcean, Sky_DeepOcean);

    Biome::STONE_BEACH = (new StoneBeachBiome(
        BiomeID_STONE_BEACH,
        (new BiomeProperties(L"Stone Beach"))->depth(0.1)->scale(0.8)->temperature(0.2)->downfall(0.3)));

    Biome::STONE_BEACH->setPreviewColor(Preview_StoneBeach)
        ->setNameAndDescription(StringIDs::StoneBeach, StringIDs::AStoneCoveredBiomeThatLinksMountainsTo)
        ->setWaterSkyColor(Water_StoneBeach, Sky_StoneBeach);

    Biome::COLD_BEACH = (new BeachBiome(BiomeID_COLD_BEACH, (new BiomeProperties(L"Cold Beach"))
                                                                ->depth(0.0)
                                                                ->scale(0.025)
                                                                ->temperature(0.05)
                                                                ->downfall(0.3)
                                                                ->snow()));

    Biome::COLD_BEACH->setPreviewColor(Preview_ColdBeach)
        ->setNameAndDescription(StringIDs::ColdBeach, StringIDs::ABeachWithSnowyWeatherConditions)
        ->setWaterSkyColor(Water_ColdBeach, Sky_ColdBeach);

    Biome::BIRCH_FOREST
        = (new ForestBiome(BiomeID_BIRCH_FOREST, ForestBiome::BIRCH,
                           (new BiomeProperties(L"Birch Forest"))->temperature(0.6)->downfall(0.6)));

    Biome::BIRCH_FOREST->setPreviewColor(Preview_BirchForest)
        ->setNameAndDescription(StringIDs::BirchForest, StringIDs::AForestMadeEntirelyOutOfBirchTrees)
        ->setWaterSkyColor(Water_BirchForest, Sky_BirchForest);

    Biome::BIRCH_FOREST_HILLS = (new ForestBiome(BiomeID_BIRCH_FOREST_HILLS, ForestBiome::BIRCH,
                                                 (new BiomeProperties(L"Birch Forest Hills"))
                                                     ->depth(0.45)
                                                     ->scale(0.3)
                                                     ->temperature(0.6)
                                                     ->downfall(0.6)));

    Biome::BIRCH_FOREST_HILLS->setPreviewColor(Preview_BirchForestHills)
        ->setNameAndDescription(StringIDs::BirchForest, StringIDs::AForestMadeEntirelyOutOfBirchTrees)
        ->setWaterSkyColor(Water_BirchForestHills, Sky_BirchForestHills);

    Biome::ROOFED_FOREST
        = (new ForestBiome(BiomeID_ROOFED_FOREST, ForestBiome::ROOFED,
                           (new BiomeProperties(L"Roofed Forest"))->temperature(0.7)->downfall(0.8)));

    Biome::ROOFED_FOREST->setPreviewColor(Preview_RoofedForest)
        ->setNameAndDescription(StringIDs::RoofedForest, StringIDs::ATemperateBiomeCoveredInADenseForest)
        ->setWaterSkyColor(Water_RoofedForest, Sky_RoofedForest);

    Biome::COLD_TAIGA = (new TaigaBiome(BiomeID_COLD_TAIGA, TaigaBiome::DEFAULT,
                                        (new BiomeProperties(L"Cold Taiga"))
                                            ->depth(0.2)
                                            ->scale(0.2)
                                            ->temperature(-0.5)
                                            ->downfall(0.4)
                                            ->snow()));

    Biome::COLD_TAIGA->setPreviewColor(Preview_ColdTaiga)
        ->setNameAndDescription(StringIDs::ColdTaiga, StringIDs::ASnowyVariantOfTaigaBiomeWhereFerns)
        ->setWaterSkyColor(Water_ColdTaiga, Sky_ColdTaiga);

    Biome::COLD_TAIGA_HILLS = (new TaigaBiome(BiomeID_COLD_TAIGA_HILLS, TaigaBiome::DEFAULT,
                                              (new BiomeProperties(L"Cold Taiga Hills"))
                                                  ->depth(0.45)
                                                  ->scale(0.3)
                                                  ->temperature(-0.5)
                                                  ->downfall(0.4)
                                                  ->snow()));

    Biome::COLD_TAIGA_HILLS->setPreviewColor(Preview_ColdTaigaHills)
        ->setNameAndDescription(StringIDs::ColdTaiga, StringIDs::ASnowyVariantOfTaigaBiomeWhereFerns)
        ->setWaterSkyColor(Water_ColdTaigaHills, Sky_ColdTaigaHills);

    Biome::MEGA_TAIGA = (new TaigaBiome(
        BiomeID_MEGA_TAIGA, TaigaBiome::MEGA,
        (new BiomeProperties(L"Mega Taiga"))->temperature(0.3)->downfall(0.8)->depth(0.2)->scale(0.2)));

    Biome::MEGA_TAIGA->setPreviewColor(Preview_MegaTaiga)
        ->setNameAndDescription(StringIDs::RedwoodTaiga, StringIDs::AColdBiomeSimilarToRegularBiomeBut)
        ->setWaterSkyColor(Water_MegaTaiga, Sky_MegaTaiga);

    Biome::MEGA_TAIGA_HILLS = (new TaigaBiome(BiomeID_MEGA_TAIGA_HILLS, TaigaBiome::MEGA,
                                              (new BiomeProperties(L"Mega Taiga Hills"))
                                                  ->depth(0.45)
                                                  ->scale(0.3)
                                                  ->temperature(0.3)
                                                  ->downfall(0.8)));

    Biome::MEGA_TAIGA_HILLS->setPreviewColor(Preview_MegaTaigaHills)
        ->setNameAndDescription(StringIDs::RedwoodTaiga, StringIDs::AColdBiomeSimilarToRegularBiomeBut)
        ->setWaterSkyColor(Water_MegaTaigaHills, Sky_MegaTaigaHills);

    // but this isn't edge? My enum value names must be wrong...
    Biome::EXTREME_HILLS_PLUS = (new ExtremeHillsBiome(
        BiomeID_EXTREME_HILLS_PLUS, ExtremeHillsBiome::EDGE,
        (new BiomeProperties(L"Extreme Hills+"))->depth(1.0)->scale(0.5)->temperature(0.2)->downfall(0.3)));

    Biome::EXTREME_HILLS_PLUS->setPreviewColor(Preview_ExtremeHillsPlus)
        ->setNameAndDescription(StringIDs::ExtremeHills,
                                StringIDs::AColdBiomeWithSparseVegetationLivestockWill)
        ->setWaterSkyColor(Water_ExtremeHillsPlus, Sky_ExtremeHillsPlus);

    Biome::SAVANNA = (new SavannaBiome(BiomeID_SAVANNA, (new BiomeProperties(L"Savanna"))
                                                            ->depth(0.125)
                                                            ->scale(0.05)
                                                            ->temperature(1.2)
                                                            ->downfall(0.0)
                                                            ->dry()));
    Biome::SAVANNA->setPreviewColor(Preview_Savanna)
        ->setNameAndDescription(StringIDs::Savanna, StringIDs::AWarmDryBiomeWithNoRainVillages)
        ->setWaterSkyColor(Water_Savanna, Sky_Savanna);

    Biome::SAVANNA_PLATEAU
        = (new SavannaBiome(BiomeID_SAVANNA_PLATEAU, (new BiomeProperties(L"Savanna Plateau"))
                                                         ->depth(1.5)
                                                         ->scale(0.025)
                                                         ->temperature(1.0)
                                                         ->downfall(0.0)
                                                         ->dry()));
    Biome::SAVANNA_PLATEAU->setPreviewColor(Preview_SavannaPlateau)
        ->setNameAndDescription(StringIDs::Savanna, StringIDs::AWarmDryBiomeWithNoRainVillages)
        ->setWaterSkyColor(Water_SavannaPlateau, Sky_SavannaPlateau);

    Biome::MESA = (new MesaBiome(BiomeID_MESA, false, false,
                                 (new BiomeProperties(L"Mesa"))->temperature(2.0)->downfall(0.0)->dry()));
    Biome::MESA->setPreviewColor(Preview_Mesa)
        ->setNameAndDescription(StringIDs::Mesa, StringIDs::AHotAridBiome)
        ->setWaterSkyColor(Water_Mesa, Sky_Mesa);

    Biome::MESA_PLATEAU_F = (new MesaBiome(BiomeID_MESA_PLATEAU_F, false, true,
                                           (new BiomeProperties(L"Mesa Plateau F"))
                                               ->depth(1.5)
                                               ->scale(0.025)
                                               ->temperature(2.0)
                                               ->downfall(0.0)
                                               ->dry()));
    Biome::MESA_PLATEAU_F->setPreviewColor(Preview_MesaPlateauF)
        ->setNameAndDescription(StringIDs::Mesa, StringIDs::AHotAridBiome)
        ->setWaterSkyColor(Water_MesaPlateauF, Sky_MesaPlateauF);

    Biome::MESA_PLATEAU = (new MesaBiome(BiomeID_MESA_PLATEAU, false, false,
                                         (new BiomeProperties(L"Mesa Plateau"))
                                             ->depth(1.5)
                                             ->scale(0.025)
                                             ->temperature(2.0)
                                             ->downfall(0.0)
                                             ->dry()));

    Biome::MESA_PLATEAU->setPreviewColor(Preview_MesaPlateau)
        ->setNameAndDescription(StringIDs::Mesa, StringIDs::AHotAridBiome)
        ->setWaterSkyColor(Water_MesaPlateau, Sky_MesaPlateau);

    Biome::THE_VOID = (new VoidBiome(BiomeID_THE_VOID, (new BiomeProperties(L"The Void"))->dry()));

    Biome::SUNFLOWER_PLAINS = (new PlainsBiome(BiomeID_SUNFLOWER_PLAINS, false,
                                               (new BiomeProperties(L"Sunflower Plains"))
                                                   ->mutated(L"plains")
                                                   ->depth(0.125)
                                                   ->scale(0.05)
                                                   ->temperature(0.8)
                                                   ->downfall(0.4)));

    Biome::SUNFLOWER_PLAINS->setPreviewColor(Preview_Plains_Mutated)
        ->setNameAndDescription(StringIDs::Plains, StringIDs::ATemperateGrassLandBiomeWithFewTrees)
        ->setWaterSkyColor(Water_Plains, Sky_Plains);

    Biome::DESERT_M = (new DesertBiome(BiomeID_DESERT_M, (new BiomeProperties(L"Desert M"))
                                                             ->mutated(L"desert")
                                                             ->depth(0.225)
                                                             ->scale(0.25)
                                                             ->temperature(2.0)
                                                             ->downfall(0.0)
                                                             ->dry()));

    Biome::DESERT_M->setPreviewColor(Preview_Desert_Mutated)
        ->setNameAndDescription(StringIDs::Desert, StringIDs::AHotBiomeWithNoRainfallWithLittle)
        ->setWaterSkyColor(Water_Desert, Sky_Desert);

    Biome::EXTREME_HILLS_M = (new ExtremeHillsBiome(BiomeID_EXTREME_HILLS_M, ExtremeHillsBiome::M,
                                                    (new BiomeProperties(L"Extreme Hills M"))
                                                        ->mutated(L"extreme_hills")
                                                        ->depth(1.0)
                                                        ->scale(0.5)
                                                        ->temperature(0.2)
                                                        ->downfall(0.3)));
    Biome::EXTREME_HILLS_M->setPreviewColor(Preview_ExtremeHills_Mutated)
        ->setNameAndDescription(StringIDs::ExtremeHills,
                                StringIDs::AColdBiomeWithSparseVegetationLivestockWill)
        ->setWaterSkyColor(Water_ExtremeHills, Sky_ExtremeHills);

    Biome::FLOWER_FOREST = (new ForestBiome(BiomeID_FLOWER_FOREST, ForestBiome::FLOWER,
                                            (new BiomeProperties(L"Flower Forest"))
                                                ->mutated(L"forest")
                                                ->scale(0.4)
                                                ->temperature(0.7)
                                                ->downfall(0.8)));

    Biome::FLOWER_FOREST->setPreviewColor(Preview_Forest_Mutated)
        ->setNameAndDescription(StringIDs::Forest, StringIDs::ATemperateWoodlandBiomeWithPlentifulFlowersAnd)
        ->setWaterSkyColor(Water_Forest, Sky_Forest);

    Biome::TAIGA_M = (new TaigaBiome(BiomeID_TAIGA_M, TaigaBiome::DEFAULT,
                                     (new BiomeProperties(L"Taiga M"))
                                         ->mutated(L"taiga")
                                         ->depth(0.3)
                                         ->scale(0.4)
                                         ->temperature(0.25)
                                         ->downfall(0.8)));

    Biome::TAIGA_M->setPreviewColor(Preview_Taiga_Mutated)
        ->setNameAndDescription(StringIDs::Taiga, StringIDs::AConiferousWoodlandBiomeVillagesCanBeFound)
        ->setWaterSkyColor(Water_Taiga, Sky_Taiga);

    Biome::SWAMP_M = (new SwampBiome(BiomeID_SWAMPLAND_M, (new BiomeProperties(L"Swampland M"))
                                                              ->mutated(L"swampland")
                                                              ->depth(-0.1)
                                                              ->scale(0.3)
                                                              ->temperature(0.8)
                                                              ->downfall(0.9)
                                                              ->waterColor(14745518)));

    Biome::SWAMP_M->setPreviewColor(Preview_Swampland_Mutated)
        ->setNameAndDescription(StringIDs::Swampland, StringIDs::ADankWetBiomeOfVariableTemperatureWitch)
        ->setWaterSkyColor(Water_Swampland, Sky_Swampland);

    Biome::ICE_PLAINS_SPIKES = (new IceBiome(BiomeID_ICE_PLAINS_SPIKES, IceBiome::SPIKES,
                                             (new BiomeProperties(L"Ice Plains Spikes"))
                                                 ->mutated(L"ice_flats")
                                                 ->depth(0.425)
                                                 ->scale(0.45)
                                                 ->temperature(0.0)
                                                 ->downfall(0.5)
                                                 ->snow()));

    Biome::ICE_PLAINS_SPIKES->setPreviewColor(Preview_IcePlains_Mutated)
        ->setNameAndDescription(StringIDs::IceFlats, StringIDs::AnIcyBiomeWithLittleVegetationItWill)
        ->setWaterSkyColor(Water_IcePlains, Sky_IcePlains);

    Biome::JUNGLE_M = (new JungleBiome(BiomeID_JUNGLE_M, JungleBiome::DEFAULT,
                                       (new BiomeProperties(L"Jungle M"))
                                           ->mutated(L"jungle")
                                           ->depth(0.2)
                                           ->scale(0.4)
                                           ->temperature(0.95)
                                           ->downfall(0.9)));

    Biome::JUNGLE_M->setPreviewColor(Preview_Jungle_Mutated)
        ->setNameAndDescription(StringIDs::Jungle, StringIDs::AWarmBiomeEncrustedWithDenseTallForest)
        ->setWaterSkyColor(Water_Jungle, Sky_Jungle);

    Biome::JUNGLE_EDGE_M = (new JungleBiome(BiomeID_JUNGLE_EDGE, JungleBiome::EDGE,
                                            (new BiomeProperties(L"JungleEdge M"))
                                                ->mutated(L"jungle_edge")
                                                ->depth(0.2)
                                                ->scale(0.4)
                                                ->temperature(0.95)
                                                ->downfall(0.8)));

    Biome::JUNGLE_EDGE_M->setPreviewColor(Preview_JungleEdge_Mutated)
        ->setNameAndDescription(StringIDs::Jungle, StringIDs::AWarmBiomeEncrustedWithDenseTallForest)
        ->setWaterSkyColor(Water_JungleEdge, Sky_JungleEdge);

    Biome::BIRCH_FOREST_M
        = (new MutatedForestBiome(BiomeID_BIRCH_FOREST_M, (new BiomeProperties(L"Birch Forest M"))
                                                              ->mutated(L"birch_forest")
                                                              ->depth(0.2)
                                                              ->scale(0.4)
                                                              ->temperature(0.6)
                                                              ->downfall(0.6)));

    Biome::BIRCH_FOREST_M->setPreviewColor(Preview_BirchForest_Mutated)
        ->setNameAndDescription(StringIDs::BirchForest, StringIDs::AForestMadeEntirelyOutOfBirchTrees)
        ->setWaterSkyColor(Water_BirchForest, Sky_BirchForest);

    Biome::BIRCH_FOREST_HILLS_M
        = (new MutatedForestBiome(BiomeID_BIRCH_FOREST_HILLS_M, (new BiomeProperties(L"Birch Forest Hills M"))
                                                                    ->mutated(L"birch_forest_hills")
                                                                    ->depth(0.55)
                                                                    ->scale(0.5)
                                                                    ->temperature(0.6)
                                                                    ->downfall(0.6)));

    Biome::BIRCH_FOREST_HILLS_M->setPreviewColor(Preview_BirchForestHills_Mutated)
        ->setNameAndDescription(StringIDs::BirchForest, StringIDs::AForestMadeEntirelyOutOfBirchTrees)
        ->setWaterSkyColor(Water_BirchForestHills, Sky_BirchForestHills);

    Biome::ROOFED_FOREST_M = (new ForestBiome(BiomeID_ROOFED_FOREST_M, ForestBiome::ROOFED,
                                              (new BiomeProperties(L"Roofed Forest M"))
                                                  ->mutated(L"roofed_forest")
                                                  ->depth(0.2)
                                                  ->scale(0.4)
                                                  ->temperature(0.7)
                                                  ->downfall(0.8)));

    Biome::ROOFED_FOREST_M->setPreviewColor(Preview_RoofedForest_Mutated)
        ->setNameAndDescription(StringIDs::RoofedForest, StringIDs::ATemperateBiomeCoveredInADenseForest)
        ->setWaterSkyColor(Water_RoofedForest, Sky_RoofedForest);

    Biome::COLD_TAIGA_M = (new TaigaBiome(BiomeID_COLD_TAIGA_M, TaigaBiome::DEFAULT,
                                          (new BiomeProperties(L"Cold Taiga M"))
                                              ->mutated(L"taiga_cold")
                                              ->depth(0.3)
                                              ->scale(0.4)
                                              ->temperature(-0.5)
                                              ->downfall(0.4)
                                              ->snow()));

    Biome::COLD_TAIGA_M->setPreviewColor(Preview_ColdTaiga_Mutated)
        ->setNameAndDescription(StringIDs::ColdTaiga, StringIDs::ASnowyVariantOfTaigaBiomeWhereFerns)
        ->setWaterSkyColor(Water_ColdTaiga, Sky_ColdTaiga);

    Biome::MEGA_SPRUCE_TAIGA = (new TaigaBiome(BiomeID_MEGA_SPRUCE_TAIGA, TaigaBiome::MEGA_SPRUCE,
                                               (new BiomeProperties(L"Mega Spruce Taiga"))
                                                   ->mutated(L"redwood_taiga")
                                                   ->depth(0.2)
                                                   ->scale(0.2)
                                                   ->temperature(0.25)
                                                   ->downfall(0.8)));
    Biome::MEGA_SPRUCE_TAIGA->setPreviewColor(Preview_MegaTaiga_Mutated)
        ->setNameAndDescription(StringIDs::RedwoodTaiga, StringIDs::AColdBiomeSimilarToRegularBiomeBut)
        ->setWaterSkyColor(Water_MegaTaiga, Sky_MegaTaiga);

    Biome::REDWOOD_TAIGA_HILLS_M = (new TaigaBiome(BiomeID_REDWOOD_TAIGA_HILLS_M, TaigaBiome::MEGA_SPRUCE,
                                                   (new BiomeProperties(L"Redwood Taiga Hills M"))
                                                       ->mutated(L"redwood_taiga_hills")
                                                       ->depth(0.2)
                                                       ->scale(0.2)
                                                       ->temperature(0.25)
                                                       ->downfall(0.8)));
    Biome::REDWOOD_TAIGA_HILLS_M->setPreviewColor(Preview_MegaTaigaHills_Mutated)
        ->setNameAndDescription(StringIDs::RedwoodTaiga, StringIDs::AColdBiomeSimilarToRegularBiomeBut)
        ->setWaterSkyColor(Water_MegaTaigaHills, Sky_MegaTaigaHills);

    Biome::EXTREME_HILLS_PLUS_M = (new ExtremeHillsBiome(BiomeID_EXTREME_HILLS_PLUS_M, ExtremeHillsBiome::M,
                                                         (new BiomeProperties(L"Extreme Hills+ M"))
                                                             ->mutated(L"extreme_hills_with_trees")
                                                             ->depth(1.0)
                                                             ->scale(0.5)
                                                             ->temperature(0.2)
                                                             ->downfall(0.3)));

    Biome::EXTREME_HILLS_PLUS_M->setPreviewColor(Preview_ExtremeHillsPlus_Mutated)
        ->setNameAndDescription(StringIDs::ExtremeHills,
                                StringIDs::AColdBiomeWithSparseVegetationLivestockWill)
        ->setWaterSkyColor(Water_ExtremeHillsPlus, Sky_ExtremeHillsPlus);

    Biome::SAVANNA_M = (new MutatedSavannaBiome(BiomeID_SAVANNA_M, (new BiomeProperties(L"Savanna M"))
                                                                       ->mutated(L"savanna")
                                                                       ->depth(0.3625)
                                                                       ->scale(1.225)
                                                                       ->temperature(1.1)
                                                                       ->downfall(0.0)
                                                                       ->dry()));
    Biome::SAVANNA_M->setPreviewColor(Preview_Savanna_Mutated)
        ->setNameAndDescription(StringIDs::Savanna, StringIDs::AWarmDryBiomeWithNoRainVillages)
        ->setWaterSkyColor(Water_Savanna, Sky_Savanna);

    Biome::SAVANNA_PLATEAU_M
        = (new MutatedSavannaBiome(BiomeID_SAVANNA_PLATEAU_M, (new BiomeProperties(L"Savanna Plateau M"))
                                                                  ->mutated(L"savanna_rock")
                                                                  ->depth(1.05)
                                                                  ->scale(1.2125)
                                                                  ->temperature(1.0)
                                                                  ->downfall(0.0)
                                                                  ->dry()));
    Biome::SAVANNA_PLATEAU_M->setPreviewColor(Preview_SavannaPlateau_Mutated)
        ->setNameAndDescription(StringIDs::Savanna, StringIDs::AWarmDryBiomeWithNoRainVillages)
        ->setWaterSkyColor(Water_SavannaPlateau, Sky_SavannaPlateau);

    Biome::MESA_BRYCE = (new MesaBiome(
        BiomeID_MESA_BRYCE, true, false,
        (new BiomeProperties(L"Mesa (Bryce)"))->mutated(L"mesa")->temperature(2.0)->downfall(0.0)->dry()));
    Biome::MESA_BRYCE->setPreviewColor(Preview_Mesa_Mutated)
        ->setNameAndDescription(StringIDs::Mesa, StringIDs::AHotAridBiome)
        ->setWaterSkyColor(Water_Mesa, Sky_Mesa);

    Biome::MESA_PLATEAU_F_M = (new MesaBiome(BiomeID_MESA_PLATEAU_F_M, 0, 1,
                                             (new BiomeProperties(L"Mesa Plateau F M"))
                                                 ->mutated(L"mesa_rock")
                                                 ->depth(0.45)
                                                 ->scale(0.3)
                                                 ->temperature(2.0)
                                                 ->downfall(0.0)
                                                 ->dry()));
    Biome::MESA_PLATEAU_F_M->setPreviewColor(Preview_MesaPlateauF_Mutated)
        ->setNameAndDescription(StringIDs::Mesa, StringIDs::AHotAridBiome)
        ->setWaterSkyColor(Water_MesaPlateauF, Sky_MesaPlateauF);

    Biome::MESA_PLATEAU_M = (new MesaBiome(BiomeID_MESA_PLATEAU_M, false, false,
                                           (new BiomeProperties(L"Mesa Plateau M"))
                                               ->mutated(L"mesa_clear_rock")
                                               ->depth(0.45)
                                               ->scale(0.3)
                                               ->temperature(2.0)
                                               ->downfall(0.0)
                                               ->dry()));
    Biome::MESA_PLATEAU_M->setPreviewColor(Preview_MesaPlateau_Mutated)
        ->setNameAndDescription(StringIDs::Mesa, StringIDs::AHotAridBiome)
        ->setWaterSkyColor(Water_MesaPlateau, Sky_MesaPlateau);

    Biome::DEFAULT = Biome::OCEAN;
}
