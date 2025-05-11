#include "Minecraft.Client/CGameNetworkManager.h"
#include "Minecraft.Client/CMinecraftApp.h"
#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.Client/platform/NX/Platform.h"
#include "Minecraft.World/eINSTANCEOF.h"
#include "Minecraft.World/enchantment/EnchantmentHelper.h"
#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.World/entity/LivingEntity.h"
#include "Minecraft.World/entity/mob/MobEffectInstance.h"
#include "Minecraft.World/entity/mob/MobEffects.h"
#include "Minecraft.World/entity/player/Player.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/state/BlockState.h"
#include "Minecraft.World/level/chunk/LevelChunk.h"
#include "Minecraft.World/level/gamemode/minigames/MiniGameDef.h"
#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Util/Mth.h"
#include <memory>

void LivingEntity::travel(float x, float y, float z) {
    Player* player = this->isType(ePlayer) ? (Player*)this : nullptr;
    if (this->PositionLocked_4()) {
        this->mDeltaMovement.x = 0;
        this->mDeltaMovement.z = 0;
        if (Minecraft::InMiniGame(EMiniGameId::TUMBLE, false)
            || Minecraft::InMiniGame(EMiniGameId::GLIDE, false))
            this->mDeltaMovement.y = 0;
    }

    if (this->isEffectiveAi() || this->isControlledByLocalInstance()) {
        if (!this->isInWater() || (player && player->mAbilities.mIsFlying)) {
            if (!this->isInLava() || (player && player->mAbilities.mIsFlying)) {
                if (this->isFallFlying() && !this->PositionLocked_4()
                    && !CConsoleMinecraftApp::sInstance.IsAppPaused()) {
                    this->CheckThermalAreas();

                    double idk;
                    this->fallFlyingTravel(this->mDeltaMovement.x, this->mDeltaMovement.y,
                                           this->mDeltaMovement.z, this->getLookAngle(), this->mXRot,
                                           this->mFallDistance, idk, this->GetLiftForceModifier_4());

                    if (player && CConsoleMinecraftApp::sInstance.GetFirstMiniGameType() == GLIDE
                        && player->CheckPowerup((PowerupItems::eGlide_Timed_Powerup_ID)0)
                        && this->mDeltaMovement.y < 0.0) {
                        this->move(SELF, this->mDeltaMovement.x, this->mDeltaMovement.y * 0.2,
                                   this->mDeltaMovement.z, false);
                    } else if (this->double398 + this->double3A0 == 0.0) {
                        this->move(SELF, this->mDeltaMovement.x, this->mDeltaMovement.y,
                                   this->mDeltaMovement.z, false);
                    } else {
                        this->move(SELF, this->mDeltaMovement.x, this->double398 + this->double3A0,
                                   this->mDeltaMovement.z, false);
                        if (this->double3A0 != 0.0)
                            this->mDeltaMovement.y = 0.0f;
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
                        this->mDeltaMovement.x = Mth::clamp(this->mDeltaMovement.x, -0.15, 0.15);
                        this->mDeltaMovement.z = Mth::clamp(this->mDeltaMovement.z, -0.15, 0.15);
                        this->mFallDistance = 0.0F;

                        if (this->mDeltaMovement.y < -0.15)
                            this->mDeltaMovement.y = -0.15;

                        if (this->isSneaking() && this->isType(ePlayer) && this->mDeltaMovement.y < 0.0)
                            this->mDeltaMovement.y = 0.0;
                    }

                    PIXBeginNamedEvent(0.0, "move");
                    this->move(SELF, this->mDeltaMovement.x, this->mDeltaMovement.y, this->mDeltaMovement.z,
                               false);
                    PIXEndNamedEvent();

                    if (this->mHorizontalCollision && this->onLadder())
                        this->mDeltaMovement.y = 0.2;

                    PIXBeginNamedEvent(0.0, "Update y delta");
                    if (this->hasEffect(MobEffects::LEVITATION)) {
                        this->mDeltaMovement.y
                            += (0.05 * (this->getEffect(MobEffects::LEVITATION)->getAmplifier() + 1)
                                - this->mDeltaMovement.y)
                               * 0.2;
                    } else {
                        blockPos.set(Mth::floor(this->mX), 0, Mth::floor(this->mZ));
                        bool v67 = this->mLevel->mIsLocal ? CGameNetworkManager::sInstance->IsHost() : true;
                        if (this->PositionLocked_4()) {
                            if (Minecraft::InMiniGame(TUMBLE, false) || Minecraft::InMiniGame(GLIDE, false)) {
                                this->mDeltaMovement.y = 0;
                            }
                        }

                        if (v67
                            || (this->mLevel->hasChunkAt(blockPos)
                                && this->mLevel->getChunkAt(blockPos)->isTerrainPopulated())) {
                            if (!this->isNoGravity()) {
                                this->mDeltaMovement.y -= 0.8f;
                            }
                        }
                    }

                    PIXEndNamedEvent();
                    this->mDeltaMovement.y *= 0.98;
                    this->mDeltaMovement.x *= finalFriction;
                    this->mDeltaMovement.z *= finalFriction;
                }

            } else {
                PIXBeginNamedEvent(0.0, "Travel in lava");
                double YBefore = this->mY;
                this->moveRelative(x, y, z, 0.02f);
                this->move(SELF, this->mDeltaMovement.x, this->mDeltaMovement.y, this->mDeltaMovement.z,
                           false);

                this->mDeltaMovement.x *= 0.5;
                this->mDeltaMovement.y *= 0.5;
                this->mDeltaMovement.z *= 0.5;

                if (!this->isNoGravity()) {
                    this->mDeltaMovement.y -= 0.02;
                }

                if (this->mHorizontalCollision
                    && this->isFree(this->mDeltaMovement.x,
                                    YBefore + this->mDeltaMovement.y + 0.600000024 - this->mY,
                                    this->mDeltaMovement.z)) {
                    this->mDeltaMovement.y = 0.300000012;
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
            this->move(SELF, this->mDeltaMovement.x, this->mDeltaMovement.y, this->mDeltaMovement.z, false);
            this->mDeltaMovement.x *= waterSlow;
            this->mDeltaMovement.y *= 0.800000012;
            this->mDeltaMovement.z *= waterSlow;

            if (!this->isNoGravity()) {
                this->mDeltaMovement.y -= 0.02;
            }

            if (this->mHorizontalCollision
                && this->isFree(this->mDeltaMovement.x, this->mDeltaMovement.y + 0.600000024 - this->mY + d0,
                                this->mDeltaMovement.z)) {
                this->mDeltaMovement.y = 0.300000012;
            }
            PIXEndNamedEvent();
        }
    }

    this->updateModelAnimation();
}