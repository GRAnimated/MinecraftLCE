#pragma once

#include "net/minecraft/world/level/gamemode/minigames/EMiniGameId.h"

class MiniGameDef {
public:
    static void StaticCtor();

    static MiniGameDef& GetCustomGameModeById(EMiniGameId id, bool);

    bool HasFeatureDirectionalFireworks() const;
    int GetLivesPerRound() const;
    double getBaseDamage(int, double) const;
    float getExhaustionAttack(float) const;
    float getExhaustionDrop(float) const;
    int getExhaustionHeal(int) const;
    float getExhaustionIdle(float) const;
    float getExhaustionJump(float) const;
    float getExhaustionMine(float) const;
    float getExhaustionSneak(float) const;
    float getExhaustionSprint(float) const;
    float getExhaustionSprintJump(float) const;
    float getExhaustionSwim(float) const;
    float getExhaustionWalk(float) const;
    int getHealLevel(int) const;
    int getHealthTickCount(int) const;
    int getHealthTickCountSaturated(int) const;
    int getMaxFood(int) const;
    float getMaxSaturation(float) const;
    float getStartSaturation(float) const;
    float getSprintLevel(float) const;
    int getStarveLevel(int) const;
    int getPotionDuration(int, int) const;
    bool HasFeatureArrowCanKnockback() const;
    bool ArePowerupsActive() const;
    EMiniGameId GetId() const;
};
