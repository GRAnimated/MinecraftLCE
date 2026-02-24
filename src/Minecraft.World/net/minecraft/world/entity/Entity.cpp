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
    return m_id;
}
void Entity::setId(int id) {
    m_id = id;
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
        m_id = getSmallId();
    } else {
        m_id = sEntityAmount++;
        if (sEntityAmount == 0x7FFFFFF)
            sEntityAmount = 2048;
    }

    sViewScale = 1.0;

    m_blocksBuilding = false;
    m_vehicle = nullptr;
    m_boardingCooldown = 0;
    m_forcedLoading = false;

    m_xo = m_yo = m_zo = 0.0;
    m_x = m_y = m_z = 0.0;
    m_deltaMovementX = m_deltaMovementY = m_deltaMovementZ = 0.0;
    m_xRot = m_yRot = 0.0f;
    m_xRotO = m_yRotO = 0.0f;

    m_fieldD8 = 0;
    m_fieldDc = 0;
    m_fieldE0 = 0;
    m_fieldE4 = 0;
    m_boundingBox = AABB::newPermanent(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    m_fallTicks = 0;
    m_hardLandingsCount = 0;
    m_width = 0.6f;
    m_height = 1.8f;
    m_onGround = false;
    m_hasVerticalCollision = false;
    m_hasHorizontalCollision = false;
    m_hasCollision = false;
    m_isHurtMarked = false;
    m_isInWeb = false;
    m_cipa = true;
    m_isRemoved = false;
    m_nextStep = 1;
    m_nextFlap = 1.0f;
    m_xOld = m_yOld = m_zOld = 0.0;
    m_maxUpStep = 0.0f;
    m_hasNoPhysics = false;
    m_pushThrough = 0;
    m_walkDistO = 0.0f;
    m_walkDist = 0.0f;
    m_moveDist = 0.0f;
    m_fallDistance = 0.0f;

    Random* random = new Random();
    m_rand = random;
    m_tickCount = 0;
    m_wasInWater = false;
    m_invulnerableTime = 0;
    m_isFirstTick = true;
    m_isImmuneToFire = false;
    m_isInChunk = false;
    m_xChunk = m_yChunk = m_zChunk = 0;
    m_xp = m_yp = m_zp = 0;
    m_field190 = nullptr;
    m_hasNoCulling = false;
    m_hasImpulse = false;
    m_changingDimensionDelay = 0;
    m_isInsidePortal = false;
    m_portalTime = 0;
    m_dimensionId = 0;
    m_isGlowing = false;
    m_portalEntranceOffset = nullptr;
    m_portalEntranceForwards = nullptr;

    if (synched)
        m_stringUuid = L"ent" + Mth::createInsecureUUID(random);

    m_commandStats = new CommandStats();

    m_isInvulnerable = false;
    m_hasTeleported = false;
    m_remainingFireTicks = -getFireImmuneTicks();
    m_pistonDeltas = arrayWithLength<double>(3, true);
    m_pistonDeltasGameTime = 0;
    m_inventory = NonNullList<not_null_ptr<ItemInstance>>();

    m_type = 0;
    m_fieldCc = false;
    m_fieldD0 = -1;
}

Entity::Entity(Level* level, bool synched) {
    m_level = level;
    MemSect(16);
    _init(synched, level);
    MemSect(0);

    setPos(0.0, 0.0, 0.0);

    if (level)
        m_dimensionId = level->m_dimension->getType()->getId();

    if (synched) {
        SynchedEntityData* synchedEntityData = new SynchedEntityData(this);
        m_entityData = std::shared_ptr<SynchedEntityData>(synchedEntityData);
    } else {
        m_entityData = nullptr;
    }

    if (m_entityData) {
        m_entityData->createDateItem(qword_7101789FA0, 0);
        m_entityData->createDateItem(qword_7101789FA8, 300);
        m_entityData->createDateItem(qword_7101789FB8, false);
        m_entityData->createDateItem(qword_7101789FB0, std::wstring(L""));
        m_entityData->createDateItem(qword_7101789FC0, false);
        m_entityData->createDateItem(qword_7101789FC8, false);
        m_entityData->createDateItem(qword_7101789FD0, false);
        m_entityData->createDateItem(qword_7101789FD8, false);
        m_entityData->createDateItem(qword_7101789FE0, std::wstring(L""));
    }

    m_fieldE8 = 0;
}

void Entity::fjDerivedCtorCalls() {
    this->m_type = this->GetType();
    this->defineSynchedData();
}

void Entity::kill() {
    this->remove();
}

void Entity::resetPos() {
    if (!this->m_level)
        return;

    std::shared_ptr<Entity> ent = shared_from_this();
    while (this->m_y > 0.0 && this->m_y < 256.0) {
        this->setPos(this->m_x, this->m_y, this->m_z);

        if (this->m_level->getCollisionAABBs(ent, this->getBoundingBox(), false, false, false)->empty()) {
            break;
        }

        ++this->m_y;
    }

    this->m_deltaMovementZ = this->m_deltaMovementY = this->m_deltaMovementX = 0.0;
    this->m_xRot = 0.0f;
}

void Entity::remove() {
    this->m_isRemoved = true;
    this->stopCurrentLerp();
}

void Entity::setDropContainerContent(bool) {}

void Entity::setSize(float width, float height) {
    if (width != this->m_width || height != this->m_height) {
        float widthBefore = this->m_width;
        this->m_width = width;
        this->m_height = height;
        if (this->m_width < widthBefore) {
            double halfWidth = width / 2.0;
            this->setBoundingBox(AABB::newTemp(this->m_x - halfWidth, this->m_y, this->m_z - halfWidth,
                                               this->m_x + halfWidth, this->m_y + this->m_height,
                                               this->m_z + halfWidth));
            return;
        }

        const AABB* aabb = this->getBoundingBox();
        this->setBoundingBox(AABB::newTemp(aabb->m_inX, aabb->m_inY, aabb->m_inZ, aabb->m_inX + this->m_width,
                                           aabb->m_inY + this->m_height, aabb->m_inZ + this->m_width));
        if (this->m_width > widthBefore && !this->m_isFirstTick && !this->m_level->m_isLocal) {
            this->move((MoverType)0, (widthBefore - this->m_width), 0.0, (widthBefore - this->m_width),
                       false);
        }
    }
}

void Entity::setPos(double x, double y, double z) {
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
    float halfWidth = this->m_width / 2.0f;
    this->setBoundingBox(
        AABB::newTemp(x - halfWidth, y, z - halfWidth, x + halfWidth, y + this->m_height, z + halfWidth));
}

void Entity::tick() {
    if (!this->m_level->m_isLocal) {
        this->setSharedFlag(8, this->isGlowing());
    }

    PIXBeginNamedEvent(0.0, "Entity tick");
    this->baseTick();
    PIXEndNamedEvent();
}

// void baseTick() {} // don't care about this rn

void Entity::processDimensionDelay() {
    if (this->m_changingDimensionDelay > 0)
        --this->m_changingDimensionDelay;
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

    if (this->m_remainingFireTicks < i)
        this->m_remainingFireTicks = i;
}

void Entity::clearFire() {
    this->m_remainingFireTicks = 0;
}

void Entity::outOfWorld() {
    this->remove();
}

// void Entity::move(MoverType, double, double, double, bool) {} // maybe not

void Entity::updateDeltaAfterMove(Block* block, double oldX, double oldY, double oldZ, double& newX,
                                  double& newY, double& newZ) {
    if (newX != oldX)
        this->m_deltaMovementX = 0.0f;
    if (newZ != oldZ)
        this->m_deltaMovementZ = 0.0f;
    if (newY != oldY) {
        PIXBeginNamedEvent(0.0f, "Update entity after falling");
        block->updateEntityAfterFallOn(this->m_level, shared_from_this());
        PIXEndNamedEvent();
    }
}

void Entity::setLocationFromBoundingbox() {
    const AABB* tempAABB = this->getBoundingBox();
    this->m_x = (tempAABB->m_inX + tempAABB->m_axX) / 2.0;
    this->m_y = tempAABB->m_inY;
    this->m_z = (tempAABB->m_inZ + tempAABB->m_axZ) / 2.0;
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
        this->m_level->playSound(nullptr, this->m_x, this->m_y, this->m_z, sound, this->getSoundSource(),
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

void Entity::checkFallDamage(double fall, bool onGround, Block* block, const BlockPos& pos) {
    if (onGround) {
        if (this->m_fallDistance > 0.0f) {
            block->fallOn(this->m_level, pos, shared_from_this(), this->m_fallDistance);
            ++this->m_hardLandingsCount;  // hard enough to take fall damage
        }

        this->m_fallTicks = 0;
        this->m_fallDistance = 0.0f;
    } else if (fall < 0.0) {
        this->m_fallDistance -= (float)fall;
        ++this->m_fallTicks;
    }
}

AABB* Entity::getCollideBox() {
    return nullptr;
}

void Entity::burn(int howMuch) {
    if (!this->m_isImmuneToFire)
        this->hurt(DamageSource::IN_FIRE, howMuch);
}

Vec3* Entity::getViewVector(float partialTicks) {
    if (partialTicks == 1.0f) {
        return this->calculateViewVector(this->m_xRot, this->m_yRot);
    } else {
        return this->calculateViewVector(this->m_xRotO + ((this->m_xRot - this->m_xRotO) * partialTicks),
                                         this->m_yRotO + ((this->m_yRot - this->m_yRotO) * partialTicks));
    }
}
void Entity::readAdditionContructionTag(CompoundTag*) {}
void Entity::SetPositionLocked(bool) {}
void Entity::SetGlideCollisionDamage(bool) {}
void Entity::SetLiftForceModifier(double) {}
void Entity::onLoadedFromSave() {}
void Entity::setUsingItemFlag(bool) {}
void Entity::fjDebugCheckSmallIdLeaks() {}
