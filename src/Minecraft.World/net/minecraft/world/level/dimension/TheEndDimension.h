#pragma once

#include "net/minecraft/world/level/dimension/Dimension.h"

class EndDragonFight;

class TheEndDimension : public Dimension {
public:
    EndDragonFight* getDragonFight();

private:
    EndDragonFight* m_dragonFight;
};
