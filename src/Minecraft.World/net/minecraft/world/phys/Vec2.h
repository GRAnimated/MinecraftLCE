#pragma once

#include "net/minecraft/util/ThreadStorage.h"

namespace phys {
class Vec2 {
public:
    DECLARE_THREAD_STORAGE(Vec2)

    Vec2() {}

    float x;
    float y;
};
}  // namespace phys
