/**
 * @file mem.h
 * @brief Memory allocation functions.
 */

#pragma once

#include <nn/os.h>
#include <nn/types.h>
#include <nn/util/util_TypedStorage.h>

namespace nn {
namespace nlibsdk {
namespace heap {
class CentralHeap;
}  // namespace heap
}  // namespace nlibsdk

namespace mem {
class StandardAllocator {
public:
    StandardAllocator();
    StandardAllocator(void* address, size_t size);
    StandardAllocator(void* address, size_t size, bool enableCache);

    ~StandardAllocator() {
        if (mIsInitialized) {
            Finalize();
        }
    }

    void Initialize(void* address, size_t size);
    void Initialize(void* address, size_t size, bool enableCache);
    void Finalize();
    void* Reallocate(void* address, size_t newSize);
    void* Allocate(size_t size);
    void* Allocate(size_t size, size_t alignment);
    void Free(void* address);

    size_t GetSizeOf(const void* address) const;
    void ClearThreadCache() const;
    void CleanUpManagementArea() const;
    size_t GetTotalFreeSize() const;
    size_t GetAllocatableSize() const;
    void Dump() const;

    bool mIsInitialized;
    bool mIsEnabledThreadCache;
    uintptr_t mAllocAddr;
    nn::os::TlsSlot mTlsSlot;
    nn::util::TypedStorage<nn::nlibsdk::heap::CentralHeap, 48, 8> mCentralHeapStorage;
};

static_assert(sizeof(StandardAllocator) == 0x48);

}  // namespace mem
}  // namespace nn