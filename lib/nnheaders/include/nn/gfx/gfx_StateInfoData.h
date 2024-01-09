#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/nn_BitTypes.h>
#include <nn/util/util_BitPack.h>

namespace nn::gfx {

struct MultisampleStateInfoData {
    enum Flag { Flag_AlphaToCoverageEnable };

    uint8_t sampleCount;
    char reserved2;
    nn::util::BitPack16 flag;
    uint32_t sampleMask;
    char reserved[8];
};

struct RasterizerStateInfoData {
    enum Flag {
        Flag_RasterDisable,
        Flag_MultisampleEnable,
        Flag_DepthClipDisable,
        Flag_ScissorEnable
    };

    Bit8 fillMode;
    Bit8 frontFace;
    Bit8 cullMode;
    Bit8 primitiveTopologyType;
    nn::util::BitPack16 flag;
    Bit8 conservativeRasterizationMode;
    char reserved2;
    float slopeScaledDepthBias;
    int32_t depthBias;
    float depthBiasClamp;
    char reserved3[4];
    MultisampleStateInfoData multisample;
    char reserved[24];
};

struct BlendTargetStateInfoData {
    enum Flag { Flag_BlendEnable };

    nn::util::BitPack8 flag;
    Bit8 sourceColorBlendFactor;
    Bit8 destinationColorBlendFactor;
    Bit8 colorBlendFunction;
    Bit8 sourceAlphaBlendFactor;
    Bit8 destinationAlphaBlendFactor;
    Bit8 alphaBlendFunction;
    Bit8 channelMask;
    char reserved[24];
};

struct BlendStateInfoData {
    enum Flag {
        Flag_AlphaToCoverageEnable,
        Flag_DualSourceBlendEnable,
        Flag_IndependentBlendEnable,
        Flag_LogicOperationEnable
    };

    uint8_t blendTargetCount;
    Bit8 logicOperation;
    nn::util::BitPack16 flag;
    float blendConstant[4];
    char reserved2[4];
    detail::Ptr<const BlendTargetStateInfoData> pBlendTargetArray;
    char reserved[16];
};

struct StencilStateInfoData {
    Bit8 stencilFailOperation;
    Bit8 depthFailOperation;
    Bit8 depthPassOperation;
    Bit8 comparisonFunction;
    uint8_t stencilRef;
    char reserved[11];
};

struct DepthStencilStateInfoData {
    enum Flag {
        Flag_DepthTestEnable,
        Flag_DepthWriteEnable,
        Flag_StencilTestEnable,
        Flag_DepthBoundsTestEnable
    };

    Bit8 depthComparisonFunction;
    uint8_t stencilReadMask;
    uint8_t stencilWriteMask;
    char reserved2;
    nn::util::BitPack16 flag;
    char reserved3[2];
    StencilStateInfoData frontStencil;
    StencilStateInfoData backStencil;
    char reserved[24];
};

struct ColorTargetStateInfoData {
    Bit32 format;
    char reserved[28];
};

struct RenderTargetStateInfoData {
    uint8_t colorTargetCount;
    char reserved2[3];
    Bit32 depthStencilFormat;
    detail::Ptr<const ColorTargetStateInfoData> pColorTargetStateArray;
    char reserved[16];
};

struct VertexAttributeStateInfoData {
    uint8_t semanticIndex;
    char reserved2;
    int16_t shaderSlot;
    uint16_t bufferIndex;
    char reserved3[2];
    uint32_t offset;
    Bit32 format;
    detail::Ptr<const char> pName;
    char reserved[16];
};

struct VertexBufferStateInfoData {
    int32_t stride;
    uint32_t divisor;
    char reserved[8];
};

struct VertexStateInfoData {
    uint16_t attributeCount;
    uint16_t bufferCount;
    char reserved2[4];
    detail::Ptr<const VertexAttributeStateInfoData> pAttributeArray;
    detail::Ptr<const VertexBufferStateInfoData> pBufferArray;
    char reserved[24];
};

struct TessellationStateInfoData {
    uint16_t patchControlPointCount;
    char reserved[30];
};

struct DepthRangeInfoData {
    float minDepth;
    float maxDepth;
    char reserved[8];
};

struct ViewportStateInfoData {
    float originX;
    float originY;
    float width;
    float height;
    DepthRangeInfoData depthRange;
    char reserved[16];
};

struct ScissorStateInfoData {
    uint32_t originX;
    uint32_t originY;
    uint32_t width;
    uint32_t height;
    char reserved[16];
};

struct ViewportScissorStateInfoData {
    enum Flag { Flag_ScissorEnable };

    nn::util::BitPack8 flag;
    char reserved2;
    uint16_t viewportCount;
    uint16_t scissorCount;
    char reserved3[2];
    detail::Ptr<const ViewportStateInfoData> pViewportArray;
    detail::Ptr<const ScissorStateInfoData> pScissorArray;
    char reserved[8];
};

}  // namespace nn::gfx