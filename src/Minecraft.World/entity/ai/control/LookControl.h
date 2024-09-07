#pragma once

#include <memory>

class Entity;
class Mob;

class LookControl {
public:
    LookControl(Mob*);
    void setLookAt(std::shared_ptr<Entity>, float, float);
    void setLookAt(double, double, double, float, float);
    float rotlerp(float, float, float);
    void tick();
    bool isHasWanted();
    double getWantedX();
    double getWantedY();
    double getWantedZ();

    Mob* mMob = nullptr;
    float mYMaxRotSpeed = 0.0f;
    float mXMaxRotAngle = 0.0f;
    bool mIsHasWanted = false;
    double mWantedX = 0.0;
    double mWantedY = 0.0;
    double mWantedZ = 0.0;
};