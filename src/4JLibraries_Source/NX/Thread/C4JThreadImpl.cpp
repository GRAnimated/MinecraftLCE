#include "NX/Thread/C4JThreadImpl.h"
#include "net/minecraft/core/System.h"

void C4JThreadImpl::Run() {
    this->m_startTime = System::processTimeInMilliSecs();
    this->m_hasStarted = true;
    this->m_isRunning = true;
    nn::os::StartThread(m_thread);
}

bool C4JThreadImpl::isRunning() {
    return this->m_isRunning;
}

bool C4JThreadImpl::hasStarted() {
    return this->m_hasStarted;
}

// NON_MATCHING | Score: 10 (lower is better)
// there's uxtw instead of original sxtw
void C4JThreadImpl::SetProcessor(int core) {
    this->m_processor = core;

    const unsigned int idx = this->m_processor % 3;

    sMask = (idx < 3) ? sCores[idx] : 1;
    nn::os::SetThreadCoreMask(this->m_thread, idx, sMask);
}

int C4JThreadImpl::GetProcessor() {
    return this->m_processor;
}

void C4JThreadImpl::SetPriority(int priority) {
    unsigned p = priority - 14;

    m_priority = 16;
    if (p < 5)
        m_priority = priority;
    nn::os::ChangeThreadPriority(this->m_thread, m_priority);
}

// NON_MATCHING
bool C4JThreadImpl::WaitForCompletion(int i) {}
