#pragma once
#include "FJ_Event.h"

class FJ_MouseMoveEvent : public FJ_Event {
public:
    FJ_MouseMoveEvent(bool, bool, float, float); // NOTE: had to change param order to make fui::dispatchMouseMoveEvent match

    uint64_t unk;
};