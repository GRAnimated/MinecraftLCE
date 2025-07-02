#include "net/minecraft/client/platform/NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/damagesource/DamageSource.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/enchantment/Enchantment.h"
#include "net/minecraft/world/enchantment/enchantments/ProtectionEnchantment.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/phys/AABB.h"
#include <memory>

Entity::Entity(Level*, bool) {}

void Entity::fjDerivedCtorCalls() {
    this->mType = this->GetType();
    this->defineSynchedData();
}

void Entity::kill() {
    this->remove();
}

// NON_MATCHING: some shared_ptr crap
void Entity::resetPos() {
    if (this->mLevel) {
        std::shared_ptr<Entity> ent = shared_from_this();
        while (this->mY > 0.0 && this->mY < 256.0) {
            this->setPos(this->mX, this->mY, this->mZ);

            if (this->mLevel->getCollisionAABBs(ent, this->getBoundingBox(), false, false, false).empty()) {
                break;
            }

            ++this->mY;
        }

        this->mDeltaMovement.x = this->mDeltaMovement.y = this->mDeltaMovement.z = 0.0;
        this->mXRot = 0.0f;
    }
}

void Entity::remove() {
    this->mRemoved = true;
    this->stopCurrentLerp();
}

void Entity::setDropContainerContent(bool) {}

void Entity::setSize(float width, float height) {
    if (width != this->mWidth || height != this->mHeight) {
        float widthBefore = this->mWidth;
        this->mWidth = width;
        this->mHeight = height;
        if (this->mWidth < widthBefore) {
            double halfWidth = width / 2.0;
            this->setBoundingBox(AABB::newTemp(this->mX - halfWidth, this->mY, this->mZ - halfWidth,
                                               this->mX + halfWidth, this->mY + this->mHeight,
                                               this->mZ + halfWidth));
            return;
        }

        const AABB* aabb = this->getBoundingBox();
        this->setBoundingBox(AABB::newTemp(aabb->min.x, aabb->min.y, aabb->min.z, aabb->min.x + this->mWidth,
                                           aabb->min.y + this->mHeight, aabb->min.z + this->mWidth));
        if (this->mWidth > widthBefore && !this->mFirstTick && !this->mLevel->mIsLocal) {
            this->move((MoverType)0, (widthBefore - this->mWidth), 0.0, (widthBefore - this->mWidth), false);
        }
    }
}

void Entity::setPos(double x, double y, double z) {
    this->mX = x;
    this->mY = y;
    this->mZ = z;
    float halfWidth = this->mWidth / 2.0f;
    this->setBoundingBox(
        AABB::newTemp(x - halfWidth, y, z - halfWidth, x + halfWidth, y + this->mHeight, z + halfWidth));
}

void Entity::tick() {
    if (!this->mLevel->mIsLocal) {
        this->setSharedFlag(8, this->isGlowing());
    }

    PIXBeginNamedEvent(0.0, "Entity tick");
    this->baseTick();
    PIXEndNamedEvent();
}

// void baseTick() {} // don't care about this rn

void Entity::processDimensionDelay() {
    if (this->mChangingDimensionDelay > 0)
        --this->mChangingDimensionDelay;
}

int Entity::getPortalWaitTime() {
    return 1;
}

void Entity::setSecondsOnFire(int seconds) {
    int i = seconds * 20;
    if (this->isType(eLivingEntity)) {
        i = ProtectionEnchantment::getFireAfterDampener(
            std::static_pointer_cast<LivingEntity>(shared_from_this()), i);
    }

    if (this->mFire < i)
        this->mFire = i;
}

void Entity::clearFire() {
    this->mFire = 0;
}

void Entity::outOfWorld() {
    this->remove();
}

// void Entity::move(MoverType, double, double, double, bool) {} // maybe not

void Entity::updateDeltaAfterMove(Block* block, double oldX, double oldY, double oldZ, double& newX,
                                  double& newY, double& newZ) {
    if (newX != oldX)
        this->mDeltaMovement.x = 0.0f;
    if (newZ != oldZ)
        this->mDeltaMovement.z = 0.0f;
    if (newY != oldY) {
        PIXBeginNamedEvent(0.0f, "Update entity after falling");
        block->updateEntityAfterFallOn(this->mLevel, shared_from_this());
        PIXEndNamedEvent();
    }
}

void Entity::setLocationFromBoundingbox() {
    const AABB* tempAABB = this->getBoundingBox();
    this->mX = (tempAABB->min.x + tempAABB->max.x) / 2.0;
    this->mY = tempAABB->min.y;
    this->mZ = (tempAABB->min.z + tempAABB->max.z) / 2.0;
}

/* TOO LAZY TO DO SOUNDEVENTS
void Entity::getSwimSound() {}

void Entity::getSwimSplashSound() {}
*/

// void Entity::checkInsideBlocks() {}

void Entity::onInsideBlock(const BlockState*) {}

// void playStepSound(const BlockPos&, Block*) {}

float Entity::playFlySound(float) {
    return 0.0f;
}

bool Entity::makeFlySound() {
    return false;
}

void Entity::playSound(const SoundEvent* sound, float volume, float pitch) {
    if (!this->isSilent()) {
        this->mLevel->playSound(nullptr, this->mX, this->mY, this->mZ, sound, this->getSoundSource(), volume,
                                pitch, 16.0f);
    }
}

/* SynchedEntityData crap
bool Entity::isSilent() {}
void Entity::setSilent(bool) {}
void Entity::isNoGravity() {}
void Entity::setNoGravity(bool) {}
*/

bool Entity::makeStepSound() {
    return true;
}

void Entity::checkFallDamage(double fall, bool onGround, Block* block, const BlockPos& pos) {
    if (onGround) {
        if (this->mFallDistance > 0.0f) {
            block->fallOn(this->mLevel, pos, shared_from_this(), this->mFallDistance);
            ++this->mFallTicks2;
        }

        this->idk = 0;
        this->mFallDistance = 0.0f;
    } else if (fall < 0.0) {
        this->mFallDistance -= (float)fall;
        ++this->idk;
    }
}

AABB* Entity::getCollideBox() {
    return nullptr;
}

void Entity::burn(int howMuch) {
    if (!this->mIsImmuneToFire)
        this->hurt(DamageSource::IN_FIRE, howMuch);
}

Vec3* Entity::getViewVector(float partialTicks) {
    if (partialTicks == 1.0f) {
        return this->calculateViewVector(this->mXRot, this->mYRot);
    } else {
        return this->calculateViewVector(this->mXRotO + ((this->mXRot - this->mXRotO) * partialTicks),
                                         this->mYRotO + ((this->mYRot - this->mYRotO) * partialTicks));
    }
}