#pragma once

#include "net/minecraft/client/C4JEvent.h"
#include "nn/os.h"

class C4JEventImpl : public C4JEvent {
public:
    C4JEventImpl(C4JEvent::EMode);
    virtual ~C4JEventImpl() override;
    virtual void Set() override;
    virtual void Clear() override;
    virtual bool WaitForSignal(int) override;

    bool field_8;
    int field_C;
    nn::os::EventType mEventType;
};
