#include "NX/Thread/C4JEventImpl.h"

void C4JEventImpl::Set() {
    nn::os::SignalEvent(&this->m_eventType);
}

void C4JEventImpl::Clear() {
    nn::os::ClearEvent(&this->m_eventType);
}

int C4JEventImpl::WaitForSignal(int time) {
    nn::os::EventType* event = &m_eventType;
    m_waiting++;

    if (time == -1) {
        nn::os::WaitEvent(event);
        m_waiting--;

        return 0;
    }

    const bool wait = nn::os::TimedWaitEvent(event, nn::TimeSpan::FromMilliSeconds(time));
    m_waiting--;

    return wait ? 0 : 0x102;  // likely some constant
}
