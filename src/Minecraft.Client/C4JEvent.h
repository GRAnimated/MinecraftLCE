#pragma once

class C4JEvent {
public:
    enum EMode : int {
        _0 = 0,
    };
    C4JEvent(C4JEvent::EMode);
    virtual ~C4JEvent();
    virtual void Set() = 0;
    virtual void Clear() = 0;
    virtual bool WaitForSignal(int) = 0;
};
