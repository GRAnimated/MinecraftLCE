#include "XLockFreeStack.h"
#include "net/minecraft/core/System.h"

template <typename T>
XLockFreeStack<T>::XLockFreeStack() {
    this->m_vector = new std::vector<T>();
    InitializeCriticalSectionAndSpinCount(&m_mutex, 0x1400);
}

template <typename T>
T* XLockFreeStack<T>::Pop() {
    EnterCriticalSection(&this->m_mutex);
    if (m_vector.empty()) {
        LeaveCriticalSection(&this->m_mutex);
        return nullptr;
    }

    T* a = m_vector.back();
    m_vector.pop_back();

    LeaveCriticalSection(&this->m_mutex);

    return a;
}
