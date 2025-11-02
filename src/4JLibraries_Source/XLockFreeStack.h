#pragma once

#include "NX/Platform.h"
#include "nn/os/os_MutexTypes.h"
#include "types.h"

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

ASSERT_SIZEOF(XLockFreeStack<unsigned char>, 0x38)
