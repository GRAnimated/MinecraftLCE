#pragma once
#include "FJ_Event.h"

class FJ_FocusEvent : public FJ_Event {
public:
    FJ_FocusEvent(bool, bool, bool);
};
