#pragma once

#include "net/minecraft/world/entity/player/Player.h"

class AbstractClientPlayer : public Player {
public:
    float mElytraRotX;
    float mElytraRotY;
    float mElytraRotZ;
};
