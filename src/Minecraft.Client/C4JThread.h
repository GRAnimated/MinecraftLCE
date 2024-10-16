#pragma once

class C4JThread {
public:
    virtual ~C4JThread();
    virtual void Run() = 0;
    virtual void isRunning() = 0;
    virtual void hasStarted() = 0;
    virtual void SetProcessor(int) = 0;
    virtual void GetProcessor() = 0;
    virtual void SetPriority(int) = 0;
    virtual void WaitForCompletion(int) = 0;
    virtual void GetExitCode() = 0;
    virtual void getName() = 0;
    virtual void SetDeleteOnExit(bool) = 0;
};
