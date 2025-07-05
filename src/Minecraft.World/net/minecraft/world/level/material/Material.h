#pragma once

#include "net/minecraft/world/level/material/MaterialColor.h"
#include "net/minecraft/world/level/material/PushReaction.h"

class DecorationMaterial;
class GasMaterial;
class LiquidMaterial;
class PortalMaterial;
class WebMaterial;

// Materials in this version are a 1:1 match to Java Edition 1.12's order, but I've chosen to use
// official names from 1.14.4+. Materials in that version are sorted pretty differently so some
// these names have a couple guessed names.
class Material {
public:
    void staticCtor();
    static GasMaterial* AIR;
    static Material* GRASS;
    static Material* DIRT;
    static Material* WOOD;
    static Material* STONE;
    static Material* METAL;
    static Material* HEAVY_METAL;
    static LiquidMaterial* WATER;
    static LiquidMaterial* LAVA;
    static Material* LEAVES;
    static DecorationMaterial* PLANTS;
    static DecorationMaterial* MOSS;
    static Material* SPONGE;
    static Material* WOOL;
    static GasMaterial* FIRE;
    static Material* SAND;
    static DecorationMaterial* CIRCUITS;  // Guessed name
    static DecorationMaterial* CLOTH_DECORATION;
    static Material* GLASS;
    static Material* REDSTONE_LIGHT;  // Guessed name
    static Material* EXPLOSIVE;
    static Material* CORAL;  // Guessed name
    static Material* ICE;
    static Material* ICE_SOLID;
    static DecorationMaterial* TOP_SNOW;
    static Material* SNOW;
    static Material* CACTUS;
    static Material* CLAY;
    static Material* VEGETABLE;
    static Material* EGG;
    static PortalMaterial* PORTAL;
    static Material* CAKE;
    static WebMaterial* CLOTH;
    static Material* PISTON;
    static Material* BARRIER;
    static GasMaterial* STRUCTURAL_AIR;

    Material(const MaterialColor* color);
    virtual ~Material();
    virtual bool isLiquid();
    virtual bool letsWaterThrough();
    virtual bool isSolid();
    virtual bool blocksLight();
    virtual bool blocksMotion();
    virtual Material* neverBuildable();
    virtual Material* notAlwaysDestroyable();
    virtual Material* flammable();
    virtual bool isFlammable();
    virtual Material* replaceable();
    virtual bool isReplaceable();
    virtual bool isSolidBlocking();
    virtual bool isAlwaysDestroyable();
    virtual PushReaction getPushReaction();
    bool isDestroyedByHand();
    Material* notPushable();
    Material* destroyOnPush();
    Material* makeDestroyedByHand();
    const MaterialColor* getColor() const;

    bool mIsFlammable;
    bool mIsReplaceable;
    bool mIsNeverBuildable;
    const MaterialColor* mColor;
    bool mIsAlwaysDestroyable;
    PushReaction mPushReaction;
    bool mIsDestroyedByHand;
};

// To avoid clangd warning about unused includes in other files, we include them here.
#include "net/minecraft/world/level/material/DecorationMaterial.h"
#include "net/minecraft/world/level/material/GasMaterial.h"
#include "net/minecraft/world/level/material/LiquidMaterial.h"
#include "net/minecraft/world/level/material/PortalMaterial.h"
#include "net/minecraft/world/level/material/WebMaterial.h"
