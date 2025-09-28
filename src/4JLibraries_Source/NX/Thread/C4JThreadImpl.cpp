#include "4JLibraries_Source/NX/Thread/C4JThreadImpl.h"
#include "net/minecraft/core/System.h"

void C4JThreadImpl::Run() {
    this->mStartTime = System::processTimeInMilliSecs();
    this->mHasStarted = true;
    this->mIsRunning = true;
    nn::os::StartThread(mThread);
}

bool C4JThreadImpl::isRunning() {
    return this->mIsRunning;
}

bool C4JThreadImpl::hasStarted() {
    return this->mHasStarted;
}

// NON_MATCHING | Score: 10 (lower is better)
// there's uxtw instead of original sxtw
void C4JThreadImpl::SetProcessor(int core) {
    this->mProcessor = core;

    const unsigned int idx = this->mProcessor % 3;

    sMask = (idx < 3) ? sCores[idx] : 1;
    nn::os::SetThreadCoreMask(this->mThread, idx, sMask);
}

int C4JThreadImpl::GetProcessor() {
    return this->mProcessor;
}

void C4JThreadImpl::SetPriority(int priority) {
    unsigned p = priority - 14;

    mPriority = 16;
    if (p < 5)
        mPriority = priority;
    nn::os::ChangeThreadPriority(this->mThread, mPriority);
}

bool C4JThreadImpl::WaitForCompletion(int i) {}
