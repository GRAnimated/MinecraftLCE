#pragma once

#include "net/minecraft/world/entity/player/AbstractClientPlayer.h"

class LocalPlayer : public AbstractClientPlayer {
public:
    char fill[160];
    int mItemRendererThingy;
};
