#include "fui/event/FJ_Event.h"

FJ_Event::FJ_Event(eFJEventType type, bool a2, bool a3) {
    this->m_eventType = type;
    this->m_unk2 = a2;
    this->m_unk3 = a3;
}
