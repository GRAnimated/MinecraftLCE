#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/nn_BitTypes.h>
#include <nn/util/util_BitPack.h>

namespace nn::gfx {

template <>
struct BufferImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };

    enum Flag { Flag_Shared, Flag_CpuCached };

    Bit8 state;
    nn::util::BitPack8 flags;
    char reserved[6];
    detail::Ptr<void> pNvnBuffer;
    char nvnBuffer[48];
    detail::Ptr<void> userPtr;
};

template <>
struct BufferTextureViewImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };
    enum Flag { Flag_Shared };

    Bit8 state;
    nn::util::BitPack8 flags;
    char reserved[6];
    char nvnTexture[192];
    detail::Ptr<void> pNvnTexture;
};

}  // namespace nn::gfx