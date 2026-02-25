#include "net/minecraft/client/particle/TrackingEmitter.h"

#include "net/minecraft/client/particle/Particle.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/LevelListener.h"

TrackingEmitter::TrackingEmitter(Level* level, std::shared_ptr<Entity> entity, const ParticleType* type,
                                 int maxAge)
    : Particle(level, entity->m_x, entity->getBoundingBox()->m_inY + (entity->m_height / 2), entity->m_z,
               entity->m_deltaMovementX, entity->m_deltaMovementY, entity->m_deltaMovementZ) {
    m_target = entity;
    m_maxAge = maxAge;
    m_type = type;
    tick();
}

ePARTICLE_TYPE TrackingEmitter::getType() {
    return ePARTICLE_TYPE::ePARTICLE_TYPE_TrackingEmitter;
}

int TrackingEmitter::getParticleTexture() {
    return 3;
}

void TrackingEmitter::render(BufferBuilder*, std::shared_ptr<Entity>&, float, float, float, float, float,
                             float) {
    return;
}

// NON_MATCHING | score 1225
void TrackingEmitter::tick() {
    for (int i = 0; i < 16; i++) {
        double f1 = (m_random.nextFloat() * 2) - 1.0;
        double f2 = (m_random.nextFloat() * 2) - 1.0;
        double f3 = (m_random.nextFloat() * 2) - 1.0;
        double expr = (f1 * f1 + f2 * f2 + f3 * f3);
        if (expr <= 1.0f) {
            m_level->addParticle(
                m_type, m_target->m_x + f1 * m_target->m_width / 4,
                m_target->getBoundingBox()->m_inY + (m_target->m_height * 0.5) + f2 * m_target->m_height / 4,
                m_target->m_z + f3 * m_target->m_width / 4, f1, f2 + 0.2, f3, arrayWithLength<int>());
        }
    }

    m_age++;
    if (m_age >= m_maxAge)
        remove();
}
