#pragma once

#include "NX/Thread/C4JEvent.h"
#include "nn/os.h"

class C4JEventImpl : public C4JEvent {
public:
    C4JEventImpl(C4JEvent::EMode);
    ~C4JEventImpl() override;
    void Set() override;
    void Clear() override;
    int WaitForSignal(int) override;

    bool field_8;
    int field_C;
    nn::os::EventType mEventType;
};
