#include "Minecraft.World/level/material/DecorationMaterial.h"
#include "Minecraft.World/level/material/GasMaterial.h"
#include "Minecraft.World/level/material/LiquidMaterial.h"
#include "Minecraft.World/level/material/PortalMaterial.h"
#include "Minecraft.World/level/material/WebMaterial.h"

__attribute__((noinline)) Material::Material(MaterialColor const* color) : mColor(color) {
    mIsFlammable = false;
    mIsReplaceable = false;
    mIsNeverBuildable = false;
    mIsAlwaysDestroyable = true;
    mPushReaction = NORMAL;
    mIsDestroyedByHand = false;
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
    MOSS = (DecorationMaterial*)(new DecorationMaterial(MaterialColor::PLANT))->flammable()->destroyOnPush()->replaceable();
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
    TOP_SNOW = (DecorationMaterial*)(new DecorationMaterial(MaterialColor::SNOW))->replaceable()->neverBuildable()->notAlwaysDestroyable()->destroyOnPush();
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

__attribute__((noinline)) Material* Material::neverBuildable() {
    mIsNeverBuildable = true;
    return this;
}

__attribute__((noinline)) Material* Material::notAlwaysDestroyable() {
    mIsAlwaysDestroyable = false;
    return this;
}

__attribute__((noinline)) Material* Material::flammable() {
    mIsFlammable = true;
    return this;
}

bool Material::isFlammable() {
    return mIsFlammable;
}

__attribute__((noinline)) Material* Material::replaceable() {
    mIsReplaceable = true;
    return this;
}

bool Material::isReplaceable() {
    return mIsReplaceable;
}

bool Material::isSolidBlocking() {
    if (mIsNeverBuildable)
        return false;
    return blocksMotion();
}

bool Material::isAlwaysDestroyable() {
    return mIsAlwaysDestroyable;
}

PushReaction Material::getPushReaction() {
    return mPushReaction;
}

bool Material::isDestroyedByHand() {
    return mIsDestroyedByHand;
}

__attribute__((noinline)) Material* Material::notPushable() {
    mPushReaction = BLOCK;
    return this;
}

__attribute__((noinline)) Material* Material::destroyOnPush() {
    mPushReaction = DESTROY;
    return this;
}

__attribute__((noinline)) Material* Material::makeDestroyedByHand() {
    mIsDestroyedByHand = true;
    return this;
}

MaterialColor const* Material::getColor() const {
    return mColor;
}