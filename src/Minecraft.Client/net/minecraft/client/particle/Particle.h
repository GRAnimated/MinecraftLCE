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

    void* m_field0x8;
    void* m_field0x10;
    Level* m_level;
    double m_prevPosX;
    double m_prevPosY;
    double m_prevPosZ;
    double m_posX;
    double m_posY;
    double m_posZ;
    double m_velX;
    double m_velY;
    double m_velZ;
    bool m_isOnGround;
    bool m_canCollide;
    bool m_isRemoved;
    bool m_field0x6b;
    float m_width;
    float m_height;
    int m_field0x74;
    Random m_random;
    int m_field0x90;
    int m_field0x94;
    TextureUVCoordinateSet m_uvSet;
    float m_texJitterX;
    float m_texJitterY;
    float m_field0x108;
    float m_field0x10c;
    float m_field0x110;
    float m_alpha;
    int m_age;
    int m_maxAge;
    float m_scale;
    float m_gravityScale;
    TextureAtlasSprite* m_spriteAtlas;
    void* m_field0x130;
    AABB* m_boundingBox;

    static double X_OFFSET;
    static double Y_OFFSET;
    static double Z_OFFSET;
    static Vec3* VIEW_DIRECTION;  // mhh idk maybe this should be in ParticleEngine, tho the setter is here
};

// ASSERT_SIZEOF(Particle, 0x98)

static_assert(offsetof(Particle, m_random) == 0x78);
static_assert(offsetof(Particle, m_uvSet) == 0x98);
static_assert(offsetof(Particle, m_boundingBox) == 0x138);
static_assert(offsetof(Particle, m_canCollide) == 0x69);
static_assert(offsetof(Particle, m_width) == 0x6c);
