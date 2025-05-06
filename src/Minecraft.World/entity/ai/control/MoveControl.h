#include "Minecraft.World/entity/ai/control/Control.h"

class Mob;

class MoveControl : Control {
public:
    MoveControl(Mob*);

    virtual ~MoveControl();
    virtual void setWantedPosition(double, double, double, double);
    virtual void tick();

    Mob* mMob;
    double mWantedX = 0.0;
    double mWantedY = 0.0;
    double mWantedZ = 0.0;
    double mSpeedModifier = 0.0;
    float mStrafeForwards = 0.0f;
    float mStrafeRight = 0.0f;
    int mOperation = 0;
};