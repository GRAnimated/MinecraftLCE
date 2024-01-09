#pragma once

#include <nn/os/detail/os_InternalCriticalSection-os.horizon.h>
#include <nn/util/util_TypedStorage.h>

namespace nn::os::detail {

class InternalCriticalSection {
public:
    void Initialize();
    void Finalize();
    void Enter();
    bool TryEnter();
    void Leave();
    bool IsLockedByCurrentThread() const;
    void lock();
    void unlock();
    InternalCriticalSectionImpl* Get();

private:
    InternalCriticalSectionImpl m_Impl;
};

typedef nn::util::TypedStorage<InternalCriticalSection, 4, 4> InternalCriticalSectionStorage;

}  // namespace nn::os::detail