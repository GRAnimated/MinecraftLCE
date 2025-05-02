#include "Minecraft.Client/platform/NX/Platform.h"
#include "Minecraft.World/eINSTANCEOF.h"
#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/enchantments/ProtectionEnchantment.h"
#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.World/entity/LivingEntity.h"
#include "Minecraft.World/level/DamageSource.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Block.h"
#include "Minecraft.World/phys/AABB.h"
#include "Minecraft.Core/BlockPos.h"
#include <memory>

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
        while (this->mPosY > 0.0 && this->mPosY < 256.0) {
            this->setPos(this->mPosX, this->mPosY, this->mPosZ);

            if (this->mLevel
                    ->getCollisionAABBs(shared_from_this(), this->getBoundingBox(), false, false, false)
                    .empty()) {
                break;
            }

            ++this->mPosY;
        }

        this->mMotion.x = this->mMotion.y = this->mMotion.z = 0.0;
        this->mPitch = 0.0f;
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
            this->setBoundingBox(AABB::newTemp(this->mPosX - halfWidth, this->mPosY, this->mPosZ - halfWidth,
                                               this->mPosX + halfWidth, this->mPosY + this->mHeight,
                                               this->mPosZ + halfWidth));
            return;
        }

        const AABB* aabb = this->getBoundingBox();
        this->setBoundingBox(AABB::newTemp(aabb->min.x, aabb->min.y, aabb->min.z, aabb->min.x + this->mWidth,
                                           aabb->min.y + this->mHeight, aabb->min.z + this->mWidth));
        if (this->mWidth > widthBefore && !this->mFirstUpdate && !this->mLevel->mIsLocal) {
            this->move((MoverType)0, (widthBefore - this->mWidth), 0.0, (widthBefore - this->mWidth), false);
        }
    }
}

void Entity::setPos(double x, double y, double z) {
    this->mPosX = x;
    this->mPosY = y;
    this->mPosZ = z;
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
    if (this->mTimeUntilPortal > 0)
        --this->mTimeUntilPortal;
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
        this->mMotion.x = 0.0f;
    if (newZ != oldZ)
        this->mMotion.z = 0.0f;
    if (newY != oldY) {
        PIXBeginNamedEvent(0.0f, "Update entity after falling");
        block->updateEntityAfterFallOn(this->mLevel, shared_from_this());
        PIXEndNamedEvent();
    }
}

void Entity::setLocationFromBoundingbox() {
    const AABB* tempAABB = this->getBoundingBox();
    this->mPosX = (tempAABB->min.x + tempAABB->max.x) / 2.0;
    this->mPosY = tempAABB->min.y;
    this->mPosZ = (tempAABB->min.z + tempAABB->max.z) / 2.0;
}

/* TOO LAZY TO DO SOUNDEVENTS
void Entity::getSwimSound() {}

void Entity::getSwimSplashSound() {}
*/

// void Entity::checkInsideBlocks() {}

void Entity::onInsideBlock(BlockState const*) {}

// void playStepSound(BlockPos const&, Block*) {}

float Entity::playFlySound(float) {
    return 0.0f;
}

bool Entity::makeFlySound() {
    return false;
}

void Entity::playSound(SoundEvent const* sound, float volume, float pitch) {
    if (!this->isSilent()) {
        this->mLevel->playSound(nullptr, this->mPosX, this->mPosY, this->mPosZ, sound, this->getSoundSource(),
                                volume, pitch, 16.0f);
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

void Entity::checkFallDamage(double fall, bool onGround, Block* block, BlockPos const& pos) {
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

// NON_MATCHING: some magic crap
Vec3* Entity::getViewVector(float partialTicks) {
    float yaw = this->mYaw;
    float pitch;
    if (partialTicks == 1.0f) {
        pitch = this->mPitch;
    } else {
        yaw = this->mPrevYaw + ((yaw - this->mPrevYaw) * partialTicks);
        pitch = this->mPrevPitch + ((this->mPitch - this->mPrevPitch) * partialTicks);
    }
    return this->calculateViewVector(pitch, yaw);
}