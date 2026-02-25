#pragma once

#include "net/minecraft/world/entity/player/AbstractClientPlayer.h"

class LocalPlayer : public AbstractClientPlayer {
public:
    char m_fill[160];
    int m_itemRendererThingy;
};
