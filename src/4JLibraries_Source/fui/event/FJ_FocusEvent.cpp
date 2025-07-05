#include "fui/event/FJ_FocusEvent.h"

FJ_FocusEvent::FJ_FocusEvent(bool hasFocus, bool a2, bool a3)
    : FJ_Event(hasFocus ? eFJEventType::FOCUS_IN : eFJEventType::FOCUS_OUT, a2, a3) {}