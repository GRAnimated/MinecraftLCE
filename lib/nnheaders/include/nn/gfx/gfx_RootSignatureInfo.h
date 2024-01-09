#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_RootSignatureInfoData.h>

namespace nn::gfx {
class DescriptorRangeInfo : public detail::DataContainer<DescriptorRangeInfoData> {
public:
    DescriptorRangeInfo();
    void SetDefault();
    void SetDescriptorSlotType(DescriptorSlotType);
    void SetDescriptorSlotCount(int);
    void SetBaseShaderSlot(int);
    void SetBufferDescriptorSlotOffset(int);
    void SetTextureSamplerDescriptorSlotOffset(int, int);
    DescriptorSlotType GetDescriptorSlotType() const;
    int GetDescriptorSlotCount() const;
    int GetBaseShaderSlot() const;
    int GetBufferDescriptorSlotOffset() const;
    int GetTextureDescriptorSlotOffset() const;
    int GetSamplerDescriptorSlotOffset() const;
};

class DescriptorTableInfo : public detail::DataContainer<DescriptorTableInfoData> {
public:
    DescriptorTableInfo();
    void SetDefault();
    void SetShaderStage(ShaderStage);
    void SetDescriptorRangeInfoArray(const DescriptorRangeInfo*, int);
    ShaderStage GetShaderStage() const;
    const DescriptorRangeInfo* GetDescriptorRangeInfoArray() const;
    int GetDescriptorRangeCount() const;
};

class DynamicDescriptorInfo : public detail::DataContainer<DynamicDescriptorInfoData> {
public:
    DynamicDescriptorInfo();
    void SetDefault();
    void SetShaderStage(ShaderStage);
    void SetShaderSlot(int);
    ShaderStage GetShaderStage() const;
    int GetShaderSlot() const;
};

class RootSignatureInfo : public detail::DataContainer<RootSignatureInfoData> {
public:
    RootSignatureInfo();
    void SetDefault();
    void SetDescriptorTableInfoArray(const DescriptorTableInfo*, int);
    void SetDynamicDescriptorInfoArray(const DynamicDescriptorInfo*, int);
    const DescriptorTableInfo* GetDescriptorTableInfoArray() const;
    int GetDescriptorTableCount() const;
    const DynamicDescriptorInfo* GetDynamicDescriptorInfoArray() const;
    int GetDynamicDescriptorCount() const;
};

}  // namespace nn::gfx