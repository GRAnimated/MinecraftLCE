#pragma once

#include "4JLibraries_Source/fui/event/FJ_Event.h"

class FJ_KeyboardEvent : public FJ_Event {
public:
    FJ_KeyboardEvent(bool, int, bool, bool);

    int mChar;
};
