#include "FJ_KeyboardEvent.h"

// not sure what the first bool is
// calling it state since it seems to determine enum value
FJ_KeyboardEvent::FJ_KeyboardEvent(bool state, int ch, bool a3, bool a4) : FJ_Event(state ? eFJEventType::ZERO : eFJEventType::ONE, a3, a4) {
    this->mChar = ch;
}