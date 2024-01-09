#include <nn/gfx/gfx_StateInfo.h>

#include "detail/gfx_NvnHelper.h"

namespace nn::gfx {

void MultisampleStateInfo::SetDefault() {
    SetAlphaToCoverageEnabled(false);
    SetSampleCount(1);
    SetSampleMask(0xFFFFFFFF);
}

void RasterizerStateInfo::SetDefault() {
    SetFillMode(FillMode_Solid);
    SetFrontFace(FrontFace_Ccw);
    SetCullMode(CullMode_Back);
    SetPrimitiveTopologyType(PrimitiveTopologyType_Triangle);

    SetRasterEnabled(true);
    SetMultisampleEnabled(false);
#if NN_SDK_VER > NN_MAKE_VER(3, 5, 1)
    SetDepthClipEnabled(true);
#else
    SetDepthClipEnabled(false);
#endif
    SetScissorEnabled(false);

    SetSlopeScaledDepthBias(0.0f);
    SetDepthBias(0);
    SetDepthBiasClamp(0.0f);

    SetConservativeRasterizationMode(ConservativeRasterizationMode_Disable);

    EditMultisampleStateInfo().SetDefault();
}

void BlendTargetStateInfo::SetDefault() {
    SetBlendEnabled(false);
    SetSourceColorBlendFactor(BlendFactor_One);
    SetSourceAlphaBlendFactor(BlendFactor_One);
    SetDestinationColorBlendFactor(BlendFactor_Zero);
    SetColorBlendFunction(BlendFunction_Add);
    SetDestinationAlphaBlendFactor(BlendFactor_Zero);
    SetAlphaBlendFunction(BlendFunction_Add);
    SetChannelMask(ChannelMask_Red | ChannelMask_Green | ChannelMask_Blue | ChannelMask_Alpha);
}

void BlendStateInfo::SetDefault() {
    SetAlphaToCoverageEnabled(false);
    SetDualSourceBlendEnabled(false);
    SetIndependentBlendEnabled(false);
    SetLogicOperationEnabled(false);

    SetLogicOperation(LogicOperation_NoOp);
    SetBlendConstant(0.0f, 0.0f, 0.0f, 1.0f);

    SetBlendTargetStateInfoArray(nullptr, 0);
}

void StencilStateInfo::SetDefault() {
    SetStencilFailOperation(StencilOperation_Keep);
    SetDepthFailOperation(StencilOperation_Keep);
    SetDepthPassOperation(StencilOperation_Keep);
    SetComparisonFunction(ComparisonFunction_Always);
    SetStencilRef(0);
}

void DepthStencilStateInfo::SetDefault() {
    SetDepthComparisonFunction(ComparisonFunction_Less);

    SetDepthTestEnabled(false);
    SetDepthWriteEnabled(false);
    SetStencilTestEnabled(false);
    SetDepthBoundsTestEnabled(false);

    SetStencilReadMask(0xFF);
    SetStencilWriteMask(0xFF);

    EditFrontStencilStateInfo().SetDefault();
    EditBackStencilStateInfo().SetDefault();
}

void ColorTargetStateInfo::SetDefault() {
    SetFormat(ImageFormat_Undefined);
}

void RenderTargetStateInfo::SetDefault() {
    SetDepthStencilFormat(ImageFormat_Undefined);
    SetColorTargetStateInfoArray(nullptr, 0);
}

void VertexAttributeStateInfo::SetDefault() {
    SetSemanticIndex(0);
    SetShaderSlot(-1);
    SetBufferIndex(0);
    SetOffset(0);

    SetFormat(AttributeFormat_Undefined);
    SetNamePtr(nullptr);
}

void VertexBufferStateInfo::SetDefault() {
    SetStride(0);
    SetDivisor(0);
}

void VertexStateInfo::SetDefault() {
    SetVertexAttributeStateInfoArray(nullptr, 0);
    SetVertexBufferStateInfoArray(nullptr, 0);
}

void TessellationStateInfo::SetDefault() {
    SetPatchControlPointCount(1);
}

void ViewportStateInfo::SetDefault() {
    SetOriginX(0.0f);
    SetOriginY(0.0f);
    SetWidth(0.0f);
    SetHeight(0.0f);
    SetMinDepth(0.0f);
    SetMaxDepth(1.0f);
}

void ScissorStateInfo::SetDefault() {
    SetOriginX(0);
    SetOriginY(0);
    SetWidth(0);
    SetHeight(0);
}

void ViewportScissorStateInfo::SetDefault() {
    SetScissorEnabled(false);
    SetViewportStateInfoArray(nullptr, 0);
    SetScissorStateInfoArray(nullptr, 0);
}

}  // namespace nn::gfx