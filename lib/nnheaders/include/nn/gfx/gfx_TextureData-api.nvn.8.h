#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/nn_BitTypes.h>
#include <nn/util/util_BitPack.h>

namespace nn::gfx {

template <>
struct TextureImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };
    enum Flag { Flag_Shared };

    Bit8 state;
    nn::util::BitPack8 flags;
    char reserved[6];
    detail::Ptr<void> pNvnTexture;
    char nvnTexture[192];
    detail::Ptr<void> userPtr;
};

template <>
struct TextureViewImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };
    enum Flag { Flag_Shared };

    Bit8 state;
    nn::util::BitPack8 flags;
    char reserved[6];
    detail::Ptr<void> pNvnTexture;
    detail::Ptr<void> pNvnTextureView;
    char nvnTextureView[40];
    detail::Ptr<void> userPtr;
};

template <>
struct ColorTargetViewImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };
    enum Flag { Flag_Shared };

    Bit8 state;
    nn::util::BitPack8 flags;
    char reserved[6];
    detail::Ptr<void> pNvnTexture;
    detail::Ptr<void> pNvnTextureView;
    char nvnTextureView[40];
    detail::Ptr<void> userPtr;
};

template <>
struct DepthStencilViewImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };
    enum Flag { Flag_Shared };

    Bit8 state;
    nn::util::BitPack8 flags;
    char reserved[6];
    detail::Ptr<void> pNvnTexture;
    detail::Ptr<void> pNvnTextureView;
    char nvnTextureView[40];
    detail::Ptr<void> userPtr;
};

}  // namespace nn::gfx