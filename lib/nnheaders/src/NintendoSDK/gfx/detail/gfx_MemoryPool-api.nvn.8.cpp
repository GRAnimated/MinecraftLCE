#include <nn/gfx/detail/gfx_MemoryPool-api.nvn.8.h>

#include <nn/gfx/detail/gfx_Device-api.nvn.8.h>
#include <nn/gfx/gfx_MemoryPoolInfo.h>

#include "gfx_NvnHelper.h"

namespace nn::gfx::detail {

size_t MemoryPoolImpl<ApiVariationNvn8>::GetPoolMemoryAlignment(DeviceImpl<ApiVariationNvn8>*,
                                                                const MemoryPoolInfo&) {
    return 0x1000;
}

size_t MemoryPoolImpl<ApiVariationNvn8>::GetPoolMemorySizeGranularity(DeviceImpl<ApiVariationNvn8>*,
                                                                      const MemoryPoolInfo&) {
    return 0x1000;
}

MemoryPoolImpl<ApiVariationNvn8>::MemoryPoolImpl() {
    state = State_NotInitialized;
}

MemoryPoolImpl<ApiVariationNvn8>::~MemoryPoolImpl() {}

void MemoryPoolImpl<ApiVariationNvn8>::Initialize(DeviceImpl<ApiVariationNvn8>* pDevice,
                                                  const MemoryPoolInfo& info) {
    int memoryPoolFlags = Nvn::GetMemoryPoolFlags(info.GetMemoryPoolProperty());

    pNvnMemoryPool = &nvnMemoryPool;
    pMemory = info.GetPoolMemory();

    NVNmemoryPoolBuilder builder;
    nvnMemoryPoolBuilderSetDevice(&builder, pDevice->ToData()->pNvnDevice);
    nvnMemoryPoolBuilderSetDefaults(&builder);
    nvnMemoryPoolBuilderSetFlags(&builder, memoryPoolFlags);
    nvnMemoryPoolBuilderSetStorage(&builder, info.GetPoolMemory(), info.GetPoolMemorySize());
    nvnMemoryPoolInitialize(pNvnMemoryPool, &builder);

    flags.SetBit(Flag_Shared, false);
    state = State_Initialized;
}

void MemoryPoolImpl<ApiVariationNvn8>::Finalize(DeviceImpl<ApiVariationNvn8>*) {
    nvnMemoryPoolFinalize(pNvnMemoryPool);
    pMemory = nullptr;
    state = State_NotInitialized;
}

void* MemoryPoolImpl<ApiVariationNvn8>::Map() const {
    return nvnMemoryPoolMap(pNvnMemoryPool);
}

void MemoryPoolImpl<ApiVariationNvn8>::Unmap() const {}

void MemoryPoolImpl<ApiVariationNvn8>::FlushMappedRange(ptrdiff_t offset, size_t size) const {
    nvnMemoryPoolFlushMappedRange(pNvnMemoryPool, offset, size);
}

void MemoryPoolImpl<ApiVariationNvn8>::InvalidateMappedRange(ptrdiff_t offset, size_t size) const {
    nvnMemoryPoolInvalidateMappedRange(pNvnMemoryPool, offset, size);
}

}  // namespace nn::gfx::detail