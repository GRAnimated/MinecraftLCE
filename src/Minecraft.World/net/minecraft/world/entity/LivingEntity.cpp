#include "net/minecraft/world/entity/LivingEntity.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CGameNetworkManager.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/effect/MobEffectInstance.h"
#include "net/minecraft/world/effect/MobEffects.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/item/enchantment/EnchantmentHelper.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"
#include <cmath>
#include <memory>

eINSTANCEOF LivingEntity::GetType() {
    return eLivingEntity;
}
void LivingEntity::setBoundingBox(AABB* box) {
    const int newMinX = Mth::floor(box->min.x);
    const int newMaxX = Mth::floor(box->max.x);
    const int newMinY = Mth::floor(box->min.y);
    const int newMaxY = Mth::floor(box->max.y);
    const int newMinZ = Mth::floor(box->min.z);
    const int newMaxZ = Mth::floor(box->max.z);

    const int oldMinX = this->mMinX;
    const int oldMaxX = this->mMaxX;
    const int oldMinY = this->mMinY;
    const int oldMaxY = this->mMaxY;
    const int oldMinZ = this->mMinZ;
    const int oldMaxZ = this->mMaxZ;

    this->mMinX = newMinX;
    this->mMaxX = newMaxX;
    this->mMinY = newMinY;
    this->mMaxY = newMaxY;
    this->mMinZ = newMinZ;
    this->mMaxZ = newMaxZ;

    if (newMinX != oldMinX || newMaxX != oldMaxX || newMinY != oldMinY || newMaxY != oldMaxY
        || newMinZ != oldMinZ || newMaxZ != oldMaxZ) {
        ++this->dword50C;
    }
    this->Entity::setBoundingBox(box);
}

void LivingEntity::dropEquipment(bool, int) {}
void LivingEntity::dropDeathLoot(bool, int) {}
void LivingEntity::hurtArmor(float) {}
void LivingEntity::hurtCurrentlyUsedShield(float) {}
void LivingEntity::travel(float x, float y, float z) {
    Player* player = this->isType(ePlayer) ? (Player*)this : nullptr;
    if (this->PositionLocked_4()) {
        this->mDeltaMovementX = 0;
        this->mDeltaMovementZ = 0;
        if (Minecraft::InMiniGame(EMiniGameId::TUMBLE, false)
            || Minecraft::InMiniGame(EMiniGameId::GLIDE, false))
            this->mDeltaMovementY = 0;
    }

    if (this->isEffectiveAi() || this->isControlledByLocalInstance()) {
        if (!this->isInWater() || (player && player->mAbilities.mIsFlying)) {
            if (!this->isInLava() || (player && player->mAbilities.mIsFlying)) {
                if (this->isFallFlying() && !this->PositionLocked_4()
                    && !CConsoleMinecraftApp::sInstance.IsAppPaused()) {
                    this->CheckThermalAreas();

                    double idk;
                    this->fallFlyingTravel(this->mDeltaMovementX, this->mDeltaMovementY,
                                           this->mDeltaMovementZ, this->getLookAngle(), this->mXRot,
                                           this->mFallDistance, idk, this->GetLiftForceModifier_4());

                    if (player && CConsoleMinecraftApp::sInstance.GetFirstMiniGameType() == GLIDE
                        && player->CheckPowerup((PowerupItems::eGlide_Timed_Powerup_ID)0)
                        && this->mDeltaMovementY < 0.0) {
                        this->move(SELF, this->mDeltaMovementX, this->mDeltaMovementY * 0.2,
                                   this->mDeltaMovementZ, false);
                    } else if (this->double398 + this->double3A0 == 0.0) {
                        this->move(SELF, this->mDeltaMovementX, this->mDeltaMovementY, this->mDeltaMovementZ,
                                   false);
                    } else {
                        this->move(SELF, this->mDeltaMovementX, this->double398 + this->double3A0,
                                   this->mDeltaMovementZ, false);
                        if (this->double3A0 != 0.0)
                            this->mDeltaMovementY = 0.0f;
                    }
                } else {
                    MutableBlockPos blockPos = MutableBlockPos(
                        Mth::floor(this->mX), Mth::floor(this->getBoundingBox()->min.y - 1.0),
                        Mth::floor(this->mZ));
                    float finalFriction = 0.91f;
                    if (this->mOnGround) {
                        PIXBeginNamedEvent(0.0, "Get friction 1");
                        Block* block = this->mLevel->getBlockState(blockPos)->getBlock();
                        block = this->IsCreativeFlying()
                                        && (block == Blocks::ICE || block == Blocks::PACKED_ICE
                                            || block == Blocks::FROSTED_ICE || block == Blocks::SLIME) ?
                                    Blocks::STONE :
                                    this->mLevel->getBlockState(blockPos)->getBlock();
                        finalFriction = block->mFriction * 0.91f;
                        PIXEndNamedEvent();
                    }

                    float tempSpeed = 0.16277f / (finalFriction * finalFriction * finalFriction);
                    float finalSpeed;
                    PIXBeginNamedEvent(0.0, "Update speed");
                    if (this->mOnGround) {
                        finalSpeed = tempSpeed * this->getSpeed();
                    } else if (this->GetType() == eWitherBoss) {
                        finalSpeed = tempSpeed * this->mFlyingSpeed;
                    } else {
                        finalSpeed = this->mFlyingSpeed;
                    }
                    PIXEndNamedEvent();

                    PIXBeginNamedEvent(0.0, "moveRelative");
                    Entity::moveRelative(x, y, z, finalSpeed);
                    PIXEndNamedEvent();

                    finalFriction = 0.91f;
                    if (this->mOnGround) {
                        PIXBeginNamedEvent(0.0, "Get friction 2");
                        blockPos.set(Mth::floor(this->mX), Mth::floor(this->getBoundingBox()->min.y - 1.0),
                                     Mth::floor(this->mZ));
                        Block* block = this->mLevel->getBlockState(blockPos)->getBlock();
                        block = this->IsCreativeFlying()
                                        && (block == Blocks::ICE || block == Blocks::PACKED_ICE
                                            || block == Blocks::FROSTED_ICE || block == Blocks::SLIME) ?
                                    Blocks::STONE :
                                    this->mLevel->getBlockState(blockPos)->getBlock();
                        finalFriction = block->mFriction * 0.91;
                        PIXEndNamedEvent();
                    }
                    if (this->onLadder()) {
                        this->mDeltaMovementX = Mth::clamp(this->mDeltaMovementX, -0.15, 0.15);
                        this->mDeltaMovementZ = Mth::clamp(this->mDeltaMovementZ, -0.15, 0.15);
                        this->mFallDistance = 0.0F;

                        if (this->mDeltaMovementY < -0.15)
                            this->mDeltaMovementY = -0.15;

                        if (this->isSneaking() && this->isType(ePlayer) && this->mDeltaMovementY < 0.0)
                            this->mDeltaMovementY = 0.0;
                    }

                    PIXBeginNamedEvent(0.0, "move");
                    this->move(SELF, this->mDeltaMovementX, this->mDeltaMovementY, this->mDeltaMovementZ,
                               false);
                    PIXEndNamedEvent();

                    if (this->mHasHorizontalCollision && this->onLadder())
                        this->mDeltaMovementY = 0.2;

                    PIXBeginNamedEvent(0.0, "Update y delta");
                    if (this->hasEffect(MobEffects::LEVITATION)) {
                        this->mDeltaMovementY
                            += (0.05 * (this->getEffect(MobEffects::LEVITATION)->getAmplifier() + 1)
                                - this->mDeltaMovementY)
                               * 0.2;
                    } else {
                        blockPos.set(Mth::floor(this->mX), 0, Mth::floor(this->mZ));
                        bool v67 = this->mLevel->mIsLocal ? CGameNetworkManager::sInstance.IsHost() : true;
                        if (this->PositionLocked_4()) {
                            if (Minecraft::InMiniGame(TUMBLE, false) || Minecraft::InMiniGame(GLIDE, false)) {
                                this->mDeltaMovementY = 0;
                            }
                        }

                        if (v67
                            || (this->mLevel->hasChunkAt(blockPos)
                                && this->mLevel->getChunkAt(blockPos)->isTerrainPopulated())) {
                            if (!this->isNoGravity()) {
                                this->mDeltaMovementY -= 0.8f;
                            }
                        }
                    }

                    PIXEndNamedEvent();
                    this->mDeltaMovementY *= 0.98;
                    this->mDeltaMovementX *= finalFriction;
                    this->mDeltaMovementZ *= finalFriction;
                }

            } else {
                PIXBeginNamedEvent(0.0, "Travel in lava");
                double YBefore = this->mY;
                this->moveRelative(x, y, z, 0.02f);
                this->move(SELF, this->mDeltaMovementX, this->mDeltaMovementY, this->mDeltaMovementZ, false);

                this->mDeltaMovementX *= 0.5;
                this->mDeltaMovementY *= 0.5;
                this->mDeltaMovementZ *= 0.5;

                if (!this->isNoGravity()) {
                    this->mDeltaMovementY -= 0.02;
                }

                if (this->mHasHorizontalCollision
                    && this->isFree(this->mDeltaMovementX,
                                    YBefore + this->mDeltaMovementY + 0.600000024 - this->mY,
                                    this->mDeltaMovementZ)) {
                    this->mDeltaMovementY = 0.300000012;
                }
                PIXEndNamedEvent();
            }
        } else {
            PIXBeginNamedEvent(0.0, "Travel in water");
            double d0 = this->mY;
            float waterSlow = this->getWaterSlowDown();
            float f2 = 0.02f;
            float depthStrider = EnchantmentHelper::getDepthStrider(
                std::static_pointer_cast<LivingEntity>(shared_from_this()));

            if (depthStrider > 3.0f) {
                depthStrider = 3.0f;
            }

            if (depthStrider > 0.0f) {
                waterSlow += (0.54600006f - waterSlow) * depthStrider / 3.0f;
                f2 += (this->getSpeed() - f2) * depthStrider / 3.0f;
            }

            this->moveRelative(x, y, z, f2);
            this->move(SELF, this->mDeltaMovementX, this->mDeltaMovementY, this->mDeltaMovementZ, false);
            this->mDeltaMovementX *= waterSlow;
            this->mDeltaMovementY *= 0.800000012;
            this->mDeltaMovementZ *= waterSlow;

            if (!this->isNoGravity()) {
                this->mDeltaMovementY -= 0.02;
            }

            if (this->mHasHorizontalCollision
                && this->isFree(this->mDeltaMovementX, this->mDeltaMovementY + 0.600000024 - this->mY + d0,
                                this->mDeltaMovementZ)) {
                this->mDeltaMovementY = 0.300000012;
            }
            PIXEndNamedEvent();
        }
    }

    this->updateModelAnimation();
}

void LivingEntity::serverAiStep() {}
float LivingEntity::getAttackAnim(float a2) {
    float v3 = this->mAttackAnim - this->mOAttackAnim;
    if (v3 < 0.0)
        v3 = v3 + 1.0;

    return mOAttackAnim + v3 * a2;
}

float LivingEntity::getAbsorptionAmount() {
    return this->mAbsorptionAmount;
}

// NON_MATCHING | Score: 805 (lower is better)
// ???
// some weird fmaxf issue
void LivingEntity::setAbsorptionAmount(float amount) {
    this->mAbsorptionAmount = fmaxf(amount, 0.0);
}
void LivingEntity::onEnterCombat() {}
void LivingEntity::onLeaveCombat() {}
void LivingEntity::setRecordPlayingNearby(const BlockPos&, bool) {}
