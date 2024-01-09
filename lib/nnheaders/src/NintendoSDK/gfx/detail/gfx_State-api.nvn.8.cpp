#include <nn/gfx/detail/gfx_State-api.nvn.8.h>

#include <nn/gfx/detail/gfx_Shader-api.nvn.8.h>
#include <nn/gfx/gfx_StateInfo.h>
#include <nn/util/util_BitArray.h>
#include <nn/util/util_BytePtr.h>

#include <algorithm>

#include "gfx_NvnHelper.h"

namespace nn::gfx::detail {

RasterizerStateImpl<ApiVariationNvn8>::RasterizerStateImpl() {}

RasterizerStateImpl<ApiVariationNvn8>::~RasterizerStateImpl() {}

void RasterizerStateImpl<ApiVariationNvn8>::Initialize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice, const InfoType& info) {
    NVNpolygonState* pPolygonState = reinterpret_cast<NVNpolygonState*>(&nvnPolygonState);
    NVNmultisampleState* pMultisampleState =
        reinterpret_cast<NVNmultisampleState*>(&nvnMultisampleState);

    nvnPolygonStateSetDefaults(pPolygonState);
    nvnPolygonStateSetCullFace(pPolygonState, Nvn::GetCullMode(info.GetCullMode()));
    nvnPolygonStateSetFrontFace(pPolygonState, Nvn::GetFrontFace(info.GetFrontFace()));
    nvnPolygonStateSetPolygonMode(pPolygonState, Nvn::GetFillMode(info.GetFillMode()));

    nvnDepthBias = info.GetDepthBias();
    nvnDepthBiasClamp = info.GetDepthBiasClamp();
    nvnSlopeScaledDepthBias = info.GetSlopeScaledDepthBias();

    bool polyEnables =
        (nvnDepthBias != 0.0f || nvnDepthBiasClamp != 0.0f || nvnSlopeScaledDepthBias != 0);
    nvnPolygonStateSetPolygonOffsetEnables(pPolygonState, (polyEnables) ?
                                                              (NVN_POLYGON_OFFSET_ENABLE_POINT |
                                                               NVN_POLYGON_OFFSET_ENABLE_LINE |
                                                               NVN_POLYGON_OFFSET_ENABLE_FILL) :
                                                              NVN_POLYGON_OFFSET_ENABLE_NONE);

    nvnSampleMask = info.GetMultisampleStateInfo().GetSampleMask();
    nvnMultisampleStateSetDefaults(pMultisampleState);
    nvnMultisampleStateSetMultisampleEnable(pMultisampleState, info.IsMultisampleEnabled());
#if NN_SDK_VER > NN_MAKE_VER(3, 5, 1)
    int sampleCount = info.GetMultisampleStateInfo().GetSampleCount();
    nvnMultisampleStateSetSamples(pMultisampleState, (sampleCount > 1) ? sampleCount : 0);
#else
    nvnMultisampleStateSetSamples(pMultisampleState,
                                  info.GetMultisampleStateInfo().GetSampleCount());
#endif
    nvnMultisampleStateSetAlphaToCoverageEnable(
        pMultisampleState, info.GetMultisampleStateInfo().IsAlphaToCoverageEnabled());

    flags.SetBit(Flag_MultisampleEnabled, info.IsMultisampleEnabled());
    flags.SetBit(Flag_DepthClipEnabled, info.IsDepthClipEnabled());
    flags.SetBit(Flag_RasterEnabled, info.IsRasterEnabled());
    flags.SetBit(Flag_ConservativeRasterEnabled,
                 info.GetConservativeRasterizationMode() == ConservativeRasterizationMode_Enable);

    state = State_Initialized;
}

void RasterizerStateImpl<ApiVariationNvn8>::Finalize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice) {
    state = State_NotInitialized;
}

size_t BlendStateImpl<ApiVariationNvn8>::GetRequiredMemorySize(const InfoType& info) {
    return 8 * info.GetBlendTargetCount();
}

BlendStateImpl<ApiVariationNvn8>::BlendStateImpl() {}

BlendStateImpl<ApiVariationNvn8>::~BlendStateImpl() {}

void BlendStateImpl<ApiVariationNvn8>::SetMemory(void* p, size_t s) {
    pNvnBlendStateData = p;
    memorySize = s;
}

void* BlendStateImpl<ApiVariationNvn8>::GetMemory() {
    return pNvnBlendStateData;
}

void* BlendStateImpl<ApiVariationNvn8>::GetMemory() const {
    return pNvnBlendStateData;
}

void BlendStateImpl<ApiVariationNvn8>::Initialize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice, const InfoType& info) {
    auto pColorState = reinterpret_cast<NVNcolorState*>(&nvnColorState);
    auto pChannelMaskState = reinterpret_cast<NVNchannelMaskState*>(&nvnChannelMaskState);
    NVNblendState* pBlendStateData = pNvnBlendStateData;
    const BlendTargetStateInfo* pBlendInfo = info.GetBlendTargetStateInfoArray();

    nvnBlendConstant[0] = info.GetBlendConstant(ColorChannel_Red);
    nvnBlendConstant[1] = info.GetBlendConstant(ColorChannel_Green);
    nvnBlendConstant[2] = info.GetBlendConstant(ColorChannel_Blue);
    nvnBlendConstant[3] = info.GetBlendConstant(ColorChannel_Alpha);

    nvnColorStateSetDefaults(pColorState);
    nvnChannelMaskStateSetDefaults(pChannelMaskState);

    targetCount = info.GetBlendTargetCount();

    for (int index = 0; index < info.GetBlendTargetCount(); ++index) {
        int infoIndex = (info.IsIndependentBlendEnabled()) ? index : 0;

#if NN_SDK_VER > NN_MAKE_VER(3, 5, 1)
        nvnColorStateSetBlendEnable(pColorState, index, pBlendInfo[infoIndex].IsBlendEnabled());
#else
        nvnColorStateSetBlendEnable(pColorState, index, pBlendInfo[index].IsBlendEnabled());
#endif
        nvnBlendStateSetDefaults(&pBlendStateData[index]);
        nvnBlendStateSetBlendTarget(&pBlendStateData[index], index);

        nvnBlendStateSetBlendFunc(
            &pBlendStateData[index],
            Nvn::GetBlendFunction(pBlendInfo[infoIndex].GetSourceColorBlendFactor()),
            Nvn::GetBlendFunction(pBlendInfo[infoIndex].GetDestinationColorBlendFactor()),
            Nvn::GetBlendFunction(pBlendInfo[infoIndex].GetSourceAlphaBlendFactor()),
            Nvn::GetBlendFunction(pBlendInfo[infoIndex].GetDestinationAlphaBlendFactor()));

        nvnBlendStateSetBlendEquation(
            &pBlendStateData[index],
            Nvn::GetBlendEquation(pBlendInfo[infoIndex].GetColorBlendFunction()),
            Nvn::GetBlendEquation(pBlendInfo[infoIndex].GetAlphaBlendFunction()));

        ChannelMask channelMask = static_cast<ChannelMask>(pBlendInfo[infoIndex].GetChannelMask());
        nvnChannelMaskStateSetChannelMask(pChannelMaskState, index,
                                          (channelMask & ChannelMask_Red) == ChannelMask_Red,
                                          (channelMask & ChannelMask_Green) == ChannelMask_Green,
                                          (channelMask & ChannelMask_Blue) == ChannelMask_Blue,
                                          (channelMask & ChannelMask_Alpha) == ChannelMask_Alpha);
    }

    if (info.IsLogicOperationEnabled()) {
        nvnColorStateSetLogicOp(pColorState, Nvn::GetLogicOperation(info.GetLogicOperation()));
    }

    state = State_Initialized;
}

void BlendStateImpl<ApiVariationNvn8>::Finalize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice) {
    state = State_NotInitialized;
}

DepthStencilStateImpl<ApiVariationNvn8>::DepthStencilStateImpl() {}

DepthStencilStateImpl<ApiVariationNvn8>::~DepthStencilStateImpl() {}

void DepthStencilStateImpl<ApiVariationNvn8>::Initialize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice, const DepthStencilStateInfo& info) {
    auto pDepthStencilState = reinterpret_cast<NVNdepthStencilState*>(&nvnDepthStencilState);

    flag = info.ToData()->flag;

    nvnDepthStencilStateSetDefaults(pDepthStencilState);
    nvnDepthStencilStateSetDepthTestEnable(pDepthStencilState, info.IsDepthTestEnabled());
    nvnDepthStencilStateSetDepthWriteEnable(pDepthStencilState, info.IsDepthWriteEnabled());
    nvnDepthStencilStateSetStencilTestEnable(pDepthStencilState, info.IsStencilTestEnabled());

    nvnDepthStencilStateSetDepthFunc(pDepthStencilState,
                                     Nvn::GetDepthFunction(info.GetDepthComparisonFunction()));

    nvnDepthStencilStateSetStencilFunc(
        pDepthStencilState, NVN_FACE_BACK,
        Nvn::GetStencilFunction(info.GetBackStencilStateInfo().GetComparisonFunction()));

    nvnDepthStencilStateSetStencilOp(
        pDepthStencilState, NVN_FACE_BACK,
        Nvn::GetStencilOperation(info.GetBackStencilStateInfo().GetStencilFailOperation()),
        Nvn::GetStencilOperation(info.GetBackStencilStateInfo().GetDepthFailOperation()),
        Nvn::GetStencilOperation(info.GetBackStencilStateInfo().GetDepthPassOperation()));

    nvnDepthStencilStateSetStencilFunc(
        pDepthStencilState, NVN_FACE_FRONT,
        Nvn::GetStencilFunction(info.GetFrontStencilStateInfo().GetComparisonFunction()));

    nvnDepthStencilStateSetStencilOp(
        pDepthStencilState, NVN_FACE_FRONT,
        Nvn::GetStencilOperation(info.GetFrontStencilStateInfo().GetStencilFailOperation()),
        Nvn::GetStencilOperation(info.GetFrontStencilStateInfo().GetDepthFailOperation()),
        Nvn::GetStencilOperation(info.GetFrontStencilStateInfo().GetDepthPassOperation()));

    nvnStencilBackRef = info.GetBackStencilStateInfo().GetStencilRef();
    nvnStencilFrontRef = info.GetFrontStencilStateInfo().GetStencilRef();
    nvnStencilValueMask = info.GetStencilReadMask();
    nvnStencilMask = info.GetStencilWriteMask();

    state = State_Initialized;
}

void DepthStencilStateImpl<ApiVariationNvn8>::Finalize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice) {
    state = State_NotInitialized;
}

size_t VertexStateImpl<ApiVariationNvn8>::GetRequiredMemorySize(const InfoType& info) {
    int maxSlot = -1;
    const VertexAttributeStateInfo* pAttribStates = info.GetVertexAttributeStateInfoArray();

    for (int idxAttribute = 0, attributeCount = info.GetVertexAttributeCount();
         idxAttribute < attributeCount; ++idxAttribute) {
        const VertexAttributeStateInfo& attribState = pAttribStates[idxAttribute];

        if (attribState.GetShaderSlot() < 0) {
            maxSlot = 15;
        } else {
            maxSlot = std::max(maxSlot, attribState.GetShaderSlot());
        }
    }

    // todo: figure out magic numbers
    return size_t(8) * info.GetVertexBufferCount() + size_t(4) * (maxSlot + 1);
}

VertexStateImpl<ApiVariationNvn8>::VertexStateImpl() {}

VertexStateImpl<ApiVariationNvn8>::~VertexStateImpl() {}

void VertexStateImpl<ApiVariationNvn8>::SetMemory(void* p, size_t s) {
    pNvnVertexStreamState = p;
    memorySize = s;
}

void* VertexStateImpl<ApiVariationNvn8>::GetMemory() {
    return pNvnVertexStreamState;
}

const void* VertexStateImpl<ApiVariationNvn8>::GetMemory() const {
    return pNvnVertexStreamState;
}

void VertexStateImpl<ApiVariationNvn8>::Initialize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice, const VertexStateInfo& info,
    const ShaderImpl<ApiVariationNvn8>* pVertexShader) {
    vertexStreamStateCount = info.GetVertexBufferCount();
    pNvnVertexAttribState = nn::util::BytePtr(pNvnVertexStreamState.ptr)
                                .Advance(size_t(8) * info.GetVertexBufferCount())
                                .Get();

    for (int idxVertexBufferState = 0; idxVertexBufferState < info.GetVertexBufferCount();
         ++idxVertexBufferState) {
        const VertexBufferStateInfo& src =
            info.GetVertexBufferStateInfoArray()[idxVertexBufferState];
        NVNvertexStreamState* pDst =
            static_cast<NVNvertexStreamState*>(pNvnVertexStreamState) + idxVertexBufferState;

        nvnVertexStreamStateSetDefaults(pDst);
        nvnVertexStreamStateSetStride(pDst, src.GetStride());
        nvnVertexStreamStateSetDivisor(pDst, src.GetDivisor());
    }

    const int maxAttribs = 256;
    Bit32 bitArrayMemory[8] = {};
    nn::util::BitArray setAttribs(bitArrayMemory, sizeof(bitArrayMemory), maxAttribs);
    int maxSlot = -1;

    for (int idxVertexAttribState = 0; idxVertexAttribState < info.GetVertexAttributeCount();
         ++idxVertexAttribState) {
        const VertexAttributeStateInfo& src =
            info.GetVertexAttributeStateInfoArray()[idxVertexAttribState];

        int idxDst = src.GetShaderSlot();
        if (pVertexShader && src.GetNamePtr()) {
            idxDst = pVertexShader->GetInterfaceSlot(ShaderStage_Vertex, ShaderInterfaceType_Input,
                                                     src.GetNamePtr());
        }

        if (idxDst >= 0) {
            NVNvertexAttribState* pDst =
                static_cast<NVNvertexAttribState*>(pNvnVertexAttribState) + idxDst;

            nvnVertexAttribStateSetDefaults(pDst);
            nvnVertexAttribStateSetFormat(pDst, Nvn::GetAttributeFormat(src.GetFormat()),
                                          src.GetOffset());
            nvnVertexAttribStateSetStreamIndex(pDst, src.GetBufferIndex());

            setAttribs.set(idxDst, true);
            maxSlot = std::max(maxSlot, idxDst);
        }
    }

    vertexAttributeStateCount = info.GetVertexAttributeCount() ? maxSlot + 1 : 0;

    if (maxSlot >= info.GetVertexAttributeCount()) {
        for (int idxSlot = 0; idxSlot <= maxSlot; ++idxSlot) {
            if (!setAttribs.test(idxSlot)) {
                nvnVertexAttribStateSetDefaults(
                    static_cast<NVNvertexAttribState*>(pNvnVertexAttribState) + idxSlot);
            }
        }
    }

    state = State_Initialized;
}

void VertexStateImpl<ApiVariationNvn8>::Finalize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice) {
    state = State_NotInitialized;
}

TessellationStateImpl<ApiVariationNvn8>::TessellationStateImpl() {
    state = State_NotInitialized;
}

TessellationStateImpl<ApiVariationNvn8>::~TessellationStateImpl() {}

void TessellationStateImpl<ApiVariationNvn8>::Initialize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice, const TessellationStateInfo& info) {
    patchSize = info.GetPatchControlPointCount();
    state = State_Initialized;
}

void TessellationStateImpl<ApiVariationNvn8>::Finalize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice) {
    state = State_NotInitialized;
}

size_t ViewportScissorStateImpl<ApiVariationNvn8>::GetRequiredMemorySize(
    const ViewportScissorStateInfo& info) {
    int extraViewportCount = info.GetViewportCount() - 1;
    return size_t(40) * extraViewportCount;
}

ViewportScissorStateImpl<ApiVariationNvn8>::ViewportScissorStateImpl() {
    state = State_NotInitialized;
}

ViewportScissorStateImpl<ApiVariationNvn8>::~ViewportScissorStateImpl() {}

void ViewportScissorStateImpl<ApiVariationNvn8>::SetMemory(void* pMemory, size_t size) {
    pWorkMemory = pMemory;
    memorySize = size;
}

void* ViewportScissorStateImpl<ApiVariationNvn8>::GetMemory() {
    return pWorkMemory;
}

const void* ViewportScissorStateImpl<ApiVariationNvn8>::GetMemory() const {
    return pWorkMemory;
}

void ViewportScissorStateImpl<ApiVariationNvn8>::Initialize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice, const ViewportScissorStateInfo& info) {
    flag = info.ToData()->flag;
    viewportCount = info.GetViewportCount();

    const ViewportStateInfo* pViewports = info.GetViewportStateInfoArray();
    const ScissorStateInfo* pScissor = info.GetScissorStateInfoArray();

    viewport[0] = pViewports->GetOriginX();
    viewport[1] = pViewports->GetOriginY();
    viewport[2] = pViewports->GetWidth();
    viewport[3] = pViewports->GetHeight();
    depthRange[0] = pViewports->GetMinDepth();
    depthRange[1] = pViewports->GetMaxDepth();

    if (info.IsScissorEnabled()) {
        scissor[0] = pScissor->GetOriginX();
        scissor[1] = pScissor->GetOriginY();
        scissor[2] = pScissor->GetWidth();
        scissor[3] = pScissor->GetHeight();
    } else {
        scissor[0] = 0;
        scissor[1] = 0;
        scissor[2] = 0x7FFFFFFF;
        scissor[3] = 0x7FFFFFFF;
    }

    int extraViewportCount = info.GetViewportCount() - 1;

    nn::util::BytePtr ptr(pWorkMemory.ptr);
    float* viewportArray = ptr.Get<float>();
    float* depthRangeArray = ptr.Advance(size_t(16) * extraViewportCount).Get<float>();
    int32_t* scissorArray = ptr.Advance(size_t(8) * extraViewportCount).Get<int32_t>();

    for (int idx = 1; idx < viewportCount; ++idx) {
        int idxExtra = idx - 1;
        const ViewportStateInfo& viewportInfo = pViewports[idx];

        viewportArray[4 * idxExtra + 0] = viewportInfo.GetOriginX();
        viewportArray[4 * idxExtra + 1] = viewportInfo.GetOriginY();
        viewportArray[4 * idxExtra + 2] = viewportInfo.GetWidth();
        viewportArray[4 * idxExtra + 3] = viewportInfo.GetHeight();
        depthRangeArray[2 * idxExtra + 0] = viewportInfo.GetMinDepth();
        depthRangeArray[2 * idxExtra + 1] = viewportInfo.GetMaxDepth();
    }

    for (int idx = 1; idx < viewportCount; ++idx) {
        int idxExtra = idx - 1;
        const ScissorStateInfo& scissorInfo = pScissor[idx];

        if (info.IsScissorEnabled()) {
            scissorArray[4 * idxExtra + 0] = scissorInfo.GetOriginX();
            scissorArray[4 * idxExtra + 1] = scissorInfo.GetOriginY();
            scissorArray[4 * idxExtra + 2] = scissorInfo.GetWidth();
            scissorArray[4 * idxExtra + 3] = scissorInfo.GetHeight();
        } else {
            scissorArray[4 * idxExtra + 0] = 0;
            scissorArray[4 * idxExtra + 1] = 0;
            scissorArray[4 * idxExtra + 2] = 0x7FFFFFFF;
            scissorArray[4 * idxExtra + 3] = 0x7FFFFFFF;
        }
    }

    state = State_Initialized;
}
void ViewportScissorStateImpl<ApiVariationNvn8>::Finalize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice) {
    state = State_NotInitialized;
}

}  // namespace nn::gfx::detail