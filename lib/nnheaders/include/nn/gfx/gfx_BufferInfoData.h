#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/nn_BitTypes.h>

namespace nn::gfx {

struct BufferInfoData {
    uint32_t size;
    Bit32 gpuAccessFlag;
    char reserved[8];
};

struct BufferTextureViewInfoData {
    Bit32 format;
    uint32_t offset;
    uint32_t size;
    char reserved2[4];
    detail::Ptr<const void> pBuffer;
    char reserved[8];
};

}  // namespace nn::gfx