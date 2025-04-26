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

    Mob* mMob;
    float mYMaxRotSpeed;
    float mXMaxRotAngle;
    bool mIsHasWanted;
    double mWantedX;
    double mWantedY;
    double mWantedZ;
};