#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_MemoryPoolInfoData.h>

namespace nn::gfx {

class MemoryPoolInfo : public detail::DataContainer<MemoryPoolInfoData> {
public:
    MemoryPoolInfo() {}

    void SetDefault();

    void SetMemoryPoolProperty(int value) { memoryPoolProperty = value; }

    void SetPoolMemory(void* value, size_t size) {
        pMemory = value;
        memorySize = size;
    }

    int GetMemoryPoolProperty() const { return memoryPoolProperty; }
    void* GetPoolMemory() const { return pMemory; }
    size_t GetPoolMemorySize() const { return memorySize; }
};

}  // namespace nn::gfx