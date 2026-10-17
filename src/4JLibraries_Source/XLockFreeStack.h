#pragma once

#include "NX/Platform.h"
#include "nn/os/os_MutexTypes.h"
#include "types.h"

#include <vector>

// The original implementation serializes a pointer vector with a mutex.
template <typename T>
class XLockFreeStack {
public:
    XLockFreeStack();
    ~XLockFreeStack();

    void doSomething() {}
    void Push(T*);
    T* Pop();

    std::vector<T*> m_vector;
    nn::os::MutexType m_mutex;
};

ASSERT_SIZEOF(XLockFreeStack<unsigned char>, 0x38)
