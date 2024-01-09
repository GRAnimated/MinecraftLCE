#pragma once

#include <nn/os/detail/os_InternalConditionVariable.h>
#include <nn/os/detail/os_InternalCriticalSection.h>
#include <nn/os/detail/os_ThreadTypes-os.horizon.h>
#include <nn/os/os_ThreadCommon.h>
#include <nn/util/util_TypedStorage.h>

namespace nn {

namespace util {
class IntrusiveListNode;
}

namespace os {

struct FiberType;

namespace detail {
class MultiWaitObjectList;
}

struct ThreadType {
    util::TypedStorage<util::IntrusiveListNode, 16, 8> _allThreadsListNode;
    util::TypedStorage<detail::MultiWaitObjectList, 16, 8> _multiWaitObjectList;

    uintptr_t reserved[4];

    uint8_t _state;
    bool _stackIsAliased;
    bool _autoRegistered;
    uint8_t _suspendCount;
    int _basePriority;
    void* _originalStack;
    void* _stack;
    size_t _stackSize;
    void* _argument;
    ThreadFunction _threadFunction;
    FiberType* _currentFiber;
    FiberType* _initialFiber;
    uint32_t _lockHistory;
    uintptr_t _tlsValueArray[32];
    char _threadNameBuffer[32];
    const char* _namePointer;
    detail::InternalCriticalSectionStorage _csThread;
    detail::InternalConditionVariableStorage _cvThread;
    detail::InternalThreadHandle _handle;
};
#ifdef SWITCH
static_assert(sizeof(ThreadType) == 0x1C0, "Wrong size");
#endif

}  // namespace os

}  // namespace nn