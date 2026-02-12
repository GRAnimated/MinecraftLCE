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

        Particle** m_particles;
        int m_size;
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

    Level* m_level;
    ParticleList m_lists[30];
    std::vector<Particle*> m_partVec;
    Textures* m_textures;
    Random m_random;
    std::unordered_map<ePARTICLE_TYPE, ParticleProvider*> m_providerMap;
    bool m_tickingList;  // not sure about this name
    bool m_field0x249;
    short m_field0x24a;
    int m_field0x24c;
};

static_assert(offsetof(ParticleEngine, m_tickingList) == 0x248);

ASSERT_SIZEOF(ParticleEngine, 0x250)
ASSERT_SIZEOF(ParticleEngine::ParticleList, 0x10)
