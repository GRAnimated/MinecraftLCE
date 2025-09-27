#include "XLockFreeStack.h"
#include "net/minecraft/core/System.h"

template <typename T>
XLockFreeStack<T>::XLockFreeStack() {
    this->mVector = new std::vector<T>();
    InitializeCriticalSectionAndSpinCount(&mMutex, 0x1400);
}

template <typename T>
T* XLockFreeStack<T>::Pop() {
    EnterCriticalSection(&this->mMutex);
    if (mVector.empty()) {
        LeaveCriticalSection(&this->mMutex);
        return nullptr;
    }

    T* a = mVector.back();
    mVector.pop_back();

    LeaveCriticalSection(&this->mMutex);

    return a;
}
