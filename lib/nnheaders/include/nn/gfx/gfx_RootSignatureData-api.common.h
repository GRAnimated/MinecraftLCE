#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/nn_BitTypes.h>

namespace nn::gfx {

template <class TTarget>
struct RootSignatureImplData {
    Bit8 state;
    char reserved[3];
    uint32_t memorySize;
    detail::Ptr<void> pWorkMemory;
};

}  // namespace nn::gfx