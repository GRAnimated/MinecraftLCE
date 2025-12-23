#pragma once

#include "net/minecraft/world/entity/mob/Mob.h"

class Path;

class PathfinderMob : public Mob {
public:
    PathfinderMob(Level* level);

    ~PathfinderMob() override;
    bool couldWander() override;
    bool checkSpawnRules() override;
    void tickLeash() override;
    virtual float getWalkTargetValue(const BlockPos&);
    virtual bool isPathFinding();
    virtual bool isWithinRestriction();
    virtual bool isWithinRestriction(const BlockPos&);
    virtual void restrictTo(const BlockPos&, int);
    virtual BlockPos getRestrictCenter();
    virtual float getRestrictRadius();
    virtual void clearRestriction();
    virtual bool hasRestriction();
    virtual void onLeashDistance(float);
    virtual double followLeashSpeed();

    Path* mPath;
    std::shared_ptr<Entity> someEnt;
    char byte790;
    int dword794;
    BlockPos mRestrictCenter;
    float mRestrictRadius;
    float mPathfindingMalus;
};
