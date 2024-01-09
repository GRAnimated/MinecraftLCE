#pragma once

#include <nn/types.h>

#include <nn/gfx/detail/gfx_Fwd.h>
#include <nn/gfx/gfx_VariationBase.h>
#include <nn/util.h>

namespace nn::gfx {

enum LowLevelApi { LowLevelApi_Common = 0, LowLevelApi_Nvn = 4 };

using ApiVariationNvn8 = ApiVariation<ApiType<LowLevelApi_Nvn>, ApiVersion<8>>;
using DefaultApi = ApiVariationNvn8;

struct OutOfMemoryEventArg {
    size_t minRequiredSize;
};

union ClearColorValue {
    float valueFloat[4];
    int32_t valueInt[4];
    uint32_t valueUint[4];
};

}  // namespace nn::gfx