#pragma once

enum EMiniGameId { LOBBY = 0, BATTLE = 1, TUMBLE = 2, GLIDE = 3, BUILD_OFF = 4, NORMAL_WORLD = 15 };

class MiniGameDef {
public:
    static void StaticCtor();

    static void* GetCustomGameModeById(EMiniGameId id, bool);

    bool HasFeatureDirectionalFireworks() const;
    int GetLivesPerRound() const;
    double getBaseDamage(int, double) const;
    float getExhaustionAttack(float);
    float getExhaustionDrop(float);
    int getExhaustionHeal(int);
    float getExhaustionIdle(float);
    float getExhaustionJump(float);
    float getExhaustionMine(float);
    float getExhaustionSneak(float);
    float getExhaustionSprint(float);
    float getExhaustionSprintJump(float);
    float getExhaustionSwim(float);
    float getExhaustionWalk(float);
    int getHealLevel(int);
    int getHealthTickCount(int);
    int getHealthTickCountSaturated(int);
    int getMaxFood(int);
    float getMaxSaturation(float);
    float getStartSaturation(float);
    float getSprintLevel(float);
    int getStarveLevel(int);
    int getPotionDuration();
};
