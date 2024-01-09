#pragma once

#include <nn/gfx/detail/gfx_RootSignature-api.common.h>
#include <nn/gfx/gfx_CommandBuffer.h>
#include <nn/gfx/gfx_DescriptorSlot.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_RootSignatureInfo.h>

namespace nn::gfx {
struct ResShaderContainerData;

namespace detail {

void UseMiddleWare();

int GetBlockWidth(ChannelFormat);
int GetBlockHeight(ChannelFormat);
bool IsCompressedFormat(ChannelFormat);
bool IsSrgbFormat(TypeFormat);
int GetBytePerPixel(ChannelFormat);
size_t CalculateImageSize(ChannelFormat, uint32_t, uint32_t, uint32_t);
int GetChannelCount(ChannelFormat);
size_t CalculateRowSize(uint32_t, ChannelFormat);
bool IsValidMemoryPoolProperty(int);
ImageDimension GetImageDimension(ImageStorageDimension, bool, bool);
bool CheckBinaryTarget(const ResShaderContainerData&, int, int);

inline ChannelFormat GetChannelFormat(ImageFormat format) {
    return static_cast<ChannelFormat>(format >> 8);
}

inline bool IsFilterModeAnisotropic(FilterMode filterMode) {
    return (filterMode >> 6) & 1;
}

// todo: confirm this function exists
inline bool IsFilterModeComparison(FilterMode filterMode) {
    return (filterMode >> 7) & 1;
}

template <typename TTarget>
const RootSignatureInfo::DataType& ToInfoData(const RootSignatureImpl<TTarget>* pRootSignature) {
    return *static_cast<const RootSignatureInfo::DataType*>(pRootSignature->ToData()->pWorkMemory);
}

template <typename TTarget>
const DescriptorTableInfo::DataType&
GetDescriptorTableInfoData(const RootSignatureImpl<TTarget>* pRootSignature,
                           int indexDescriptorTable) {
    const RootSignatureInfo::DataType& rootSignature = ToInfoData<TTarget>(pRootSignature);

    const DescriptorTableInfoData* pDescriptorTable = rootSignature.pDescriptorTableArray;

    return pDescriptorTable[indexDescriptorTable];
}

template <typename TTarget>
const DynamicDescriptorInfo::DataType&
GetDynamicDescriptorInfoData(const RootSignatureImpl<TTarget>* pRootSignature,
                             int indexDynamicDescriptor) {
    const RootSignatureInfo::DataType& rootSignature = ToInfoData<TTarget>(pRootSignature);

    const DynamicDescriptorInfoData* pDescriptorTable = rootSignature.pDynamicDescriptorArray;

    return pDescriptorTable[indexDynamicDescriptor];
}

template <typename TTarget>
void SetRootBufferDescriptorTable(CommandBufferImpl<TTarget>* pThis, PipelineType,
                                  int indexDescriptorTable,
                                  const DescriptorSlot& startBufferDescriptorSlot,
                                  ptrdiff_t descriptorSlotIncrementSize) {
    const DescriptorTableInfo::DataType& descriptorTable = GetDescriptorTableInfoData<TTarget>(
        pThis->ToData()->pGfxRootSignature, indexDescriptorTable);

    ShaderStage stage = static_cast<ShaderStage>(descriptorTable.shaderStage);

    for (int idxDescriptorRange = 0;
         idxDescriptorRange < static_cast<int>(descriptorTable.descriptorRangeCount);
         idxDescriptorRange++) {
        const DescriptorRangeInfoData* pDescriptorRange = descriptorTable.pDescriptorRangeArray;
        const DescriptorRangeInfo::DataType& descriptorRange = pDescriptorRange[idxDescriptorRange];
        DescriptorSlot slot = startBufferDescriptorSlot;
        slot.Offset(descriptorRange.bufferDescriptorSlotOffset * descriptorSlotIncrementSize);

        for (int idxDescriptor = 0;
             idxDescriptor < static_cast<int>(descriptorRange.descriptorSlotCount);
             ++idxDescriptor, slot.Offset(descriptorSlotIncrementSize)) {
            switch (descriptorRange.descriptorSlotType) {
            case DescriptorSlotType_ConstantBuffer:
                pThis->SetConstantBuffer(descriptorRange.baseShaderSlot + idxDescriptor, stage,
                                         slot);
                break;

            case DescriptorSlotType_UnorderedAccessBuffer:
                pThis->SetUnorderedAccessBuffer(descriptorRange.baseShaderSlot + idxDescriptor,
                                                stage, slot);
                break;

            default:
                NN_UNEXPECTED_DEFAULT;
                break;
            }
        }
    }
}

template <typename TTarget>
void SetRootTextureAndSamplerDescriptorTable(CommandBufferImpl<TTarget>* pThis, PipelineType,
                                             int indexDescriptorTable,
                                             const DescriptorSlot& startTextureDescriptorSlot,
                                             const DescriptorSlot& startSamplerDescriptorSlot,
                                             ptrdiff_t textureDescriptorSlotIncrementSize,
                                             ptrdiff_t samplerDescriptorSlotIncrementSize) {
    const DescriptorTableInfo::DataType& descriptorTable = GetDescriptorTableInfoData<TTarget>(
        pThis->ToData()->pGfxRootSignature, indexDescriptorTable);

    ShaderStage stage = static_cast<ShaderStage>(descriptorTable.shaderStage);

    for (int idxDescriptorRange = 0;
         idxDescriptorRange < static_cast<int>(descriptorTable.descriptorRangeCount);
         idxDescriptorRange++) {
        const DescriptorRangeInfoData* pDescriptorRange = descriptorTable.pDescriptorRangeArray;
        const DescriptorRangeInfo::DataType& descriptorRange = pDescriptorRange[idxDescriptorRange];
        DescriptorSlot textureSlot = startTextureDescriptorSlot;
        DescriptorSlot samplerSlot = startSamplerDescriptorSlot;
        textureSlot.Offset(
            descriptorRange.textureSamplerDescriptorSlotOffset.textureDescriptorSlotOffset *
            textureDescriptorSlotIncrementSize);
        samplerSlot.Offset(
            descriptorRange.textureSamplerDescriptorSlotOffset.samplerDescriptorSlotOffset *
            samplerDescriptorSlotIncrementSize);

        for (int idxDescriptor = 0;
             idxDescriptor < static_cast<int>(descriptorRange.descriptorSlotCount);
             ++idxDescriptor, textureSlot.Offset(textureDescriptorSlotIncrementSize),
                 samplerSlot.Offset(samplerDescriptorSlotIncrementSize)) {
            pThis->SetTextureAndSampler(descriptorRange.baseShaderSlot + idxDescriptor, stage,
                                        textureSlot, samplerSlot);
        }
    }
}

template <typename TTarget>
void SetRootConstantBuffer(CommandBufferImpl<TTarget>* pThis, PipelineType,
                           int indexDynamicDescriptor, const GpuAddress& constantBufferAddress,
                           size_t size) {
    const DynamicDescriptorInfo::DataType& dynamicDescriptor =
        GetDynamicDescriptorInfoData<TTarget>(pThis->ToData()->pGfxRootSignature,
                                              indexDynamicDescriptor);
    pThis->SetConstantBuffer(dynamicDescriptor.shaderSlot,
                             static_cast<ShaderStage>(dynamicDescriptor.shaderStage),
                             constantBufferAddress, size);
}

template <typename TTarget>
void SetRootUnorderedAccessBuffer(CommandBufferImpl<TTarget>* pThis, PipelineType,
                                  int indexDynamicDescriptor,
                                  const GpuAddress& unorderedAccessBufferAddress, size_t size) {
    const DynamicDescriptorInfo::DataType& dynamicDescriptor =
        GetDynamicDescriptorInfoData<TTarget>(pThis->ToData()->pGfxRootSignature,
                                              indexDynamicDescriptor);
    pThis->SetUnorderedAccessBuffer(dynamicDescriptor.shaderSlot,
                                    static_cast<ShaderStage>(dynamicDescriptor.shaderStage),
                                    unorderedAccessBufferAddress, size);
}

template <typename TTarget>
void SetRootTextureAndSampler(CommandBufferImpl<TTarget>* pThis, PipelineType,
                              int indexDynamicDescriptor,
                              const TextureViewImpl<TTarget>* pTextureView,
                              const SamplerImpl<TTarget>* pSampler) {
    const DynamicDescriptorInfo::DataType& dynamicDescriptor =
        GetDynamicDescriptorInfoData<TTarget>(pThis->ToData()->pGfxRootSignature,
                                              indexDynamicDescriptor);
    pThis->SetTextureAndSampler(dynamicDescriptor.shaderSlot,
                                static_cast<ShaderStage>(dynamicDescriptor.shaderStage),
                                pTextureView, pSampler);
}
}  // namespace detail
}  // namespace nn::gfx