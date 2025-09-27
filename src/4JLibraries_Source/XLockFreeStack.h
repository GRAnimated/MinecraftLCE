#pragma once

#include "NX/Platform.h"
#include "nn/os/os_MutexTypes.h"

#include <vector>

// wtf is this
template <typename T>
class XLockFreeStack {
public:
    XLockFreeStack();

    void doSomething() {}
    T* Pop();

    std::vector<T> mVector;
    nn::os::MutexType mMutex;
};

static_assert(sizeof(XLockFreeStack<unsigned char>) == 0x38);
