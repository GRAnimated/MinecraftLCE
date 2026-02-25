#include "net/minecraft/world/entity/ai/sensing/Sensing.h"
#include "net/minecraft/world/entity/mob/Mob.h"

Sensing::Sensing(Mob* mob) : m_mob(mob) {}

void Sensing::tick() {
    m_seen.clear();
    m_unseen.clear();
}

bool Sensing::canSee(std::shared_ptr<Entity> entity) {
    for (auto it = m_seen.begin(); it != m_seen.end(); ++it) {
        if (!(entity != (*it).lock())) {
            return true;
        }
    }

    for (auto it = m_unseen.begin(); it != m_unseen.end(); ++it) {
        if (!(entity != (*it).lock())) {
            return false;
        }
    }

    bool canSee = this->m_mob->canSee(entity);

    if (canSee) {
        this->m_seen.push_back(entity);
    } else {
        this->m_unseen.push_back(entity);
    }

    return canSee;
}
