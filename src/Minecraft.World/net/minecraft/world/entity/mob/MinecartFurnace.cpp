#include "net/minecraft/world/entity/mob/MinecartFurnace.h"

#include "net/minecraft/util/Mth.h"

#ifdef SAFETY_CHECKS
static_assert(offsetof(MinecartFurnace, m_fuel) == 0x308, "Furnace fuel layout");
static_assert(offsetof(MinecartFurnace, m_pushX) == 0x310, "Furnace propulsion layout");
#endif

double MinecartFurnace::getMaxSpeed() {
    return 0.2;
}

void MinecartFurnace::moveAlongTrack(const BlockPos& pos, const BlockState* state) {
    Minecart::moveAlongTrack(pos, state);
    double pushLengthSqr = m_pushX * m_pushX + m_pushZ * m_pushZ;
    if (pushLengthSqr > 0.0001
        && m_deltaMovementX * m_deltaMovementX + m_deltaMovementZ * m_deltaMovementZ > 0.001) {
        double pushLength = Mth::sqrt(pushLengthSqr);
        m_pushX /= pushLength;
        m_pushZ /= pushLength;
        if (m_pushX * m_deltaMovementX + m_pushZ * m_deltaMovementZ < 0.0) {
            m_pushX = 0.0;
            m_pushZ = 0.0;
            return;
        }
        double scale = pushLength / getMaxSpeed();
        m_pushX *= scale;
        m_pushZ *= scale;
    }
}

void MinecartFurnace::applyNaturalSlowdown() {
    double pushLengthSqr = m_pushX * m_pushX + m_pushZ * m_pushZ;
    if (pushLengthSqr > 0.0001) {
        double pushLength = Mth::sqrt(pushLengthSqr);
        m_pushX /= pushLength;
        m_pushZ /= pushLength;
        m_deltaMovementX *= static_cast<double>(0.8f);
        m_deltaMovementY *= 0.0;
        m_deltaMovementZ *= static_cast<double>(0.8f);
        m_deltaMovementX += m_pushX;
        m_deltaMovementZ += m_pushZ;
    } else {
        m_deltaMovementX *= static_cast<double>(0.98f);
        m_deltaMovementY *= 0.0;
        m_deltaMovementZ *= static_cast<double>(0.98f);
    }
    Minecart::applyNaturalSlowdown();
}
