#include "net/minecraft/world/entity/ai/control/LookControl.h"

LookControl::LookControl(Mob* mob) : m_mob(mob) {
    m_yMaxRotSpeed = 0.0f;
    m_xMaxRotAngle = 0.0f;
    m_isHasWanted = false;
    m_wantedX = m_wantedY = m_wantedZ = 0.0;
}

void LookControl::setLookAt(double wantedX, double wantedY, double wantedZ, float yMaxRotSpeed,
                            float xMaxRotAngle) {
    m_wantedX = wantedX;
    m_wantedY = wantedY;
    m_wantedZ = wantedZ;
    m_yMaxRotSpeed = yMaxRotSpeed;
    m_xMaxRotAngle = xMaxRotAngle;
    m_isHasWanted = true;
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
    return m_isHasWanted;
}

double LookControl::getWantedX() {
    return m_wantedX;
}

double LookControl::getWantedY() {
    return m_wantedY;
}

double LookControl::getWantedZ() {
    return m_wantedZ;
}
