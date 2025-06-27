#pragma once
#include "FJ_Event.h"

class FJ_KeyboardEvent : public FJ_Event {
public:
    FJ_KeyboardEvent(bool, int, bool, bool);

    uint64_t unk;
};