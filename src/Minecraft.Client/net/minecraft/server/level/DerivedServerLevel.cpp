#include "DerivedServerLevel.h"
#include "net/minecraft/world/level/border/WorldBorder.h"

DerivedServerLevel::DerivedLevelBorderChangeListener::DerivedLevelBorderChangeListener(
    DerivedServerLevel* level)
    : BorderChangeListener() {
    this->m_level = level;
}

void DerivedServerLevel::DerivedLevelBorderChangeListener::onBorderSizeSet(WorldBorder* border,
                                                                           double newSize) {
    this->m_level->getWorldBorder()->setSize(newSize);
}
void DerivedServerLevel::DerivedLevelBorderChangeListener::onBorderSizeLerping(WorldBorder* border,
                                                                               double from, double to,
                                                                               long long lerpTime) {
    this->m_level->getWorldBorder()->lerpSizeBetween(from, to, lerpTime);
}

void DerivedServerLevel::DerivedLevelBorderChangeListener::onBorderCenterSet(WorldBorder* border, double x,
                                                                             double z) {
    this->m_level->getWorldBorder()->setCenter(x, z);
}

void DerivedServerLevel::DerivedLevelBorderChangeListener::onBorderSetWarningTime(WorldBorder* border,
                                                                                  int time) {
    this->m_level->getWorldBorder()->setWarningTime(time);
}

void DerivedServerLevel::DerivedLevelBorderChangeListener::onBorderSetWarningBlocks(WorldBorder* border,
                                                                                    int blocks) {
    this->m_level->getWorldBorder()->setWarningBlocks(blocks);
}

void DerivedServerLevel::DerivedLevelBorderChangeListener::onBorderSetDamagePerBlock(WorldBorder* border,
                                                                                     double damage) {
    this->m_level->getWorldBorder()->setDamagePerBlock(damage);
}

void DerivedServerLevel::DerivedLevelBorderChangeListener::onBorderSetDamageSafeZOne(WorldBorder* border,
                                                                                     double safeZone) {
    this->m_level->getWorldBorder()->setDamageSafeZone(safeZone);
}
