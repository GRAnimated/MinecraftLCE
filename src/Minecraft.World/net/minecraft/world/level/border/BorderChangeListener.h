#pragma once

class Level;
class WorldBorder;

class BorderChangeListener {
public:
    BorderChangeListener();

    virtual ~BorderChangeListener();
    virtual void onBorderSizeSet(WorldBorder *border, double newSize) = 0;
    virtual void onBorderSizeLerping(WorldBorder *border, double from, double to, long long lerpTime) = 0;
    virtual void onBorderCenterSet(WorldBorder *border, double x, double z) = 0;
    virtual void onBorderSetWarningTime(WorldBorder *border, int time) = 0;
    virtual void onBorderSetWarningBlocks(WorldBorder *border, int) = 0;
    virtual void onBorderSetDamagePerBlock(WorldBorder *border, double damage) = 0;
    virtual void onBorderSetDamageSafeZOne(WorldBorder *border, double safeZone) = 0; // ZOne
};
