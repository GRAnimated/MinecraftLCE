#pragma once

#include <nn/nn_BitTypes.h>

namespace nn::os::detail {

class InternalCriticalSectionImplByHorizon {
public:
    InternalCriticalSectionImplByHorizon();
    void Initialize();
    void Finalize();
    void Enter();
    bool TryEnter();
    void Leave();
    bool IsLockedByCurrentThread() const;
    void lock();
    void unlock();

private:
    Bit32 m_ThreadHandle;
};

typedef InternalCriticalSectionImplByHorizon InternalCriticalSectionImpl;

}  // namespace nn::os::detail