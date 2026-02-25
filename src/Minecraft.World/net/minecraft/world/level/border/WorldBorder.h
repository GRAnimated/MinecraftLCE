#pragma once

#include "net/minecraft/world/level/border/BorderChangeListener.h"
#include "net/minecraft/world/level/border/BorderStatus.h"
#include "net/minecraft/world/level/chunk/ChunkPos.h"
#include "types.h"

#include <memory>
#include <vector>

class AABB;
class BlockPos;
class Entity;
class Level;

class WorldBorder {
public:
    explicit WorldBorder(Level*);

    virtual ~WorldBorder();

    double getMinX();
    double getMaxX();
    double getMinZ();
    double getMaxZ();
    double getSize();

    virtual double getCenterX();
    virtual double getCenterZ();

    int getAbsoluteMaxSize() DELETE_UNUSED;
    void setAbsoluteMaxSize(int maxSize);

    double getDamagePerBlock();
    void setDamagePerBlock(double damage);

    double getDamageSafeZone();
    void setDamageSafeZone(double safeZone);

    BorderStatus* getStatus();

    bool isWithinBounds(AABB* aabb);
    bool isWithinBounds(ChunkPos* pos) DELETE_EXTERNAL;
    bool isWithinBounds(const BlockPos& pos);
    bool isWithinBounds(double x, double z) DELETE_EXTERNAL;

    int getWarningBlocks() DELETE_UNUSED;
    void setWarningBlocks(int blocks);

    int getWarningTime() DELETE_UNUSED;
    void setWarningTime(int time);

    long long getLerpRemainingTime() DELETE_UNUSED;
    long long getLerpSpeed() DELETE_EXTERNAL;
    long long getLerpTarget() DELETE_UNUSED;

    double getDistanceToBorder(std::shared_ptr<Entity> entity);
    double getDistanceToBorder(double x, double z);

    void addListener(BorderChangeListener* listener);
    std::vector<BorderChangeListener*>& getListeners();
    void removeListener(BorderChangeListener* listener) DELETE_EXTERNAL;

    void setSize(double size);
    void setCenter(double x, double z);
    void lerpSizeBetween(double from, double to, long long lerpTime);

private:
    std::vector<BorderChangeListener*> m_listeners;

    double m_centerX = 0.0;
    double m_centerZ = 0.0;

    double m_currentSize = 60000000.0;
    double m_nextSize = 60000000.0;

    long m_finishTime = 0;
    long m_startTime = 0;

    int m_absoluteMaxSize = 30000000;

    double m_damagePerBlock = 0.2;
    double m_damageSafeZone = 5.0;

    int m_warningTime = 15;
    int m_warningBlocks = 5;
};

ASSERT_SIZEOF(WorldBorder, 0x70)
