#pragma once

#include "NX/Thread/C4JThread.h"
#include "nn/os/os_ThreadTypes.h"

constexpr long sCores[4] = {1, 2, 4, 0};

class C4JThreadImpl : public C4JThread {
public:
    static unsigned long sMask;

    C4JThreadImpl(int (*)(void*), void*, const char*, int);

    static void SetMainThreadID();

    ~C4JThreadImpl() override;
    void Run() override;
    bool isRunning() override;
    bool hasStarted() override;
    void SetProcessor(int) override;
    int GetProcessor() override;
    void SetPriority(int priority) override;
    bool WaitForCompletion(int) override;
    void GetExitCode() override;
    void getName() override;
    void SetDeleteOnExit(bool) override;

    void* m_unknown2[6];
    int m_unk;
    int m_processor;  // which core to use ig
    void* m_unk1;
    bool m_isRunning;
    bool m_hasStarted;
    long m_startTime;
    void* m_unknown[2];
    int m_priority;
    int m_unk23;
    nn::os::ThreadType* m_thread;
    // void* unknown[14];
};
