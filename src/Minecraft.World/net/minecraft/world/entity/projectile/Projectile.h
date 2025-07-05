#pragma once

#include <memory>

class Entity;
class HitResult;

class Projectile {
public:
    virtual ~Projectile();
    virtual void shoot(double, double, double, float, float) = 0;
    virtual void shootFromRotation(const std::shared_ptr<Entity>&, float, float, float, float, float) = 0;
    virtual bool onHit(const HitResult*);
};
