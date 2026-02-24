#pragma once

#include "net/minecraft/world/level/border/BorderChangeListener.h"
#include "net/minecraft/world/level/border/BorderStatus.h"
#include "types.h"
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

    std::vector<BorderChangeListener*> m_listeners;
    double m_centerX = 0.0;
    double m_centerZ = 0.0;
    double m_currentSize = 60000000.0;
    double m_nextSize = 60000000.0;
    long m_time1 = 0;
    long m_time2 = 0;
    int m_worldSize = 30000000;
    double m_damageAmount = 0.2;
    double m_damageSafeZone = 5.0;
    int m_warningTime = 15;
    int m_warningDistance = 5;
};

ASSERT_SIZEOF(WorldBorder, 0x70)
