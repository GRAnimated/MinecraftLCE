#pragma once

class C4JThread {
public:
    virtual ~C4JThread();
    virtual void Run() = 0;
    virtual bool isRunning() = 0;
    virtual bool hasStarted() = 0;
    virtual void SetProcessor(int) = 0;
    virtual int GetProcessor() = 0;
    virtual void SetPriority(int) = 0;
    virtual bool WaitForCompletion(int) = 0;
    virtual void GetExitCode() = 0;
    virtual void getName() = 0;
    virtual void SetDeleteOnExit(bool) = 0;
};
