#pragma once

#include "4JLibraries_Source/fui/event/FJ_Event.h"

class FJ_FocusEvent : public FJ_Event {
public:
    FJ_FocusEvent(bool, bool, bool);
};
