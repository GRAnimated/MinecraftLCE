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
    const int newMinX = Mth::floor(box->m_inX);
    const int newMaxX = Mth::floor(box->m_axX);
    const int newMinY = Mth::floor(box->m_inY);
    const int newMaxY = Mth::floor(box->m_axY);
    const int newMinZ = Mth::floor(box->m_inZ);
    const int newMaxZ = Mth::floor(box->m_axZ);

    const int oldMinX = this->m_minX;
    const int oldMaxX = this->m_maxX;
    const int oldMinY = this->m_minY;
    const int oldMaxY = this->m_maxY;
    const int oldMinZ = this->m_minZ;
    const int oldMaxZ = this->m_maxZ;

    this->m_minX = newMinX;
    this->m_maxX = newMaxX;
    this->m_minY = newMinY;
    this->m_maxY = newMaxY;
    this->m_minZ = newMinZ;
    this->m_maxZ = newMaxZ;

    if (newMinX != oldMinX || newMaxX != oldMaxX || newMinY != oldMinY || newMaxY != oldMaxY
        || newMinZ != oldMinZ || newMaxZ != oldMaxZ) {
        ++this->m_boundingBoxUpdateCount;
    }
    this->Entity::setBoundingBox(box);
}

void LivingEntity::dropEquipment(bool, int) {}
void LivingEntity::dropDeathLoot(bool, int) {}
void LivingEntity::hurtArmor(float) {}
void LivingEntity::hurtCurrentlyUsedShield(float) {}

// NON_MATCHING: a lot of stuff
void LivingEntity::travel(float x, float y, float z) {
    Player* player = this->isType(ePlayer) ? (Player*)this : nullptr;
    if (this->PositionLocked()) {
        this->m_deltaMovementX = 0;
        this->m_deltaMovementZ = 0;
        if (Minecraft::InMiniGame(EMiniGameId::TUMBLE, false)
            || Minecraft::InMiniGame(EMiniGameId::GLIDE, false))
            this->m_deltaMovementY = 0;
    }

    if (this->isEffectiveAi() || this->isControlledByLocalInstance()) {
        if (!this->isInWater() || (player && player->m_abilities.m_isFlying)) {
            if (!this->isInLava() || (player && player->m_abilities.m_isFlying)) {
                if (this->isFallFlying() && !this->PositionLocked()
                    && !CConsoleMinecraftApp::sInstance.IsAppPaused()) {
                    this->CheckThermalAreas();

                    double idk;
                    this->fallFlyingTravel(this->m_deltaMovementX, this->m_deltaMovementY,
                                           this->m_deltaMovementZ, this->getLookAngle(), this->m_xRot,
                                           this->m_fallDistance, idk, this->GetLiftForceModifier());

                    if (player && CConsoleMinecraftApp::sInstance.GetFirstMiniGameType() == GLIDE
                        && player->CheckPowerup((PowerupItems::eGlide_Timed_Powerup_ID)0)
                        && this->m_deltaMovementY < 0.0) {
                        this->move(SELF, this->m_deltaMovementX, this->m_deltaMovementY * 0.2,
                                   this->m_deltaMovementZ, false);
                    } else if (this->m_additionalGlideVelocity + this->m_appliedLiftVelocity == 0.0) {
                        this->move(SELF, this->m_deltaMovementX, this->m_deltaMovementY,
                                   this->m_deltaMovementZ, false);
                    } else {
                        this->move(SELF, this->m_deltaMovementX,
                                   this->m_additionalGlideVelocity + this->m_appliedLiftVelocity,
                                   this->m_deltaMovementZ, false);
                        if (this->m_appliedLiftVelocity != 0.0)
                            this->m_deltaMovementY = 0.0f;
                    }
                } else {
                    MutableBlockPos blockPos = MutableBlockPos(
                        Mth::floor(this->m_x), Mth::floor(this->getBoundingBox()->m_inY - 1.0),
                        Mth::floor(this->m_z));
                    float finalFriction = 0.91f;
                    if (this->m_onGround) {
                        PIXBeginNamedEvent(0.0, "Get friction 1");
                        Block* block = this->m_level->getBlockState(blockPos)->getBlock();
                        block = this->IsCreativeFlying()
                                        && (block == Blocks::ICE || block == Blocks::PACKED_ICE
                                            || block == Blocks::FROSTED_ICE || block == Blocks::SLIME) ?
                                    Blocks::STONE :
                                    this->m_level->getBlockState(blockPos)->getBlock();
                        finalFriction = block->m_friction * 0.91f;
                        PIXEndNamedEvent();
                    }

                    float tempSpeed = 0.16277f / (finalFriction * finalFriction * finalFriction);
                    float finalSpeed;
                    PIXBeginNamedEvent(0.0, "Update speed");
                    if (this->m_onGround) {
                        finalSpeed = tempSpeed * this->getSpeed();
                    } else if (this->GetType() == eWitherBoss) {
                        finalSpeed = tempSpeed * this->m_flyingSpeed;
                    } else {
                        finalSpeed = this->m_flyingSpeed;
                    }
                    PIXEndNamedEvent();

                    PIXBeginNamedEvent(0.0, "moveRelative");
                    Entity::moveRelative(x, y, z, finalSpeed);
                    PIXEndNamedEvent();

                    finalFriction = 0.91f;
                    if (this->m_onGround) {
                        PIXBeginNamedEvent(0.0, "Get friction 2");
                        blockPos.set(Mth::floor(this->m_x), Mth::floor(this->getBoundingBox()->m_inY - 1.0),
                                     Mth::floor(this->m_z));
                        Block* block = this->m_level->getBlockState(blockPos)->getBlock();
                        block = this->IsCreativeFlying()
                                        && (block == Blocks::ICE || block == Blocks::PACKED_ICE
                                            || block == Blocks::FROSTED_ICE || block == Blocks::SLIME) ?
                                    Blocks::STONE :
                                    this->m_level->getBlockState(blockPos)->getBlock();
                        finalFriction = block->m_friction * 0.91;
                        PIXEndNamedEvent();
                    }
                    if (this->onLadder()) {
                        this->m_deltaMovementX = Mth::clamp(this->m_deltaMovementX, -0.15, 0.15);
                        this->m_deltaMovementZ = Mth::clamp(this->m_deltaMovementZ, -0.15, 0.15);
                        this->m_fallDistance = 0.0F;

                        if (this->m_deltaMovementY < -0.15)
                            this->m_deltaMovementY = -0.15;

                        if (this->isSneaking() && this->isType(ePlayer) && this->m_deltaMovementY < 0.0)
                            this->m_deltaMovementY = 0.0;
                    }

                    PIXBeginNamedEvent(0.0, "move");
                    this->move(SELF, this->m_deltaMovementX, this->m_deltaMovementY, this->m_deltaMovementZ,
                               false);
                    PIXEndNamedEvent();

                    if (this->m_hasHorizontalCollision && this->onLadder())
                        this->m_deltaMovementY = 0.2;

                    PIXBeginNamedEvent(0.0, "Update y delta");
                    if (this->hasEffect(MobEffects::LEVITATION)) {
                        this->m_deltaMovementY
                            += (0.05 * (this->getEffect(MobEffects::LEVITATION)->getAmplifier() + 1)
                                - this->m_deltaMovementY)
                               * 0.2;
                    } else {
                        blockPos.set(Mth::floor(this->m_x), 0, Mth::floor(this->m_z));
                        bool v67 = this->m_level->m_isLocal ? CGameNetworkManager::sInstance.IsHost() : true;
                        if (this->PositionLocked()) {
                            if (Minecraft::InMiniGame(TUMBLE, false) || Minecraft::InMiniGame(GLIDE, false)) {
                                this->m_deltaMovementY = 0;
                            }
                        }

                        if (v67
                            || (this->m_level->hasChunkAt(blockPos)
                                && this->m_level->getChunkAt(blockPos)->isTerrainPopulated())) {
                            if (!this->isNoGravity()) {
                                this->m_deltaMovementY -= 0.8f;
                            }
                        }
                    }

                    PIXEndNamedEvent();
                    this->m_deltaMovementY *= 0.98;
                    this->m_deltaMovementX *= finalFriction;
                    this->m_deltaMovementZ *= finalFriction;
                }

            } else {
                PIXBeginNamedEvent(0.0, "Travel in lava");
                double YBefore = this->m_y;
                this->moveRelative(x, y, z, 0.02f);
                this->move(SELF, this->m_deltaMovementX, this->m_deltaMovementY, this->m_deltaMovementZ,
                           false);

                this->m_deltaMovementX *= 0.5;
                this->m_deltaMovementY *= 0.5;
                this->m_deltaMovementZ *= 0.5;

                if (!this->isNoGravity()) {
                    this->m_deltaMovementY -= 0.02;
                }

                if (this->m_hasHorizontalCollision
                    && this->isFree(this->m_deltaMovementX,
                                    YBefore + this->m_deltaMovementY + 0.600000024 - this->m_y,
                                    this->m_deltaMovementZ)) {
                    this->m_deltaMovementY = 0.300000012;
                }
                PIXEndNamedEvent();
            }
        } else {
            PIXBeginNamedEvent(0.0, "Travel in water");
            double d0 = this->m_y;
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
            this->move(SELF, this->m_deltaMovementX, this->m_deltaMovementY, this->m_deltaMovementZ, false);
            this->m_deltaMovementX *= waterSlow;
            this->m_deltaMovementY *= 0.800000012;
            this->m_deltaMovementZ *= waterSlow;

            if (!this->isNoGravity()) {
                this->m_deltaMovementY -= 0.02;
            }

            if (this->m_hasHorizontalCollision
                && this->isFree(this->m_deltaMovementX, this->m_deltaMovementY + 0.600000024 - this->m_y + d0,
                                this->m_deltaMovementZ)) {
                this->m_deltaMovementY = 0.300000012;
            }
            PIXEndNamedEvent();
        }
    }

    this->updateModelAnimation();
}

void LivingEntity::serverAiStep() {}
float LivingEntity::getAttackAnim(float a2) {
    float v3 = this->m_attackAnim - this->m_oAttackAnim;
    if (v3 < 0.0)
        v3 = v3 + 1.0;

    return m_oAttackAnim + v3 * a2;
}

float LivingEntity::getAbsorptionAmount() {
    return this->m_absorptionAmount;
}

void LivingEntity::setAbsorptionAmount(float amount) {
    if (amount < 0.0F) {
        amount = 0.0F;
    }

    this->m_absorptionAmount = amount;
}

void LivingEntity::onEnterCombat() {}
void LivingEntity::onLeaveCombat() {}
void LivingEntity::setRecordPlayingNearby(const BlockPos&, bool) {}

not_null_ptr<ItemInstance> LivingEntity::getUseItem() {
    return this->m_useItem;
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
        if (m_hasPendingThermalEntry) {
            m_hasPendingThermalEntry = false;
            if ((*activeThermal)->getSpeedBoost() == 0.0) {
                if (m_level->m_isLocal && isType(eLocalPlayer)) {
                    Minecraft* minecraft = Minecraft::GetInstance();
                    minecraft->m_soundEngine->playUI(SoundEvent::ENTER_THERMAL, 1.0f, 1.0f);
                }
                if (!m_level->m_isLocal && isType(eServerPlayer)) {
                    std::shared_ptr<Packet> packet(
                        new ClientboundSoundPacket(ClientboundSoundPacket::ESoundInstances::_1,
                                                   SoundEvent::ENTER_THERMAL, 1.0f, 1.0f, false, getId()));
                    MinecraftServer::getInstance()->tryGetPlayers()->broadcast(
                        std::static_pointer_cast<ServerPlayer>(shared_from_this()), m_x, m_y, m_z, 30.0,
                        m_dimensionId, packet);
                }
            }

            if ((*activeThermal)->getSpeedBoost() != 0.0) {
                if (m_level->m_isLocal && isType(eLocalPlayer)) {
                    Minecraft* minecraft = Minecraft::GetInstance();
                    minecraft->m_soundEngine->playUI(SoundEvent::ENTER_BOOST, 1.0f, 1.0f);
                }
                if (!m_level->m_isLocal && isType(eServerPlayer)) {
                    std::shared_ptr<Packet> packet(
                        new ClientboundSoundPacket(ClientboundSoundPacket::ESoundInstances::_1,
                                                   SoundEvent::ENTER_BOOST, 1.0f, 1.0f, false, getId()));
                    MinecraftServer::getInstance()->tryGetPlayers()->broadcast(
                        std::static_pointer_cast<ServerPlayer>(shared_from_this()), m_x, m_y, m_z, 30.0,
                        m_dimensionId, packet);
                }
            }
        }

        SetLiftForceModifier((*activeThermal)->getLiftForceModifier());

        if (!m_isApplyingStaticLift) {
            double liftMod = (*activeThermal)->getStaticLift();
            if (liftMod != 0.0) {
                m_isApplyingLift = true;
                m_liftDurationTimer = 0;
            }
            m_targetLiftVelocity = (*activeThermal)->getStaticLift();
        }

        if ((*activeThermal)->getTargetHeight() > 0.0) {
            m_isApplyingStaticLift = true;
            m_staticLiftTargetHeight = (*activeThermal)->getTargetHeight();
        }

        m_isUpdraft = !((*activeThermal)->getStaticLift() < 0.0);

        if ((*activeThermal)->getSpeedBoost() > 0.0) {
            activateElytraSpeedBoost((*activeThermal)->getSpeedBoost());
            validBoostDirection = (*activeThermal)->setBoostMods(boostDirection[1], boostDirection[0]);
        }

        if (m_thermalArea != *activeThermal && isType(eServerPlayer)) {
            std::shared_ptr<ServerPlayer> player = std::static_pointer_cast<ServerPlayer>(shared_from_this());
            player->GetGameMode()->RecordThermalEntered();
        }

        m_thermalArea = *activeThermal;
    } else if (m_thermalArea) {
        m_hasPendingThermalEntry = true;
        if (!m_level->m_isLocal) {
            m_thermalArea->updateUseCount();
            m_thermalArea = nullptr;
        }
    }

    if (m_isApplyingStaticLift) {
        if (m_y >= m_staticLiftTargetHeight || m_hasVerticalCollision) {
            m_isApplyingStaticLift = false;
            m_isApplyingLift = false;
        } else {
            m_isApplyingLift = true;
        }
    }

    if (m_isApplyingLift) {
        if (m_appliedLiftVelocity == 0.0 && m_deltaMovementY != 0.0) {
            m_appliedLiftVelocity = m_deltaMovementY;
        }
        if (m_isUpdraft) {
            if (m_appliedLiftVelocity < m_targetLiftVelocity) {
                m_appliedLiftVelocity
                    = m_appliedLiftVelocity
                      + ((m_targetLiftVelocity - m_appliedLiftVelocity) / m_targetLiftVelocity) * 0.1;
            }
        } else {
            if (m_appliedLiftVelocity > m_targetLiftVelocity) {
                m_appliedLiftVelocity
                    = m_appliedLiftVelocity
                      + ((m_targetLiftVelocity - m_appliedLiftVelocity) / m_targetLiftVelocity) * -0.1;
            }
        }

        if (!m_isApplyingStaticLift) {
            m_liftDurationTimer++;
            if (m_liftDurationTimer > 20) {
                m_isApplyingLift = false;
                m_liftDurationTimer = 0;
            }
        }
    } else if (m_isUpdraft) {
        m_appliedLiftVelocity = m_appliedLiftVelocity > 0.0 ? m_appliedLiftVelocity - 0.025 : 0.0;
    } else {
        m_appliedLiftVelocity = m_appliedLiftVelocity < 0.0 ? m_appliedLiftVelocity + 0.025 : 0.0;
    }

    if (m_isSpeedBoosting) {
        double horizSpeed
            = Mth::sqrt(m_deltaMovementX * m_deltaMovementX + m_deltaMovementZ * m_deltaMovementZ);
        if (horizSpeed < m_targetBoostSpeed) {
            if (validBoostDirection) {
                double deltaX = m_deltaMovementX;
                double absX = Mth::abs(deltaX);
                int boostX = boostDirection[1];

                deltaX += absX * 0.1 * boostX;
                m_deltaMovementX = deltaX;

                double deltaZ = m_deltaMovementZ;
                double absZ = Mth::abs(deltaZ);
                int boostZ = boostDirection[0];

                deltaZ += absZ * 0.1 * boostZ;
                m_deltaMovementZ = deltaZ;

                if (deltaX * boostX < 0.0 || deltaZ * boostZ < 0.0) {
                    m_isSpeedBoosting = false;
                }
            } else {
                m_deltaMovementX *= 1.1;
                m_deltaMovementZ *= 1.1;
            }
        } else {
            m_isSpeedBoosting = false;
        }
    }
}

void LivingEntity::fallFlyingTravel(double& motionX, double& motionY, double& motionZ, Vec3* viewAngle,
                                    float& xRot, float& fallDistance, double& speed, double liftForce) {
    if (-0.5 < motionY) {
        fallDistance = 1.0;
    }
    float pitchRad = xRot * 0.017453292f;
    double horizontalViewLength
        = std::sqrt(viewAngle->m_x * viewAngle->m_x + viewAngle->m_z * viewAngle->m_z);

    speed = std::sqrt((motionX * motionX) + (motionZ * motionZ));
    double lenView = viewAngle->length();

    float verticalBoost = std::cos(pitchRad);
    float scale = (lenView / 0.4f < 1.0f) ? (lenView / 0.4f) : 1.0f;
    verticalBoost *= verticalBoost * scale;

    verticalBoost *= (float)liftForce;

    motionY += verticalBoost * 0.06 - 0.08;

    if (horizontalViewLength > 0.0 && motionY < 0.0) {
        double d = -0.1 * motionY * verticalBoost;
        motionY += d;
        motionX += (d * viewAngle->m_x) / horizontalViewLength;
        motionZ += (d * viewAngle->m_z) / horizontalViewLength;
    }

    if (pitchRad < 0.0 && horizontalViewLength > 0.0) {
        double d = speed * -std::sin(pitchRad) * 0.04;
        motionY += d * 3.2;
        motionX -= (viewAngle->m_x * d) / horizontalViewLength;
        motionZ -= (viewAngle->m_z * d) / horizontalViewLength;
    }

    if (horizontalViewLength > 0.0) {
        motionX += ((viewAngle->m_x / horizontalViewLength) * speed - motionX) * 0.1;
        motionZ += ((viewAngle->m_z / horizontalViewLength) * speed - motionZ) * 0.1;
    }

    motionX *= 0.99;
    motionY *= 0.98;
    motionZ *= 0.99;
}
