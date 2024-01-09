#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/nn_BitTypes.h>

namespace nn::gfx {

struct DescriptorRangeInfoData {
    nn::Bit8 descriptorSlotType;
    char reserved2[3];
    uint32_t descriptorSlotCount;
    int32_t baseShaderSlot;
    char reserved3[4];
    union {
        uint32_t bufferDescriptorSlotOffset;

        struct {
            uint32_t textureDescriptorSlotOffset;
            uint32_t samplerDescriptorSlotOffset;
        } textureSamplerDescriptorSlotOffset;
    };
    char reserved[8];
};

struct DescriptorTableInfoData {
    Bit8 shaderStage;
    char reserved2[3];
    uint32_t descriptorRangeCount;
    detail::Ptr<const DescriptorRangeInfoData> pDescriptorRangeArray;
    char reserved[16];
};

struct DynamicDescriptorInfoData {
    Bit8 shaderStage;
    char reserved2[3];
    int32_t shaderSlot;
    char reserved[8];
};

struct RootSignatureInfoData {
    uint32_t descriptorTableCount;
    uint32_t dynamicDescriptorCount;
    detail::Ptr<const DescriptorTableInfoData> pDescriptorTableArray;
    detail::Ptr<const DynamicDescriptorInfoData> pDynamicDescriptorArray;
    char reserved[40];
};

}  // namespace nn::gfx
