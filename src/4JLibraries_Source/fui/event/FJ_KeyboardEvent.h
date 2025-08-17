#pragma once

#include "fui/event/FJ_Event.h"

class FJ_KeyboardEvent : public FJ_Event {
public:
    FJ_KeyboardEvent(bool, int, bool, bool);

    int mChar;
};
