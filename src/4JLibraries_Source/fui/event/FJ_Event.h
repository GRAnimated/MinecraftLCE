#pragma once

#include "cstdint"

enum eFJEventType { ZERO = 0, ONE = 1, FOCUS_IN = 2, FOCUS_OUT = 3, ADDED_TO_STAGE = 7, MOUSE_MOVE = 15 };

class FJ_Event {
public:
    FJ_Event(eFJEventType type, bool, bool);

    void* mUnk;
    uint32_t mEventType;
    bool mUnk2;
    bool mUnk3;
};
