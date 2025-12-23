#include "net/minecraft/world/entity/mob/PathfinderMob.h"

#include "DecompUtils.h"
#include "net/minecraft/world/entity/ai/Path.h"
#include "net/minecraft/world/entity/ai/PathNavigation.h"
#include "net/minecraft/world/entity/mob/TamableAnimal.h"
#include "net/minecraft/world/level/pathfinder/BlockPathTypes.h"
#include <memory>

PathfinderMob::PathfinderMob(Level* level) : Mob(level) {
    this->mPath = nullptr;
    this->someEnt = nullptr;
    this->byte790 = 0;
    this->dword794 = 0;
    this->mRestrictRadius = -1.0;
    this->mRestrictCenter = BlockPos::zero;
    this->mPathfindingMalus = BlockPathTypes::WATER->getMaulus();
}

PathfinderMob::~PathfinderMob() {
    delete this->mPath;
}

bool PathfinderMob::couldWander() {
    return this->mNoActionTime < 100 ? true : this->isExtraWanderingEnabled();
}

bool PathfinderMob::checkSpawnRules() {
    if (!Mob::checkSpawnRules())
        return false;

    return this->getWalkTargetValue(BlockPos(this->mX, this->getBoundingBox()->minY, this->mZ)) >= 0.0f;
}

void PathfinderMob::tickLeash() {
    Mob::tickLeash();
    if (this->isLeashed()) {
        if (this->getLeashHolder() != nullptr && this->getLeashHolder()->mLevel == this->mLevel) {
            std::shared_ptr<Entity> ent = this->getLeashHolder();
            this->restrictTo(BlockPos((int)ent->mX, (int)ent->mY, (int)ent->mZ), 5);
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
                this->mGoalSelector.disableControlFlag(1);
            } else if (dist > 6.0f) {
                double deltX = (ent->mX - this->mX) / dist;
                double deltY = (ent->mY - this->mY) / dist;
                double deltZ = (ent->mZ - this->mZ) / dist;
                this->mDeltaMovementX += deltX * fabs(deltX) * 0.4;
                this->mDeltaMovementY += deltY * fabs(deltY) * 0.4;
                this->mDeltaMovementZ += deltZ * fabs(deltZ) * 0.4;
            } else {
                this->mGoalSelector.enableControlFlag(1);
                Vec3* vec = Vec3::newTemp(ent->mX - this->mX, ent->mY - this->mY, ent->mZ - this->mZ)
                                ->normalize()
                                ->scale(decomp_fmax1(dist - 2.0f, 0.0f));
                this->getNavigation()->moveTo(this->mX + vec->x, this->mY + vec->y, this->mZ + vec->z,
                                              this->followLeashSpeed());
            }
        }
    }
}

float PathfinderMob::getWalkTargetValue(const BlockPos&) {
    return 0.0f;
}

bool PathfinderMob::isPathFinding() {
    return !this->mPathNavigation->isDone();
}

bool PathfinderMob::isWithinRestriction() {
    return this->isWithinRestriction(BlockPos(shared_from_this()));
}

bool PathfinderMob::isWithinRestriction(const BlockPos& pos) {
    return this->mRestrictRadius == -1.0f
           || this->mRestrictCenter.distSqr(pos) < this->mRestrictRadius * this->mRestrictRadius;
}

void PathfinderMob::restrictTo(const BlockPos& pos, int radius) {
    this->mRestrictCenter = pos;
    this->mRestrictRadius = radius;
}

BlockPos PathfinderMob::getRestrictCenter() {
    return this->mRestrictCenter;
}

float PathfinderMob::getRestrictRadius() {
    return this->mRestrictRadius;
}

void PathfinderMob::clearRestriction() {
    this->mRestrictRadius = -1.0f;
}

bool PathfinderMob::hasRestriction() {
    return this->mRestrictRadius != -1.0f;
}

void PathfinderMob::onLeashDistance(float) {}

double PathfinderMob::followLeashSpeed() {
    return 1.0;
}
