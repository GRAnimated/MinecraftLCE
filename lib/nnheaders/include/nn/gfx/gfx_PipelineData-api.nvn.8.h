#pragma once

#include <nn/gfx/detail/gfx_State-api.nvn.8.h>
#include <nn/nn_BitTypes.h>
#include <nn/util/util_BitPack.h>

namespace nn::gfx {

template <>
struct PipelineImplData<ApiVariationNvn8> {
    enum PipelineType { PipelineType_Graphics, PipelineType_Compute };
    enum State { State_NotInitialized, State_Initialized };
    enum Flag { Flag_HasTessellationState };

    Bit8 state;
    Bit8 nnPipelineType;
    nn::util::BitPack8 flags;
    char reserved;
    Bit32 memorySize;

    detail::VertexStateImpl<ApiVariationNvn8>::DataType nnVertexState;
    detail::BlendStateImpl<ApiVariationNvn8>::DataType nnBlendState;
    detail::RasterizerStateImpl<ApiVariationNvn8>::DataType nnRasterizerState;
    detail::DepthStencilStateImpl<ApiVariationNvn8>::DataType nnDepthStencilState;
    detail::TessellationStateImpl<ApiVariationNvn8>::DataType nnTessellationState;

    detail::Ptr<const detail::ShaderImpl<ApiVariationNvn8>> pShader;
    detail::Ptr<void> pWorkMemory;

    detail::Ptr<void> userPtr;
};

}  // namespace nn::gfx