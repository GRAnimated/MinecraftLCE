#include "Minecraft.World/entity/ai/control/LookControl.h"

// NON_MATCHING
LookControl::LookControl(Mob* mob) : mMob(mob) {}

void LookControl::setLookAt(double wantedX, double wantedY, double wantedZ, float yMaxRotSpeed,
                            float xMaxRotAngle) {
    mWantedX = wantedX;
    mWantedY = wantedY;
    mWantedZ = wantedZ;
    mYMaxRotSpeed = yMaxRotSpeed;
    mXMaxRotAngle = xMaxRotAngle;
    mIsHasWanted = true;
}

float LookControl::rotlerp(float curAngle, float targetAngle, float maxRot) {
    float diff = targetAngle - curAngle;

    while (diff < -180.0)
        diff += 360.0;
    while (diff >= 180.0)
        diff -= 360.0;

    if (diff > maxRot)
        diff = maxRot;
    if (diff < -maxRot)
        diff = -maxRot;

    return diff + curAngle;
}

bool LookControl::isHasWanted() {
    return mIsHasWanted;
}

double LookControl::getWantedX() {
    return mWantedX;
}

double LookControl::getWantedY() {
    return mWantedY;
}

double LookControl::getWantedZ() {
    return mWantedZ;
}
