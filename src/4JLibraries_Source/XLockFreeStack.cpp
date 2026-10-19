#include "XLockFreeStack.h"

#include "net/minecraft/core/System.h"
#include "nn/os/os_Mutex.h"

// name guessed: the original mutex-finalization wrapper at 0x710060855c.
void DeleteCriticalSection(nn::os::MutexType* mutex) {
    nn::os::FinalizeMutex(mutex);
}

template <typename T>
// name guessed
XLockFreeStack<T>::XLockFreeStack() {
    InitializeCriticalSectionAndSpinCount(&m_mutex, 0x1400);
}

template <typename T>
// name guessed
XLockFreeStack<T>::~XLockFreeStack() {
    DeleteCriticalSection(&m_mutex);
}

template <typename T>
// name guessed
void XLockFreeStack<T>::Push(T* value) {
    EnterCriticalSection(&m_mutex);
    m_vector.push_back(value);
    LeaveCriticalSection(&m_mutex);
}

template <typename T>
T* XLockFreeStack<T>::Pop() {
    EnterCriticalSection(&m_mutex);
    if (m_vector.size() != 0) {
        T* value = m_vector.back();
        m_vector.pop_back();
        LeaveCriticalSection(&m_mutex);
        return value;
    }
    LeaveCriticalSection(&m_mutex);
    return nullptr;
}

template class XLockFreeStack<unsigned char>;
