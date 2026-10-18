#include "net/minecraft/world/level/biome/Biome.h"

#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/world/entity/MobCategory.h"
#include "net/minecraft/world/level/biome/BiomeDecorator.h"

Biome::~Biome() {
    delete m_biomeDecorator;
}

Biome* Biome::setPreviewColor(eMinecraftColour color) {
    m_previewColor = color;
    return this;
}

Biome* Biome::setWaterSkyColor(eMinecraftColour water, eMinecraftColour sky) {
    m_waterColor = water;
    m_skyColor = sky;
    return this;
}

std::wstring Biome::getName(bool) {
    if (m_nameId == -1)
        return L"";
    return L10N::GetString(m_nameId);
}

std::wstring Biome::getDescription() {
    std::wstring description = L"";
    if (m_descriptionId != -1)
        description = L10N::GetString(m_descriptionId);
    return description;
}

std::vector<Biome::MobSpawnerData*>* Biome::getMobs(MobCategory* category) {
    if (category == MobCategory::MONSTER)
        return &m_hostileMobs;
    if (category == MobCategory::CREATURE)
        return &m_passiveMobs;
    if (category == MobCategory::WATER_CREATURE)
        return &m_aquaticMobs;
    if (category == MobCategory::CHICKEN)
        return &m_chickens;
    if (category == MobCategory::WOLF)
        return &m_fieldD8;
    if (category == MobCategory::MUSHROOM_COW)
        return &m_fieldF0;
    if (category == MobCategory::SLIME)
        return &m_neutralMobs;
    if (category == MobCategory::AMBIENT)
        return &m_ambientMobs;
    return nullptr;
}

float Biome::getDownfall() {
    return m_downfall;
}
float Biome::getTemperature() {
    return m_temperature;
}
float Biome::getDepth() {
    return m_depth;
}
float Biome::getScale() {
    return m_scale;
}
