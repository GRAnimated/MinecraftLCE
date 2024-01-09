#pragma once

namespace nn::gfx::detail {

template <class TImpl>
class RequiredMemory {
protected:
    static size_t GetRequiredMemorySize(...);
    static void SetMemory(void*, size_t);
    static void* GetMemory();
};

}  // namespace nn::gfx::detail