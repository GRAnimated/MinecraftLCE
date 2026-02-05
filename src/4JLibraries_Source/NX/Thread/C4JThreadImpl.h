#pragma once

#include "NX/Thread/C4JThread.h"
#include "nn/os/os_ThreadTypes.h"

constexpr long sCores[4] = {1, 2, 4, 0};

class C4JThreadImpl : public C4JThread {
public:
    static unsigned long sMask;

    C4JThreadImpl(int (*threadProc)(void *), void*, const char*, int);

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

    void* unknown2[6];
    int mUnk;
    int mProcessor;  // which core to use ig
    void* unk;
    bool mIsRunning;
    bool mHasStarted;
    long mStartTime;
    void* unknown[2];
    int mPriority;
    int mUnk23;
    nn::os::ThreadType* mThread;
    // void* unknown[14];
};
