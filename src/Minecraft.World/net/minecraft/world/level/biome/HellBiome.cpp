#include "net/minecraft/world/level/biome/HellBiome.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"

class HellBiomeDecorator : public BiomeDecorator {
public:
    HellBiomeDecorator() = default;
    ~HellBiomeDecorator() override = default;
    void decorate(Level*, Random&, Biome*, const BlockPos&) override;
};

void HellBiomeDecorator::decorate(Level*, Random&, Biome*, const BlockPos&) {}

HellBiome::HellBiome(EBiomeIDs id, BiomeProperties* properties) : Biome(id, properties) {
    m_hostileMobs.clear();
    m_passiveMobs.clear();
    m_chickens.clear();
    m_fieldD8.clear();
    m_aquaticMobs.clear();
    m_ambientMobs.clear();
    m_hostileMobs.push_back(new MobSpawnerData(eGhast, 100, 4, 4));
    m_hostileMobs.push_back(new MobSpawnerData(ePigZombie, 200, 4, 4));
    m_hostileMobs.push_back(new MobSpawnerData(eMagmaCube, 2, 4, 4));
    m_hostileMobs.push_back(new MobSpawnerData(eEnderMan, 1, 4, 4));
    m_hostileMobs.push_back(new MobSpawnerData(eWitherSkeleton, 1, 4, 4));
    delete m_biomeDecorator;
    m_biomeDecorator = new HellBiomeDecorator();
}

int HellBiome::getBaseClass() {
    return _HELL;
}
unsigned int HellBiome::getSkyColor(float) {
    return 0;
}
bool HellBiome::isFoggy() {
    return true;
}
bool HellBiome::isNatural() {
    return false;
}

Vec3* HellBiome::getFogColor(float, float) const {
    unsigned int color = Minecraft::GetInstance()->getColourTable()->getColour(Nether_Fog_Colour);
    unsigned int red = color >> 16 & 255;
    unsigned int green = color >> 8 & 255;
    unsigned int blue = color & 255;
    float r = red / 256.0f;
    float g = green / 256.0f;
    float b = blue / 256.0f;
    return Vec3::newTemp(r, g, b);
}
