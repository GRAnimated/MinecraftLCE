#pragma once

#include "net/minecraft/client/C4JThread.h"

class C4JThreadImpl : public C4JThread {
public:
    C4JThreadImpl(int (*)(void*), void*, const char*, int);

    static void SetMainThreadID();

    virtual ~C4JThreadImpl() override;
    virtual void Run() override;
    virtual void isRunning() override;
    virtual void hasStarted() override;
    virtual void SetProcessor(int) override;
    virtual void GetProcessor() override;
    virtual void SetPriority(int) override;
    virtual void WaitForCompletion(int) override;
    virtual void GetExitCode() override;
    virtual void getName() override;
    virtual void SetDeleteOnExit(bool) override;

    void* unknown[14];
};
