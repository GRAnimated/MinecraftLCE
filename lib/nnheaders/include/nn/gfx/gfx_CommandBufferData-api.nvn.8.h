#pragma once

#include <nn/gfx/detail/gfx_Common-api.nvn.h>
#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/nn_BitTypes.h>
#include <nn/util/util_BitPack.h>

namespace nn::gfx {

template <>
struct CommandBufferImplData<ApiVariationNvn8> {
    enum Flag { Flag_Shared, Flag_ConservativeRasterSupported };

    enum State { State_NotInitialized, State_Initialized, State_Begun };

    Bit8 state;
    nn::util::BitPack8 flags;
    char reserved[6];
    detail::Ptr<detail::DeviceImpl<ApiVariationNvn8>> pNnDevice;
    detail::Ptr<const detail::RootSignatureImpl<ApiVariationNvn8>> pGfxRootSignature;

    struct {
        char reserved[160];
    } nvnCommandBuffer;

    detail::Ptr<void> pNvnCommandBuffer;
    detail::NvnHandle hNvnCommandBuffer;
    char reserved2[4];
    detail::Ptr<void()> pOutOfCommandMemoryCallback;
    detail::Ptr<void()> pOutOfControlMemoryCallback;
    detail::Ptr<void> userPtr;
};

}  // namespace nn::gfx