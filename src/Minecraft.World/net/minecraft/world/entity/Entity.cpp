#include "net/minecraft/world/entity/Entity.h"

#include "NX/Platform.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/NonNullList.h"
#include "net/minecraft/network/syncher/EntityDataSerializers.h"
#include "net/minecraft/network/syncher/SynchedEntityData.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/damagesource/DamageSource.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/enchantment/enchantments/ProtectionEnchantment.h"
#include "net/minecraft/world/entity/CommandSender.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/dimension/Dimension.h"
#include "net/minecraft/world/level/dimension/DimensionType.h"
#include "net/minecraft/world/phys/AABB.h"
#include "types.h"
#include <memory>

int Entity::getId() {
    return mId;
}
void Entity::setId(int id) {
    mId = id;
}

void Entity::staticCtor() {
    // TODO: Find names for these based on the places they are used
    qword_7101789FA0 = SynchedEntityData::defineId(eSerializer, eSerializer,
                                                   EntityDataSerializers::sINT_EntityDataSerializer);
    qword_7101789FA8 = SynchedEntityData::defineId(eSerializer, eSerializer,
                                                   EntityDataSerializers::sINT_EntityDataSerializer);
    qword_7101789FB0 = SynchedEntityData::defineId(eSerializer, eSerializer,
                                                   EntityDataSerializers::sSTRING_EntityDataSerializer);
    qword_7101789FB8 = SynchedEntityData::defineId(eSerializer, eSerializer,
                                                   EntityDataSerializers::sBOOLEAN_EntityDataSerializer);
    qword_7101789FC0 = SynchedEntityData::defineId(eSerializer, eSerializer,
                                                   EntityDataSerializers::sBOOLEAN_EntityDataSerializer);
    qword_7101789FC8 = SynchedEntityData::defineId(eSerializer, eSerializer,
                                                   EntityDataSerializers::sBOOLEAN_EntityDataSerializer);
    qword_7101789FE0 = SynchedEntityData::defineId(eSerializer, eSerializer,
                                                   EntityDataSerializers::sSTRING_EntityDataSerializer);
    qword_7101789FD8 = SynchedEntityData::defineId(eSerializer, eSerializer,
                                                   EntityDataSerializers::sBOOLEAN_EntityDataSerializer);
    qword_7101789FD0 = SynchedEntityData::defineId(eSerializer, eSerializer,
                                                   EntityDataSerializers::sBOOLEAN_EntityDataSerializer);
}

// NON_MATCHING: a couple things need to be moved around to move instructions into the right place
void Entity::_init(bool synched, Level* level) {
    if (synched && TlsGetValue(sTlsIndex)) {
        mId = getSmallId();
    } else {
        mId = sEntityAmount++;
        if (sEntityAmount == 0x7FFFFFF)
            sEntityAmount = 2048;
    }

    sViewScale = 1.0;

    mBlocksBuilding = false;
    mVehicle = nullptr;
    mBoardingCooldown = 0;
    mForcedLoading = false;

    mXo = mYo = mZo = 0.0;
    mX = mY = mZ = 0.0;
    mDeltaMovementX = mDeltaMovementY = mDeltaMovementZ = 0.0;
    mXRot = mYRot = 0.0f;
    mXRotO = mYRotO = 0.0f;

    field_d8 = 0;
    field_dc = 0;
    field_e0 = 0;
    field_e4 = 0;
    mBoundingBox = AABB::newPermanent(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    mFallTicks = 0;
    mHardLandingsCount = 0;
    mWidth = 0.6f;
    mHeight = 1.8f;
    mOnGround = false;
    mHasVerticalCollision = false;
    mHasHorizontalCollision = false;
    mHasCollision = false;
    mIsHurtMarked = false;
    mIsInWeb = false;
    mCipa = true;
    mIsRemoved = false;
    mNextStep = 1;
    mNextFlap = 1.0f;
    mXOld = mYOld = mZOld = 0.0;
    mMaxUpStep = 0.0f;
    mHasNoPhysics = false;
    mPushThrough = 0;
    mWalkDistO = 0.0f;
    mWalkDist = 0.0f;
    mMoveDist = 0.0f;
    mFallDistance = 0.0f;

    Random* random = new Random();
    mRand = random;
    mTickCount = 0;
    mWasInWater = false;
    mInvulnerableTime = 0;
    mIsFirstTick = true;
    mIsImmuneToFire = false;
    mIsInChunk = false;
    mXChunk = mYChunk = mZChunk = 0;
    mXP = mYP = mZP = 0;
    field_190 = nullptr;
    mHasNoCulling = false;
    mHasImpulse = false;
    mChangingDimensionDelay = 0;
    mIsInsidePortal = false;
    mPortalTime = 0;
    mDimensionId = 0;
    mIsGlowing = false;
    mPortalEntranceOffset = nullptr;
    mPortalEntranceForwards = nullptr;

    if (synched)
        mStringUUID = L"ent" + Mth::createInsecureUUID(random);

    mCommandStats = new CommandStats();

    mIsInvulnerable = false;
    mHasTeleported = false;
    mRemainingFireTicks = -getFireImmuneTicks();
    mPistonDeltas = arrayWithLength<double>(3, true);
    mPistonDeltasGameTime = 0;
    mInventory = NonNullList<not_null_ptr<ItemInstance>>();

    mType = 0;
    field_cc = false;
    field_d0 = -1;
}

Entity::Entity(Level* level, bool synched) {
    mLevel = level;
    MemSect(16);
    _init(synched, level);
    MemSect(0);

    setPos(0.0, 0.0, 0.0);

    if (level)
        mDimensionId = level->mDimension->getType()->getId();

    if (synched) {
        SynchedEntityData* synchedEntityData = new SynchedEntityData(this);
        mEntityData = std::shared_ptr<SynchedEntityData>(synchedEntityData);
    } else {
        mEntityData = nullptr;
    }

    if (mEntityData) {
        mEntityData->createDateItem(qword_7101789FA0, 0);
        mEntityData->createDateItem(qword_7101789FA8, 300);
        mEntityData->createDateItem(qword_7101789FB8, false);
        mEntityData->createDateItem(qword_7101789FB0, std::wstring(L""));
        mEntityData->createDateItem(qword_7101789FC0, false);
        mEntityData->createDateItem(qword_7101789FC8, false);
        mEntityData->createDateItem(qword_7101789FD0, false);
        mEntityData->createDateItem(qword_7101789FD8, false);
        mEntityData->createDateItem(qword_7101789FE0, std::wstring(L""));
    }

    field_e8 = 0;
}

void Entity::fjDerivedCtorCalls() {
    this->mType = this->GetType();
    this->defineSynchedData();
}

void Entity::kill() {
    this->remove();
}

void Entity::resetPos() {
    if (!this->mLevel)
        return;

    std::shared_ptr<Entity> ent = shared_from_this();
    while (this->mY > 0.0 && this->mY < 256.0) {
        this->setPos(this->mX, this->mY, this->mZ);

        if (this->mLevel->getCollisionAABBs(ent, this->getBoundingBox(), false, false, false)->empty()) {
            break;
        }

        ++this->mY;
    }

    this->mDeltaMovementZ = this->mDeltaMovementY = this->mDeltaMovementX = 0.0;
    this->mXRot = 0.0f;
}

void Entity::remove() {
    this->mIsRemoved = true;
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
        this->setBoundingBox(AABB::newTemp(aabb->minX, aabb->minY, aabb->minZ, aabb->minX + this->mWidth,
                                           aabb->minY + this->mHeight, aabb->minZ + this->mWidth));
        if (this->mWidth > widthBefore && !this->mIsFirstTick && !this->mLevel->mIsLocal) {
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

    if (this->mRemainingFireTicks < i)
        this->mRemainingFireTicks = i;
}

void Entity::clearFire() {
    this->mRemainingFireTicks = 0;
}

void Entity::outOfWorld() {
    this->remove();
}

// void Entity::move(MoverType, double, double, double, bool) {} // maybe not

void Entity::updateDeltaAfterMove(Block* block, double oldX, double oldY, double oldZ, double& newX,
                                  double& newY, double& newZ) {
    if (newX != oldX)
        this->mDeltaMovementX = 0.0f;
    if (newZ != oldZ)
        this->mDeltaMovementZ = 0.0f;
    if (newY != oldY) {
        PIXBeginNamedEvent(0.0f, "Update entity after falling");
        block->updateEntityAfterFallOn(this->mLevel, shared_from_this());
        PIXEndNamedEvent();
    }
}

void Entity::setLocationFromBoundingbox() {
    const AABB* tempAABB = this->getBoundingBox();
    this->mX = (tempAABB->minX + tempAABB->maxX) / 2.0;
    this->mY = tempAABB->minY;
    this->mZ = (tempAABB->minZ + tempAABB->maxZ) / 2.0;
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
            ++this->mHardLandingsCount;  // hard enough to take fall damage
        }

        this->mFallTicks = 0;
        this->mFallDistance = 0.0f;
    } else if (fall < 0.0) {
        this->mFallDistance -= (float)fall;
        ++this->mFallTicks;
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
void Entity::readAdditionContructionTag(CompoundTag*) {}
void Entity::SetPositionLocked(bool) {}
void Entity::SetGlideCollisionDamage(bool) {}
void Entity::SetLiftForceModifier(double) {}
void Entity::onLoadedFromSave() {}
void Entity::setUsingItemFlag(bool) {}
void Entity::fjDebugCheckSmallIdLeaks() {}
