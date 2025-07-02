#include "net/minecraft/world/entity/ai/sensing/Sensing.h"
#include "net/minecraft/world/entity/mob/Mob.h"

Sensing::Sensing(Mob* mob) : mMob(mob) {}

void Sensing::tick() {
    mSeen.clear();
    mUnseen.clear();
}

bool Sensing::canSee(std::shared_ptr<Entity> entity) {
    for (auto it = mSeen.begin(); it != mSeen.end(); ++it) {
        if (entity == (*it).lock()) {
            return true;
        }
    }

    for (auto it = mUnseen.begin(); it != mUnseen.end(); ++it) {
        if (entity == (*it).lock()) {
            return false;
        }
    }

    bool canSee = this->mMob->canSee(entity);

    if (canSee) {
        this->mSeen.push_back(entity);
    } else {
        this->mUnseen.push_back(entity);
    }

    return canSee;
}