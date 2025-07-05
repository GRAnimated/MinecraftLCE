#include "fui/event/FJ_Event.h"

FJ_Event::FJ_Event(eFJEventType type, bool a2, bool a3) {
    this->mEventType = type;
    this->mUnk2 = a2;
    this->mUnk3 = a3;
}
