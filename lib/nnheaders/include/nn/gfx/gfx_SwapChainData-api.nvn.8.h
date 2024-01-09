#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_TextureData-api.nvn.8.h>

namespace nn::gfx {

template <>
struct SwapChainImplData<ApiVariationNvn8> {
    static const int NvnMaxScanBufferCount;
    detail::Ptr<const detail::DeviceImpl<ApiVariationNvn8>> pNnDevice;
    detail::Ptr<void> pNvnWindow;
    char nvnWindow[384];
    Bit8 state;
    nn::util::BitPack8 flag;
    char reserved[2];
    uint32_t currentScanBufferIndex;
    uint32_t totalScanBuffers;
    char reserved2[4];
    TextureImplData<ApiVariationNvn8> scanBufferTextures[4];
    ColorTargetViewImplData<ApiVariationNvn8> scanBufferViews[4];
    detail::Ptr<void> userPtr;
};

}  // namespace nn::gfx