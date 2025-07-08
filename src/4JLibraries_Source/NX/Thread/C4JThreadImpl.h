#pragma once

#include "NX/Thread/C4JThread.h"

class C4JThreadImpl : public C4JThread {
public:
    C4JThreadImpl(int (*)(void*), void*, const char*, int);

    static void SetMainThreadID();

    ~C4JThreadImpl() override;
    void Run() override;
    void isRunning() override;
    void hasStarted() override;
    void SetProcessor(int) override;
    void GetProcessor() override;
    void SetPriority(int) override;
    void WaitForCompletion(int) override;
    void GetExitCode() override;
    void getName() override;
    void SetDeleteOnExit(bool) override;

    void* unknown[14];
};
