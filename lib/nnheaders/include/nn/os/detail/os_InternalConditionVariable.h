#pragma once

#include <nn/os/detail/os_InternalConditionVariable-os.horizon.h>
#include <nn/os/detail/os_InternalCriticalSection.h>

namespace nn::os::detail {

class InternalConditionVariable {
    InternalConditionVariableImpl m_Impl;

public:
    void Initialize();
    void Signal();
    void Broadcast();
    void Wait(InternalCriticalSection*);
    ConditionVariableStatus TimedWait(InternalCriticalSection*, const TimeoutHelper&);
};

typedef util::TypedStorage<InternalConditionVariable, 4, 4> InternalConditionVariableStorage;

}  // namespace nn::os::detail