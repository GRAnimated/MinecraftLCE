#pragma once

#include "net/minecraft/util/ThreadStorage.h"

namespace phys {
class Vec2 {
public:
    DECLARE_THREAD_STORAGE(Vec2)

    Vec2() {}

    static Vec2* newTemp(float x, float y);

    float m_x;
    float m_y;
};
}  // namespace phys
