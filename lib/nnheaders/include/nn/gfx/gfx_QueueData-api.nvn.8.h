#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/nn_BitTypes.h>
#include <nn/util/util_BitPack.h>

namespace nn::gfx {

template <>
struct QueueImplData<ApiVariationNvn8> {
    detail::Ptr<detail::DeviceImpl<ApiVariationNvn8>> pNnDevice;
    detail::Ptr<void> pNvnQueue;
    char nvnQueue[8192];

    enum State { State_NotInitialized, State_Initialized };
    enum Flag { Flag_Shared };

    Bit8 state;
    nn::util::BitPack8 flags;
    char reserved[6];
    detail::Ptr<void> userPtr;
    detail::Ptr<void> pImpl;
};

}  // namespace nn::gfx