#include "net/minecraft/world/level/material/Material.h"

Material::Material(const MaterialColor* color) : m_color(color) {
    m_isFlammable = false;
    m_isReplaceable = false;
    m_isNeverBuildable = false;
    m_isAlwaysDestroyable = true;
    m_pushReaction = NORMAL;
    m_isDestroyedByHand = false;
}

void Material::staticCtor() {
    AIR = new GasMaterial(MaterialColor::NONE);
    GRASS = new Material(MaterialColor::GRASS);
    DIRT = new Material(MaterialColor::DIRT);
    WOOD = (new Material(MaterialColor::WOOD))->flammable();
    STONE = (new Material(MaterialColor::STONE))->notAlwaysDestroyable();
    METAL = (new Material(MaterialColor::METAL))->notAlwaysDestroyable();
    HEAVY_METAL = (new Material(MaterialColor::METAL))->notAlwaysDestroyable()->notPushable();
    WATER = (LiquidMaterial*)(new LiquidMaterial(MaterialColor::WATER))->destroyOnPush();
    LAVA = (LiquidMaterial*)(new LiquidMaterial(MaterialColor::FIRE))->destroyOnPush();
    LEAVES = (new Material(MaterialColor::PLANT))->flammable()->neverBuildable()->destroyOnPush();
    PLANTS = (DecorationMaterial*)(new DecorationMaterial(MaterialColor::PLANT))->destroyOnPush();
    MOSS = (DecorationMaterial*)(new DecorationMaterial(MaterialColor::PLANT))
               ->flammable()
               ->destroyOnPush()
               ->replaceable();
    SPONGE = new Material(MaterialColor::WOOL);
    WOOL = (new Material(MaterialColor::WOOL))->flammable();
    FIRE = (GasMaterial*)(new GasMaterial(MaterialColor::NONE))->destroyOnPush();
    SAND = new Material(MaterialColor::SAND);
    CIRCUITS = (DecorationMaterial*)(new DecorationMaterial(MaterialColor::NONE))->destroyOnPush();
    CLOTH_DECORATION = (DecorationMaterial*)(new DecorationMaterial(MaterialColor::WOOL))->flammable();
    GLASS = (new Material(MaterialColor::NONE))->neverBuildable()->makeDestroyedByHand();
    REDSTONE_LIGHT = (new Material(MaterialColor::NONE))->makeDestroyedByHand();
    EXPLOSIVE = (new Material(MaterialColor::FIRE))->flammable()->neverBuildable();
    CORAL = (new Material(MaterialColor::PLANT))->destroyOnPush();
    ICE = (new Material(MaterialColor::ICE))->neverBuildable()->makeDestroyedByHand();
    ICE_SOLID = (new Material(MaterialColor::ICE))->makeDestroyedByHand();
    TOP_SNOW = (DecorationMaterial*)(new DecorationMaterial(MaterialColor::SNOW))
                   ->replaceable()
                   ->neverBuildable()
                   ->notAlwaysDestroyable()
                   ->destroyOnPush();
    SNOW = (new Material(MaterialColor::SNOW))->notAlwaysDestroyable();
    CACTUS = (new Material(MaterialColor::PLANT))->neverBuildable()->destroyOnPush();
    CLAY = new Material(MaterialColor::CLAY);
    VEGETABLE = (new Material(MaterialColor::PLANT))->destroyOnPush();
    EGG = (new Material(MaterialColor::PLANT))->destroyOnPush();
    PORTAL = (PortalMaterial*)(new PortalMaterial(MaterialColor::NONE))->notPushable();
    CAKE = (new Material(MaterialColor::NONE))->destroyOnPush();
    CLOTH = (WebMaterial*)(new WebMaterial(MaterialColor::WOOL))->notAlwaysDestroyable()->destroyOnPush();
    PISTON = (new Material(MaterialColor::STONE))->notPushable();
    BARRIER = (new Material(MaterialColor::NONE))->notAlwaysDestroyable()->notPushable();
    STRUCTURAL_AIR = new GasMaterial(MaterialColor::NONE);
}

bool Material::isLiquid() {
    return false;
}

bool Material::letsWaterThrough() {
    if (isLiquid())
        return false;
    return isSolid() ^ 1;
}

bool Material::isSolid() {
    return true;
}

bool Material::blocksLight() {
    return true;
}

bool Material::blocksMotion() {
    return true;
}

Material* Material::neverBuildable() {
    m_isNeverBuildable = true;
    return this;
}

Material* Material::notAlwaysDestroyable() {
    m_isAlwaysDestroyable = false;
    return this;
}

Material* Material::flammable() {
    m_isFlammable = true;
    return this;
}

bool Material::isFlammable() {
    return m_isFlammable;
}

Material* Material::replaceable() {
    m_isReplaceable = true;
    return this;
}

bool Material::isReplaceable() {
    return m_isReplaceable;
}

bool Material::isSolidBlocking() {
    if (m_isNeverBuildable)
        return false;
    return blocksMotion();
}

bool Material::isAlwaysDestroyable() {
    return m_isAlwaysDestroyable;
}

PushReaction Material::getPushReaction() {
    return m_pushReaction;
}

bool Material::isDestroyedByHand() {
    return m_isDestroyedByHand;
}

Material* Material::notPushable() {
    m_pushReaction = BLOCK;
    return this;
}

Material* Material::destroyOnPush() {
    m_pushReaction = DESTROY;
    return this;
}

Material* Material::makeDestroyedByHand() {
    m_isDestroyedByHand = true;
    return this;
}

const MaterialColor* Material::getColor() const {
    return m_color;
}
