#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/level/border/WorldBorder.h"

#include "net/minecraft/core/System.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/phys/AABB.h"

WorldBorder::WorldBorder(Level*) {}

// NON_MATCHING | Difference: 460
// I can't seem to replicate what it does, this is the closest I've gotten so far tho.
WorldBorder::~WorldBorder() {
    m_listeners.clear();
}

double WorldBorder::getMinX() {
    double max = getCenterX() + getSize() * -0.5;

    if (max < static_cast<double>(-m_absoluteMaxSize))
        max = -m_absoluteMaxSize;
    return max;
}

double WorldBorder::getMaxX() {
    double max = getCenterX() + getSize() * 0.5;

    if (max > static_cast<double>(m_absoluteMaxSize))
        max = m_absoluteMaxSize;
    return max;
}

double WorldBorder::getMinZ() {
    double max = getCenterZ() + getSize() * -0.5;

    if (max < static_cast<double>(-m_absoluteMaxSize))
        max = -m_absoluteMaxSize;
    return max;
}

double WorldBorder::getMaxZ() {
    double max = getCenterZ() + getSize() * 0.5;

    if (max > static_cast<double>(m_absoluteMaxSize))
        max = m_absoluteMaxSize;

    return max;
}
bool WorldBorder::isWithinBounds(const BlockPos &pos) {
    return pos.getX() + 1 > this->getMinX()
        && pos.getX()     < this->getMaxX()
        && pos.getZ() + 1 > this->getMinZ()
        && pos.getZ()     < this->getMaxZ();
}

bool WorldBorder::isWithinBounds(AABB *aabb) {
    return aabb->maxX > this->getMinX()
        && aabb->minX < this->getMaxX()
        && aabb->maxZ > this->getMinZ()
        && aabb->minZ < this->getMaxZ();
}

double WorldBorder::getDistanceToBorder(std::shared_ptr<Entity> entity) {
    return this->getDistanceToBorder(entity->mX, entity->mZ);
}

double WorldBorder::getDistanceToBorder(double x, double z) {
    const double nz = z - this->getMinZ();
    const double pz = this->getMaxZ() - z;
    const double nx = x - this->getMinX();
    const double px = this->getMaxX() - x;

    double dist = std::min(nx, px);
    dist = std::min(dist, nz);
    dist = std::min(dist, pz);

    return dist;
}

void WorldBorder::addListener(BorderChangeListener* listener) {
    this->m_listeners.push_back(listener);
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
        double time = (float)(System::processTimeInMilliSecs() - m_startTime) / (float)(m_finishTime - m_startTime);

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

std::vector<BorderChangeListener*>& WorldBorder::getListeners() {
    return m_listeners;
}

void WorldBorder::setSize(double size) {
    this->m_currentSize = size;
    this->m_nextSize = size;

    const long t = System::processTimeInMilliSecs();
    this->m_finishTime = t;
    this->m_startTime = t;

    std::vector<BorderChangeListener*>& listeners = this->getListeners();
    for (auto i = listeners.begin(); i != listeners.end(); ++i) {
        (*i)->onBorderSizeSet(this, size);
    }
}

void WorldBorder::setAbsoluteMaxSize(int maxSize) {
    this->m_absoluteMaxSize = maxSize;
}

void WorldBorder::setCenter(double x, double z) {
    this->m_centerX = x;
    this->m_centerZ = z;

    std::vector<BorderChangeListener*>& listeners = this->getListeners();
    for (auto i = listeners.begin(); i != listeners.end(); ++i) {
        (*i)->onBorderCenterSet(this, x, z);
    }
}

void WorldBorder::setDamagePerBlock(double damage) {
    this->m_damagePerBlock = damage;

    std::vector<BorderChangeListener*>& listeners = this->getListeners();
    for (auto i = listeners.begin(); i != listeners.end(); ++i) {
        (*i)->onBorderSetDamagePerBlock(this, damage);
    }
}

void WorldBorder::setDamageSafeZone(double safeZone) {
    this->m_damageSafeZone = safeZone;

    std::vector<BorderChangeListener*>& listeners = this->getListeners();
    for (auto i = listeners.begin(); i != listeners.end(); ++i) {
        (*i)->onBorderSetDamageSafeZOne(this, safeZone);
    }
}

void WorldBorder::setWarningBlocks(int blocks) {
    this->m_warningBlocks = blocks;

    std::vector<BorderChangeListener*>& listeners = this->getListeners();
    for (auto i = listeners.begin(); i != listeners.end(); ++i) {
        (*i)->onBorderSetWarningBlocks(this, blocks);
    }
}

void WorldBorder::setWarningTime(int time) {
    this->m_warningTime = time;

    std::vector<BorderChangeListener*>& listeners = this->getListeners();
    for (auto i = listeners.begin(); i != listeners.end(); ++i) {
        (*i)->onBorderSetWarningTime(this, time);
    }
}

void WorldBorder::lerpSizeBetween(double from, double to, long long lerpTime) {
    this->m_currentSize = from;
    this->m_nextSize = to;

    const long t = System::processTimeInMilliSecs();
    this->m_finishTime = t + lerpTime;
    this->m_startTime = t;

    std::vector<BorderChangeListener*>& listeners = this->getListeners();
    for (auto i = listeners.begin(); i != listeners.end(); ++i) {
        (*i)->onBorderSizeLerping(this, from, to, lerpTime);
    }
}

double WorldBorder::getDamageSafeZone() {
    return m_damageSafeZone;
}

double WorldBorder::getDamagePerBlock() {
    return m_damagePerBlock;
}
