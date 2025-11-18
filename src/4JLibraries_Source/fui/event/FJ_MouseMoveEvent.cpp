#include "fui/event/FJ_MouseMoveEvent.h"

FJ_MouseMoveEvent::FJ_MouseMoveEvent(float x, float y, bool a1, bool a2)
    : FJ_Event(eFJEventType::MOUSE_MOVE, a1, a2) {
    this->mX = x;
    this->mY = y;
}
