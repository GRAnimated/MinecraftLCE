#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/nn_BitTypes.h>

namespace nn::gfx {

struct MemoryPoolInfoData {
    Bit32 memoryPoolProperty;
    uint32_t memorySize;
    detail::Ptr<void> pMemory;
    char reserved[16];
};

}  // namespace nn::gfx