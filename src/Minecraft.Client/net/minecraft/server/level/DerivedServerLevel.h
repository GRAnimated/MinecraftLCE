#pragma once

#include "net/minecraft/server/ServerLevel.h"
#include "net/minecraft/world/level/border/BorderChangeListener.h"

class DerivedServerLevel : public ServerLevel {
public:
    class DerivedLevelBorderChangeListener : public BorderChangeListener {
    public:
        explicit DerivedLevelBorderChangeListener(DerivedServerLevel* level);

        void onBorderSizeSet(WorldBorder* border, double newSize) override;
        void onBorderSizeLerping(WorldBorder* border, double from, double to, long long lerpTime) override;
        void onBorderCenterSet(WorldBorder* border, double x, double z) override;
        void onBorderSetWarningTime(WorldBorder* border, int time) override;
        void onBorderSetWarningBlocks(WorldBorder* border, int blocks) override;
        void onBorderSetDamagePerBlock(WorldBorder* border, double damage) override;
        void onBorderSetDamageSafeZOne(WorldBorder* border, double safeZone) override;

    private:
        DerivedServerLevel* m_level;
    };
};
