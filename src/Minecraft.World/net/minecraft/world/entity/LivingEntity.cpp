#include "net/minecraft/world/entity/LivingEntity.h"

#include "NX/Platform.h"
#include "net/minecraft/client/CGameNetworkManager.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/sounds/SoundEngine.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/MutableBlockPos.h"
#include "net/minecraft/network/PacketType.h"
#include "net/minecraft/network/protocol/game/ClientboundSoundPacket.h"
#include "net/minecraft/server/MinecraftServer.h"
#include "net/minecraft/server/players/PlayerList.h"
#include "net/minecraft/sounds/SoundEvent.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/effect/MobEffectInstance.h"
#include "net/minecraft/world/effect/MobEffects.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/entity/player/ServerPlayer.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/enchantment/EnchantmentHelper.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/chunk/LevelChunk.h"
#include "net/minecraft/world/level/gamemode/GameMode.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"
#include "net/minecraft/world/level/gamemode/minigames/glide/rules/ThermalAreaRuleDefinition.h"
#include "types.h"
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
        ++this->mBoundingBoxUpdateCount;
    }
    this->Entity::setBoundingBox(box);
}

void LivingEntity::dropEquipment(bool, int) {}
void LivingEntity::dropDeathLoot(bool, int) {}
void LivingEntity::hurtArmor(float) {}
void LivingEntity::hurtCurrentlyUsedShield(float) {}

void LivingEntity::travel(float x, float y, float z) {
    Player* player = this->isType(ePlayer) ? (Player*)this : nullptr;
    if (this->PositionLocked()) {
        this->mDeltaMovementX = 0;
        this->mDeltaMovementZ = 0;
        if (Minecraft::InMiniGame(EMiniGameId::TUMBLE, false)
            || Minecraft::InMiniGame(EMiniGameId::GLIDE, false))
            this->mDeltaMovementY = 0;
    }

    if (this->isEffectiveAi() || this->isControlledByLocalInstance()) {
        if (!this->isInWater() || (player && player->mAbilities.mIsFlying)) {
            if (!this->isInLava() || (player && player->mAbilities.mIsFlying)) {
                if (this->isFallFlying() && !this->PositionLocked()
                    && !CConsoleMinecraftApp::sInstance.IsAppPaused()) {
                    this->CheckThermalAreas();

                    double idk;
                    this->fallFlyingTravel(this->mDeltaMovementX, this->mDeltaMovementY,
                                           this->mDeltaMovementZ, this->getLookAngle(), this->mXRot,
                                           this->mFallDistance, idk, this->GetLiftForceModifier());

                    if (player && CConsoleMinecraftApp::sInstance.GetFirstMiniGameType() == GLIDE
                        && player->CheckPowerup((PowerupItems::eGlide_Timed_Powerup_ID)0)
                        && this->mDeltaMovementY < 0.0) {
                        this->move(SELF, this->mDeltaMovementX, this->mDeltaMovementY * 0.2,
                                   this->mDeltaMovementZ, false);
                    } else if (this->mAdditionalGlideVelocity + this->mAppliedLiftVelocity == 0.0) {
                        this->move(SELF, this->mDeltaMovementX, this->mDeltaMovementY, this->mDeltaMovementZ,
                                   false);
                    } else {
                        this->move(SELF, this->mDeltaMovementX,
                                   this->mAdditionalGlideVelocity + this->mAppliedLiftVelocity,
                                   this->mDeltaMovementZ, false);
                        if (this->mAppliedLiftVelocity != 0.0)
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
                        if (this->PositionLocked()) {
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

void LivingEntity::setAbsorptionAmount(float amount) {
    if (amount < 0.0F) {
        amount = 0.0F;
    }

    this->mAbsorptionAmount = amount;
}

void LivingEntity::onEnterCombat() {}
void LivingEntity::onLeaveCombat() {}
void LivingEntity::setRecordPlayingNearby(const BlockPos&, bool) {}

not_null_ptr<ItemInstance> LivingEntity::getUseItem() {
    return this->mUseItem;
}

// NON_MATCHING: Various issues, https://decomp.me/scratch/bm1rV
void LivingEntity::CheckThermalAreas() {
    SetLiftForceModifier(1.0);

    LevelGenerationOptions* levelGenerationOptions
        = CConsoleMinecraftApp::sInstance.getLevelGenerationOptions();
    if (!levelGenerationOptions)
        return;

    LevelRuleset* ruleset = levelGenerationOptions->getRequiredGameRules();
    int miniGameType = CConsoleMinecraftApp::sInstance.GetFirstMiniGameType();

    if (!ruleset)
        return;

    if (miniGameType != EMiniGameId::GLIDE)
        return;

    ThermalAreaRuleDefinition** activeThermal = nullptr;
    std::vector<ThermalAreaRuleDefinition*> thermalAreas;
    ruleset->getThermalAreas(&thermalAreas);

    for (auto it = thermalAreas.begin(); it != thermalAreas.end(); ++it) {
        if ((*it)->isActive() && (*it)->getConditionsMet(shared_from_this())
            && (*it)->getArea()->intersects(getSweptVolume())) {
            activeThermal = &*it;
            break;
        }
    }

    bool isInThermal = (activeThermal != nullptr);
    bool validBoostDirection = false;
    int boostDirection[2] = {0, 0};

    if (isInThermal) {
        // byte3F0 = true;
        if (mHasPendingThermalEntry) {
            mHasPendingThermalEntry = false;
            if ((*activeThermal)->getSpeedBoost() == 0.0) {
                if (mLevel->mIsLocal && isType(eLocalPlayer)) {
                    Minecraft* minecraft = Minecraft::GetInstance();
                    minecraft->mSoundEngine->playUI(SoundEvent::ENTER_THERMAL, 1.0f, 1.0f);
                }
                if (!mLevel->mIsLocal && isType(eServerPlayer)) {
                    std::shared_ptr<Packet> packet(
                        new ClientboundSoundPacket(ClientboundSoundPacket::ESoundInstances::_1,
                                                   SoundEvent::ENTER_THERMAL, 1.0f, 1.0f, false, getId()));
                    MinecraftServer::getInstance()->tryGetPlayers()->broadcast(
                        std::static_pointer_cast<ServerPlayer>(shared_from_this()), mX, mY, mZ, 30.0,
                        mDimensionId, packet);
                }
            }

            if ((*activeThermal)->getSpeedBoost() != 0.0) {
                if (mLevel->mIsLocal && isType(eLocalPlayer)) {
                    Minecraft* minecraft = Minecraft::GetInstance();
                    minecraft->mSoundEngine->playUI(SoundEvent::ENTER_BOOST, 1.0f, 1.0f);
                }
                if (!mLevel->mIsLocal && isType(eServerPlayer)) {
                    std::shared_ptr<Packet> packet(
                        new ClientboundSoundPacket(ClientboundSoundPacket::ESoundInstances::_1,
                                                   SoundEvent::ENTER_BOOST, 1.0f, 1.0f, false, getId()));
                    MinecraftServer::getInstance()->tryGetPlayers()->broadcast(
                        std::static_pointer_cast<ServerPlayer>(shared_from_this()), mX, mY, mZ, 30.0,
                        mDimensionId, packet);
                }
            }
        }

        SetLiftForceModifier((*activeThermal)->getLiftForceModifier());

        if (!mIsApplyingStaticLift) {
            double liftMod = (*activeThermal)->getStaticLift();
            if (liftMod != 0.0) {
                mIsApplyingLift = true;
                mLiftDurationTimer = 0;
            }
            mTargetLiftVelocity = (*activeThermal)->getStaticLift();
        }

        if ((*activeThermal)->getTargetHeight() > 0.0) {
            mIsApplyingStaticLift = true;
            mStaticLiftTargetHeight = (*activeThermal)->getTargetHeight();
        }

        mIsUpdraft = !((*activeThermal)->getStaticLift() < 0.0);

        if ((*activeThermal)->getSpeedBoost() > 0.0) {
            activateElytraSpeedBoost((*activeThermal)->getSpeedBoost());
            validBoostDirection = (*activeThermal)->setBoostMods(boostDirection[1], boostDirection[0]);
        }

        if (mThermalArea != *activeThermal && isType(eServerPlayer)) {
            std::shared_ptr<ServerPlayer> player = std::static_pointer_cast<ServerPlayer>(shared_from_this());
            player->GetGameMode()->RecordThermalEntered();
        }

        mThermalArea = *activeThermal;
    } else if (mThermalArea) {
        mHasPendingThermalEntry = true;
        if (!mLevel->mIsLocal) {
            mThermalArea->updateUseCount();
            mThermalArea = nullptr;
        }
    }

    if (mIsApplyingStaticLift) {
        if (mY >= mStaticLiftTargetHeight || mHasVerticalCollision) {
            mIsApplyingStaticLift = false;
            mIsApplyingLift = false;
        } else {
            mIsApplyingLift = true;
        }
    }

    if (mIsApplyingLift) {
        if (mAppliedLiftVelocity == 0.0 && mDeltaMovementY != 0.0) {
            mAppliedLiftVelocity = mDeltaMovementY;
        }
        if (mIsUpdraft) {
            if (mAppliedLiftVelocity < mTargetLiftVelocity) {
                mAppliedLiftVelocity
                    = mAppliedLiftVelocity
                      + ((mTargetLiftVelocity - mAppliedLiftVelocity) / mTargetLiftVelocity) * 0.1;
            }
        } else {
            if (mAppliedLiftVelocity > mTargetLiftVelocity) {
                mAppliedLiftVelocity
                    = mAppliedLiftVelocity
                      + ((mTargetLiftVelocity - mAppliedLiftVelocity) / mTargetLiftVelocity) * -0.1;
            }
        }

        if (!mIsApplyingStaticLift) {
            mLiftDurationTimer++;
            if (mLiftDurationTimer > 20) {
                mIsApplyingLift = false;
                mLiftDurationTimer = 0;
            }
        }
    } else if (mIsUpdraft) {
        mAppliedLiftVelocity = mAppliedLiftVelocity > 0.0 ? mAppliedLiftVelocity - 0.025 : 0.0;
    } else {
        mAppliedLiftVelocity = mAppliedLiftVelocity < 0.0 ? mAppliedLiftVelocity + 0.025 : 0.0;
    }

    if (mIsSpeedBoosting) {
        double horizSpeed = Mth::sqrt(mDeltaMovementX * mDeltaMovementX + mDeltaMovementZ * mDeltaMovementZ);
        if (horizSpeed < mTargetBoostSpeed) {
            if (validBoostDirection) {
                double deltaX = mDeltaMovementX;
                double absX = Mth::abs(deltaX);
                int boostX = boostDirection[1];

                deltaX += absX * 0.1 * boostX;
                mDeltaMovementX = deltaX;

                double deltaZ = mDeltaMovementZ;
                double absZ = Mth::abs(deltaZ);
                int boostZ = boostDirection[0];

                deltaZ += absZ * 0.1 * boostZ;
                mDeltaMovementZ = deltaZ;

                if (deltaX * boostX < 0.0 || deltaZ * boostZ < 0.0) {
                    mIsSpeedBoosting = false;
                }
            } else {
                mDeltaMovementX *= 1.1;
                mDeltaMovementZ *= 1.1;
            }
        } else {
            mIsSpeedBoosting = false;
        }
    }
}
