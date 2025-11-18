#pragma once

#include "fui/event/FJ_Event.h"

class FJ_FocusEvent : public FJ_Event {
public:
    FJ_FocusEvent(bool, bool, bool);
};
