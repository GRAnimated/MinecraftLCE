#pragma once

#include "types.h"
#include "Minecraft.World/level/border/BorderChangeListener.h"
#include "Minecraft.World/level/border/BorderStatus.h"
#include <memory>
#include <vector>

class AABB;
class BlockPos;
class Entity;
class Level;

class WorldBorder {
public:
    WorldBorder(Level*);
    virtual ~WorldBorder();

    bool isWithinBounds(const BlockPos&);
    double getMinX();
    double getMaxX();
    double getMinZ();
    double getMaxZ();
    void isWithinBounds(AABB*);
    double getDistanceToBorder(std::shared_ptr<Entity>);
    double getDistanceToBorder(double, double);
    BorderStatus* getStatus();
    double getSize();
    virtual double getCenterX();
    virtual double getCenterZ();
    std::vector<BorderChangeListener*>* getListeners();
    void setSize(double);
    double getDamageSafeZone();
    double getDamagePerBlock();

    std::vector<BorderChangeListener*> mListeners;
    double mCenterX = 0.0;
    double mCenterZ = 0.0;
    double mCurrentSize = 60000000.0;
    double mNextSize = 60000000.0;
    long mTime1 = 0;
    long mTime2 = 0;
    int mWorldSize = 30000000;
    double mDamageAmount = 0.2;
    double mDamageSafeZone = 5.0;
    int mWarningTime = 15;
    int mWarningDistance = 5;
};

ASSERT_SIZEOF(WorldBorder, 0x70)
