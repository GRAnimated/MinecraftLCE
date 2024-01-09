#pragma once

#include <nn/os/detail/os_InternalConditionVariable.h>
#include <nn/os/detail/os_InternalCriticalSection.h>
#include <nn/util/util_TypedStorage.h>

namespace nn::os {

namespace detail {
class MultiWaitObjectList;
}

struct MessageQueueType {
    util::TypedStorage<detail::MultiWaitObjectList, 16, 8> _multiWaitObjectListNotFull;
    util::TypedStorage<detail::MultiWaitObjectList, 16, 8> _multiWaitObjectListNotEmpty;
    uintptr_t* _buffer;
    int _maxCount;
    int _count;
    int _offset;
    uint8_t _state;
    detail::InternalCriticalSectionStorage _csQueue;
    detail::InternalConditionVariableStorage _cvNotFull;
    detail::InternalConditionVariableStorage _cvNotEmpty;
};

}  // namespace nn::os
