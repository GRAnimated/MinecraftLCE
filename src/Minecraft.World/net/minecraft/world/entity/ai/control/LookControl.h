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

    Mob* m_mob;
    float m_yMaxRotSpeed;
    float m_xMaxRotAngle;
    bool m_isHasWanted;
    double m_wantedX;
    double m_wantedY;
    double m_wantedZ;
};
