#pragma once

#include "net/minecraft/client/particle/Particle.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/level/LevelListener.h"
#include "types.h"
#include <array>
#include <memory>
#include <unordered_map>
#include <vector>

class Level;
class Textures;
class ParticleProvider;
class ParticleType;

class ParticleEngine {
public:
    struct ParticleList {
        ParticleList();
        void ClearParticles();
        void push_back(Particle*);
        void RemoveParticle(unsigned int);
        Particle* at(int);
        int size();
        bool empty();

        Particle** mParticles;
        int mSize;
    };

    ParticleEngine(Level* level, Textures* textures);

    void registerProviders();
    void registerParticle(ePARTICLE_TYPE, ParticleProvider*);
    void setLevel(Level*);
    void tickParticleList(ParticleEngine::ParticleList*);
    void moveParticlesBetweenLists(ParticleEngine::ParticleList*, ParticleEngine::ParticleList*);
    void tickParticle(Particle*);
    void add(Particle*);
    void crack(const BlockPos&, const Direction*);
    void createTrackingEmitter(std::shared_ptr<Entity>, const ParticleType*);
    void createTrackingEmitter(std::shared_ptr<Entity>, const ParticleType*, int);
    void render(std::shared_ptr<Entity>, float, int);
    void renderLit(std::shared_ptr<Entity>, float, int);
    void tick();
    void tickTextureType(int);

    Level* mLevel;
    ParticleList mLists[30];
    std::vector<Particle*> mPartVec;
    Textures* mTextures;
    Random mRandom;
    std::unordered_map<ePARTICLE_TYPE, ParticleProvider*> mProviderMap;
    bool mTickingList;  // not sure about this name
    bool field_0x249;
    short field_0x24a;
    int field_0x24c;
};

static_assert(offsetof(ParticleEngine, mTickingList) == 0x248);

ASSERT_SIZEOF(ParticleEngine, 0x250)
ASSERT_SIZEOF(ParticleEngine::ParticleList, 0x10)
