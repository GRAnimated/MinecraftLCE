#pragma once

#include "net/minecraft/client/particle/TextureUVCoordinateSet.h"
#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/client/renderer/vertex/BufferBuilder.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/LevelListener.h"
#include <memory>

class Particle {
public:
    virtual ePARTICLE_TYPE getType() = 0;
    virtual ~Particle();
    virtual Particle* setPower(float);
    virtual Particle* scale(float);
    virtual void tick();
    virtual void render(BufferBuilder*, std::shared_ptr<Entity>&, float, float, float, float, float, float);
    virtual int getParticleTexture();
    virtual void setSprite(TextureAtlasSprite*);
    virtual void setMiscTex(int);
    virtual std::wstring toString() const;
    virtual bool isSemiTransparent();
    virtual bool isTransparent();
    virtual void setPos(double, double, double);
    virtual void move(double, double, double);
    virtual int getLightColor();
    virtual float getBrightness();
    virtual void setSize(float, float);
    virtual void setLocationFromBoundingbox();

    static void setCamerViewDirection(Vec3*);
    static void setXOffset(double);
    static void setYOffset(double);
    static void setZOffset(double);

    Particle(Level*, double, double, double, double, double, double);
    Particle(Level*, double, double, double);

    void _init(Level*, double, double, double);
    AABB* getBoundingBox();
    void setBoundingBox(const AABB*);
    bool isAlive();
    void remove();
    float getAlpha();
    Level* getLevel();

    void* field_0x8;
    void* field_0x10;
    Level* mLevel;
    double mPrevPosX;
    double mPrevPosY;
    double mPrevPosZ;
    double mPosX;
    double mPosY;
    double mPosZ;
    double mVelX;
    double mVelY;
    double mVelZ;
    bool mIsOnGround;
    bool mCanCollide;
    bool mIsRemoved;
    bool field_0x6b;
    float mWidth;
    float mHeight;
    int field_0x74;
    Random mRandom;
    int field_0x90;
    int field_0x94;
    TextureUVCoordinateSet mUVSet;
    float mTexJitterX;
    float mTexJitterY;
    float field_0x108;
    float field_0x10c;
    float field_0x110;
    float mAlpha;
    int mAge;
    int mMaxAge;
    float mScale;
    float mGravityScale;
    TextureAtlasSprite* mSpriteAtlas;
    void* field_0x130;
    AABB* mBoundingBox;

    static double X_OFFSET;
    static double Y_OFFSET;
    static double Z_OFFSET;
    static Vec3* VIEW_DIRECTION;  // mhh idk maybe this should be in ParticleEngine, tho the setter is here
};

// ASSERT_SIZEOF(Particle, 0x98)

static_assert(offsetof(Particle, mRandom) == 0x78);
static_assert(offsetof(Particle, mUVSet) == 0x98);
static_assert(offsetof(Particle, mBoundingBox) == 0x138);
static_assert(offsetof(Particle, mCanCollide) == 0x69);
static_assert(offsetof(Particle, mWidth) == 0x6c);
