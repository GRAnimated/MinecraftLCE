#include "net/minecraft/client/particle/ParticleEngine.h"

#include "net/minecraft/client/particle/Particle.h"
#include "net/minecraft/client/particle/TrackingEmitter.h"
#include "net/minecraft/client/renderer/Camera.h"
#include "net/minecraft/client/renderer/texture/Textures.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/LevelListener.h"
#include "net/minecraft/world/level/dimension/Dimension.h"
#include "net/minecraft/world/level/dimension/DimensionType.h"
#include <cstdio>

ParticleEngine::ParticleList::ParticleList() {
    m_particles = new Particle*[0x4000];
    m_size = 0;
}

void ParticleEngine::ParticleList::ClearParticles() {
    for (int i = 0; i < m_size; ++i)
        delete m_particles[i];
    m_size = 0;
}

void ParticleEngine::ParticleList::push_back(Particle* particle) {
    m_particles[m_size++] = particle;
}

void ParticleEngine::ParticleList::RemoveParticle(unsigned int idx) {
    m_particles[idx] = m_particles[--m_size];
}

Particle* ParticleEngine::ParticleList::at(int idx) {
    return m_particles[idx];
}

int ParticleEngine::ParticleList::size() {
    return m_size;
}

bool ParticleEngine::ParticleList::empty() {
    return m_size == 0;
}

ParticleEngine::ParticleEngine(Level* level, Textures* textures) {
    m_tickingList = false;
    m_field0x249 = false;
    m_level = level;
    m_textures = textures;
    registerProviders();
    m_field0x24c = 0;
}

void ParticleEngine::registerParticle(ePARTICLE_TYPE type, ParticleProvider* provider) {
    m_providerMap[type] = provider;
}

// NON_MATCHING incomplete
void ParticleEngine::setLevel(Level* newLevel) {
    m_level = newLevel;
    if (!newLevel) {
        for (int i = 0; i < 30; i++)
            m_lists[i].ClearParticles();
    }
}

void ParticleEngine::tickParticleList(ParticleEngine::ParticleList* list) {
    m_tickingList = true;

    int sz = 0;  // this is weird, idk why it's like this and if it was originally like this, tho it matches
    if (!list->empty() && (sz = list->size()); sz > 0) {
        for (int idx = 0; idx < list->size(); ++idx) {
            sz--;
            if (sz < 0)
                break;
            Particle* p = list->at(idx);

            tickParticle(p);

            if (!p->isAlive()) {
                p = list->at(idx);
                if (p->getType() == 0x80221)
                    m_field0x24c--;

                if (p != nullptr)
                    delete p;

                list->RemoveParticle(idx);
                idx--;
            }
        }
    }

    m_tickingList = false;
}

void ParticleEngine::moveParticlesBetweenLists(ParticleEngine::ParticleList* list1,
                                               ParticleEngine::ParticleList* list2) {
    m_tickingList = true;
    if (!list1->empty() && list1->size() > 0) {
        for (int i = 0; i < list1->size(); i++) {
            Particle* p = list1->at(i);
            if (p->getAlpha() == 1.0) {
                list1->RemoveParticle(i);
                list2->push_back(p);
            }
        }
    }

    if (!list2->empty() && list2->size() > 0) {
        for (int i = 0; i < list2->size(); i++) {
            Particle* p = list2->at(i);
            if (p->getAlpha() < 1.0) {
                list2->RemoveParticle(i);
                list1->push_back(p);
            }
        }
    }
    m_tickingList = false;
}

void ParticleEngine::tickParticle(Particle* part) {
    part->tick();
}

// NON_MATCHING | 6804 meh, it's a mess i'm lazy
void ParticleEngine::add(Particle* part) {
    int dimIndex;
    int unk2;

    int partTex = part->getParticleTexture();
    float alpha = part->getAlpha();
    int typeId = part->getType();

    DimensionType* dimType = part->getLevel()->m_dimension->getType();
    if (dimType == DimensionType::OVERWORLD) {
        dimIndex = 0;
    } else {
        dimType = part->getLevel()->m_dimension->getType();
        dimIndex = 1;
        if (dimType != DimensionType::NETHER) {
            dimIndex = 2;
        }
    }

    int maxCount = 0x4000;
    if (typeId == 0x8021e)
        maxCount = 1000;
    else if (typeId == 0x80221) {
        if (m_field0x24c > 1999) {
            delete part;
            return;
        }
        m_field0x24c++;
    }

    bool transparent = part->isTransparent();
    ParticleList* list = (m_lists + dimIndex * 10 + partTex * 2 + (alpha == 1.0) + !transparent);

    if (list->size() >= maxCount) {
        Particle* old = list->at(0);
        if (old->getType() == 0x80221)
            m_field0x24c--;
        delete old;
        list->RemoveParticle(0);
    }

    list->push_back(part);
}

void ParticleEngine::createTrackingEmitter(std::shared_ptr<Entity> entity, const ParticleType* type) {
    m_partVec.push_back(new TrackingEmitter(m_level, entity, type, 3));
}

void ParticleEngine::createTrackingEmitter(std::shared_ptr<Entity> entity, const ParticleType* type,
                                           int maxAge) {
    m_partVec.push_back(new TrackingEmitter(m_level, entity, type, maxAge));
}

// NON_MATCHING incomplete
void ParticleEngine::render(std::shared_ptr<Entity> entity, float partialTicks, int) {
    if (m_field0x249) {
        return;
    }

    double entityXOld = entity->m_xOld;
    float rotX = Camera::getRotationX();
    float rotZ = Camera::getRotationZ();
    float rotYZ = Camera::getRotationYZ();
    float rotXY = Camera::getRotationXY();
    float rotXZ = Camera::getRotationXZ();

    Particle::setXOffset(entity->m_xOld + partialTicks * (entity->m_x - entity->m_xOld));
    Particle::setYOffset(entity->m_yOld + partialTicks * (entity->m_y - entity->m_yOld));
    Particle::setZOffset(entity->m_zOld + partialTicks * (entity->m_z - entity->m_zOld));

    Vec3* view = entity->getViewVector(partialTicks);
    Particle::setCamerViewDirection(view);

    int dimIndex;
    DimensionType* dimType = m_level->m_dimension->getType();
    if (dimType == DimensionType::OVERWORLD) {
        dimIndex = 0;
    } else {
        dimType = m_level->m_dimension->getType();
        dimIndex = 1;
        if (dimType != DimensionType::NETHER) {
            dimIndex = 2;
        }
    }
}

void ParticleEngine::tick() {
    for (int i = 0; i < 5; ++i) {
        tickTextureType(i);
    }

    auto it = m_partVec.begin();
    while (it != m_partVec.end()) {
        Particle* p = *it;

        p->tick();
        if (p->isAlive()) {
            ++it;
        } else {
            it = m_partVec.erase(it);
            if (p)
                delete p;
        }
    }
}

void ParticleEngine::tickTextureType(int idx) {
    int base = idx * 2;

    for (int off = 0; off <= 20; off += 10) {
        tickParticleList(m_lists + base + off);
        tickParticleList(m_lists + base + off + 1);
        moveParticlesBetweenLists(m_lists + base + off, m_lists + base + off + 1);
    }
}
