#pragma once

#include "net/minecraft/world/entity/ai/control/Control.h"

class Mob;

class MoveControl : Control {
public:
    MoveControl(Mob*);

    virtual ~MoveControl();
    virtual void setWantedPosition(double, double, double, double);
    virtual void tick();

    Mob* m_mob;
    double m_wantedX = 0.0;
    double m_wantedY = 0.0;
    double m_wantedZ = 0.0;
    double m_speedModifier = 0.0;
    float m_strafeForwards = 0.0f;
    float m_strafeRight = 0.0f;
    int m_operation = 0;
};
