#pragma once

#include "4JLibraries_Source/fui/event/FJ_Event.h"

class FJ_MouseMoveEvent : public FJ_Event {
public:
    FJ_MouseMoveEvent(float x, float y, bool a1, bool a2);

    float mX;
    float mY;
};
