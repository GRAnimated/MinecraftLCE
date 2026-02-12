#pragma once

#include "net/minecraft/world/entity/player/Player.h"

class AbstractClientPlayer : public Player {
public:
    float m_elytraRotX;
    float m_elytraRotY;
    float m_elytraRotZ;
};
