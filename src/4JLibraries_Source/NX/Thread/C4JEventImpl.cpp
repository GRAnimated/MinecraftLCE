#include "NX/Thread/C4JEventImpl.h"

void C4JEventImpl::Set() {
    nn::os::SignalEvent(&this->mEventType);
}

void C4JEventImpl::Clear() {
    nn::os::ClearEvent(&this->mEventType);
}

int C4JEventImpl::WaitForSignal(int time) {
    nn::os::EventType* event = &mEventType;
    mWaiting++;

    if (time == -1) {
        nn::os::WaitEvent(event);
        mWaiting--;

        return 0;
    }

    const bool wait = nn::os::TimedWaitEvent(event, nn::TimeSpan::FromMilliSeconds(time));
    mWaiting--;

    return wait ? 0 : 0x102;  // likely some constant
}
