#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/nn_BitTypes.h>
#include <nn/util/util_BitPack.h>

namespace nn::gfx {

template <>
struct RasterizerStateImplData<ApiVariationNvn8> {
    enum Flag {
        Flag_MultisampleEnabled,
        Flag_DepthClipEnabled,
        Flag_RasterEnabled,
        Flag_ConservativeRasterEnabled
    };

    enum State { State_NotInitialized, State_Initialized };

    Bit32 nvnPolygonState;
    char nvnMultisampleState[24];
    Bit32 nvnSampleMask;
    float nvnDepthBias;
    float nvnDepthBiasClamp;
    float nvnSlopeScaledDepthBias;
    Bit8 state;
    nn::util::BitPack8 flags;
    char reserved[2];
};

template <>
struct BlendStateImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };

    detail::Ptr<void> pNvnBlendStateData;
    Bit32 nvnColorState;
    Bit32 nvnChannelMaskState;
    float nvnBlendConstant[4];
    Bit32 memorySize;
    Bit8 state;
    Bit8 targetCount;
    char reserved[2];
};

template <>
struct DepthStencilStateImplData<ApiVariationNvn8> {
    enum Flag { Flag_DepthBoundsTestEnable = 3 };

    enum State { State_NotInitialized, State_Initialized };

    char nvnDepthStencilState[8];
    Bit32 nvnStencilValueMask;
    Bit32 nvnStencilMask;
    Bit32 nvnStencilBackRef;
    Bit32 nvnStencilFrontRef;
    Bit8 state;
    char reserved;
    nn::util::BitPack16 flag;
};

template <>
struct VertexStateImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };

    Bit8 state;
    char reserved[3];
    int32_t vertexStreamStateCount;
    int32_t vertexAttributeStateCount;
    uint32_t memorySize;
    detail::Ptr<void> pNvnVertexStreamState;
    detail::Ptr<void> pNvnVertexAttribState;
};

template <>
struct TessellationStateImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };

    Bit8 state;
    char reserved[3];
    uint32_t patchSize;
};

template <>
struct ViewportScissorStateImplData<ApiVariationNvn8> {
    enum State { State_NotInitialized, State_Initialized };

    detail::Ptr<void> pWorkMemory;
    int32_t viewportCount;
    uint32_t memorySize;
    float viewport[4];
    double depthRange[2];
    int32_t scissor[4];
    Bit8 state;
    nn::util::BitPack8 flag;
    char reserved[2];
};

}  // namespace nn::gfx