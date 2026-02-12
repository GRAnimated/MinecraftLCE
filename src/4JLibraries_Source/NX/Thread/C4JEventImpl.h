#pragma once

#include "NX/Thread/C4JEvent.h"
#include "nn/os.h"

class C4JEventImpl : public C4JEvent {
public:
    C4JEventImpl(C4JEvent::EMode);
    ~C4JEventImpl() override;
    void Set() override;
    void Clear() override;
    int WaitForSignal(int time) override;

    bool m_field8;
    int m_waiting;  // seems to be like waiting count or something
    nn::os::EventType m_eventType;
};
