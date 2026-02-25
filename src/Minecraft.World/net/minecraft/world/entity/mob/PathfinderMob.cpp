#include "net/minecraft/world/entity/mob/PathfinderMob.h"

#include "DecompUtils.h"
#include "net/minecraft/world/entity/ai/Path.h"
#include "net/minecraft/world/entity/ai/PathNavigation.h"
#include "net/minecraft/world/entity/mob/TamableAnimal.h"
#include "net/minecraft/world/level/pathfinder/BlockPathTypes.h"
#include <memory>

PathfinderMob::PathfinderMob(Level* level) : Mob(level) {
    this->m_path = nullptr;
    this->m_someEnt = nullptr;
    this->m_byte790 = 0;
    this->m_dword794 = 0;
    this->m_restrictRadius = -1.0;
    this->m_restrictCenter = BlockPos::zero;
    this->m_pathfindingMalus = BlockPathTypes::WATER->getMaulus();
}

PathfinderMob::~PathfinderMob() {
    delete this->m_path;
}

bool PathfinderMob::couldWander() {
    return this->m_noActionTime < 100 ? true : this->isExtraWanderingEnabled();
}

bool PathfinderMob::checkSpawnRules() {
    if (!Mob::checkSpawnRules())
        return false;

    return this->getWalkTargetValue(BlockPos(this->m_x, this->getBoundingBox()->m_inY, this->m_z)) >= 0.0f;
}

void PathfinderMob::tickLeash() {
    Mob::tickLeash();
    if (this->isLeashed()) {
        if (this->getLeashHolder() != nullptr && this->getLeashHolder()->m_level == this->m_level) {
            std::shared_ptr<Entity> ent = this->getLeashHolder();
            this->restrictTo(BlockPos((int)ent->m_x, (int)ent->m_y, (int)ent->m_z), 5);
            float dist = this->distanceTo(ent);

            // figuring out this shit below took me huge amount of hours
            std::shared_ptr<TamableAnimal> e
                = shared_from_this()->isType(eTamableAnimal) ?
                      std::dynamic_pointer_cast<TamableAnimal>(shared_from_this()) :
                      nullptr;
            if (e && e->isSitting()) {
                if (dist > 10.0f) {
                    this->dropLeash(true, true);
                }
                return;
            }

            this->onLeashDistance(dist);
            if (dist > 10.0f) {
                this->dropLeash(true, true);
                this->m_goalSelector.disableControlFlag(1);
            } else if (dist > 6.0f) {
                double deltX = (ent->m_x - this->m_x) / dist;
                double deltY = (ent->m_y - this->m_y) / dist;
                double deltZ = (ent->m_z - this->m_z) / dist;
                this->m_deltaMovementX += deltX * fabs(deltX) * 0.4;
                this->m_deltaMovementY += deltY * fabs(deltY) * 0.4;
                this->m_deltaMovementZ += deltZ * fabs(deltZ) * 0.4;
            } else {
                this->m_goalSelector.enableControlFlag(1);
                Vec3* vec = Vec3::newTemp(ent->m_x - this->m_x, ent->m_y - this->m_y, ent->m_z - this->m_z)
                                ->normalize()
                                ->scale(decomp_fmax1(dist - 2.0f, 0.0f));
                this->getNavigation()->moveTo(this->m_x + vec->m_x, this->m_y + vec->m_y,
                                              this->m_z + vec->m_z, this->followLeashSpeed());
            }
        }
    }
}

float PathfinderMob::getWalkTargetValue(const BlockPos&) {
    return 0.0f;
}

bool PathfinderMob::isPathFinding() {
    return !this->m_pathNavigation->isDone();
}

bool PathfinderMob::isWithinRestriction() {
    return this->isWithinRestriction(BlockPos(shared_from_this()));
}

bool PathfinderMob::isWithinRestriction(const BlockPos& pos) {
    return this->m_restrictRadius == -1.0f
           || this->m_restrictCenter.distSqr(pos) < this->m_restrictRadius * this->m_restrictRadius;
}

void PathfinderMob::restrictTo(const BlockPos& pos, int radius) {
    this->m_restrictCenter = pos;
    this->m_restrictRadius = radius;
}

BlockPos PathfinderMob::getRestrictCenter() {
    return this->m_restrictCenter;
}

float PathfinderMob::getRestrictRadius() {
    return this->m_restrictRadius;
}

void PathfinderMob::clearRestriction() {
    this->m_restrictRadius = -1.0f;
}

bool PathfinderMob::hasRestriction() {
    return this->m_restrictRadius != -1.0f;
}

void PathfinderMob::onLeashDistance(float) {}

double PathfinderMob::followLeashSpeed() {
    return 1.0;
}
