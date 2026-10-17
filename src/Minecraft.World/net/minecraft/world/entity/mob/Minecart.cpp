#include "net/minecraft/world/entity/mob/Minecart.h"

#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/phys/AABB.h"

#ifdef SAFETY_CHECKS
static_assert(offsetof(Minecart, m_flipped) == 0x2B4, "Minecart tail padding reuse");
static_assert(offsetof(Minecart, m_lerpSteps) == 0x2C4, "Minecart interpolation layout");
static_assert(offsetof(Minecart, m_lerpDeltaX) == 0x2F0, "Minecart velocity layout");
#endif

double Minecart::getMaxSpeed() {
    return 0.4;
}

void Minecart::activateMinecart(int, int, int, bool) {}

void Minecart::moveOffTrack() {
    double maxSpeed = getMaxSpeed();
    double movementX = Mth::clamp(m_deltaMovementX, -maxSpeed, maxSpeed);
    m_deltaMovementX = movementX;
    m_deltaMovementZ = Mth::clamp(m_deltaMovementZ, -maxSpeed, maxSpeed);
    if (m_onGround) {
        movementX *= 0.5;
        m_deltaMovementX = movementX;
        m_deltaMovementZ *= 0.5;
    }
    move(SELF, movementX, m_deltaMovementY, m_deltaMovementZ, false);
    if (!m_onGround) {
        m_deltaMovementX *= static_cast<double>(0.95f);
        m_deltaMovementZ *= static_cast<double>(0.95f);
    }
}

void Minecart::applyNaturalSlowdown() {
    double drag = isVehicle() ? static_cast<double>(0.997f) : static_cast<double>(0.96f);
    m_deltaMovementX *= drag;
    m_deltaMovementY *= 0.0;
    m_deltaMovementZ *= drag;
}

void Minecart::setPos(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
    double halfWidth = m_width * 0.5f;
    setBoundingBox(
        AABB::newTemp(x - halfWidth, y, z - halfWidth, x + halfWidth, y + m_height, z + halfWidth));
}

void Minecart::lerpMotion(double x, double y, double z) {
    m_deltaMovementX = x;
    m_deltaMovementY = y;
    m_deltaMovementZ = z;
    m_lerpDeltaX = x;
    m_lerpDeltaY = y;
    m_lerpDeltaZ = z;
}
