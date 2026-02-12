#include "net/minecraft/world/level/border/WorldBorder.h"

#include "net/minecraft/core/System.h"

WorldBorder::WorldBorder(Level* level) {}

double WorldBorder::getMinX() {
    double max = getCenterX() + getSize() * -0.5;

    if (max < (double)-m_worldSize)
        max = -m_worldSize;
    return max;
}

double WorldBorder::getMaxX() {
    double max = getCenterX() + getSize() * 0.5;

    if (max > (double)m_worldSize)
        max = m_worldSize;
    return max;
}

double WorldBorder::getMinZ() {
    double max = getCenterZ() + getSize() * -0.5;

    if (max < (double)-m_worldSize)
        max = -m_worldSize;
    return max;
}

double WorldBorder::getMaxZ() {
    double max = getCenterZ() + getSize() * 0.5;

    if (max > (double)m_worldSize)
        max = m_worldSize;
    return max;
}

BorderStatus* WorldBorder::getStatus() {
    if (m_nextSize < m_currentSize)
        return gBorderStatusShrinking;

    if (m_nextSize > m_currentSize)
        return gBorderStatusGrowing;

    return gBorderStatusStationary;
}

double WorldBorder::getSize() {
    if (getStatus() != gBorderStatusStationary) {
        double time = (float)(System::processTimeInMilliSecs() - m_time2) / (float)(m_time1 - m_time2);

        if (!(time >= 1.0f))
            return m_currentSize + (time * (m_nextSize - m_currentSize));

        setSize(m_nextSize);
    }
    return m_currentSize;
}

double WorldBorder::getCenterX() {
    return m_centerX;
}

double WorldBorder::getCenterZ() {
    return m_centerZ;
}

std::vector<BorderChangeListener*>* WorldBorder::getListeners() {
    return &m_listeners;
}

double WorldBorder::getDamageSafeZone() {
    return m_damageSafeZone;
}

double WorldBorder::getDamagePerBlock() {
    return m_damageAmount;
}
