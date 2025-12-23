#pragma once

#include <memory>

class Path;
class Entity;
class BlockPos;

class PathNavigation {
public:
    virtual ~PathNavigation();
    virtual void pure_virt1() = 0;
    virtual void createPath(const BlockPos& pos);
    virtual void createPath(std::shared_ptr<Entity> entity);
    virtual void moveTo(double x, double y, double z, double speed);
    virtual void moveTo(std::shared_ptr<Entity> entity, double speed);
    virtual void moveTo(Path* path, double speed);
    virtual void tick();
    virtual bool shouldAvoidSun() const;
    virtual void updatePath();
    virtual void pure_virt2() = 0;
    virtual void pure_virt3() = 0;
    virtual void trimPath();
    virtual void pure_virt4() = 0;
    virtual void getNodeEvaluator();
    virtual bool isStableDestination(const BlockPos& pos);

    bool isDone();
};
