#pragma once

#include <nn/os/detail/os_InternalCriticalSection.h>
#include <nn/os/os_ConditionVariableCommon.h>
#include <nn/types.h>

namespace nn::os::detail {

class TimeoutHelper;

class InternalConditionVariableImplByHorizon {
public:
    InternalConditionVariableImplByHorizon();
    void Initialize();
    void Signal();
    void Broadcast();
    void Wait(InternalCriticalSection*);
    ConditionVariableStatus TimedWait(InternalCriticalSection*, const TimeoutHelper&);

private:
    uint32_t m_Value;
};

typedef InternalConditionVariableImplByHorizon InternalConditionVariableImpl;

}  // namespace nn::os::detail