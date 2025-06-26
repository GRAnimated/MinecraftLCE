#pragma once
#include "cstdint"
#include "eFJEventType.h"

class FJ_Event {
public:
    FJ_Event(eFJEventType type, bool, bool);

    void* mUnk;
    uint32_t mEventType;
    bool mUnk2;
    bool mUnk3;
};