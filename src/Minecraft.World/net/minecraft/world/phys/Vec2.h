#pragma once

#include "net/minecraft/util/ThreadStorage.h"

namespace phys {
class Vec2 {
public:
    DECLARE_THREAD_STORAGE(Vec2)

    Vec2() {}

    float m_x;
    float m_y;
};
}  // namespace phys
