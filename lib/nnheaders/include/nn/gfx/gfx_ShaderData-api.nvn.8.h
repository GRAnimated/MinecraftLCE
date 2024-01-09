#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/nn_BitTypes.h>
#include <nn/util/util_BitPack.h>

namespace nn::gfx {

template <>
struct ShaderImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };
    enum Flag { Flag_SeparationEnable, Flag_ResShader, Flag_Shared };

    Bit8 state;
    nn::util::BitPack8 flags;
    char reserved[2];
    Bit32 nvnShaderStageBits;
    detail::Ptr<void> pNvnProgram;
    char nvnProgram[192];
    detail::Ptr<const void> pReflection;
    detail::Ptr<void> pOnlineCompiledShader;
    detail::Ptr<void> userPtr;
};

}  // namespace nn::gfx