#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_SamplerInfoData.h>

namespace nn::gfx {

class SamplerInfo : public detail::DataContainer<SamplerInfoData> {
public:
    SamplerInfo() {}

    void SetDefault();

    void SetFilterMode(FilterMode value) { filterMode = value; }
    void SetAddressU(TextureAddressMode value) { addressU = value; }
    void SetAddressV(TextureAddressMode value) { addressV = value; }
    void SetAddressW(TextureAddressMode value) { addressW = value; }
    void SetComparisonFunction(ComparisonFunction value) { comparisonFunction = value; }
    void SetBorderColorType(TextureBorderColorType value) { borderColorType = value; }
    void SetMaxAnisotropy(int value) { maxAnisotropy = value; }
    void SetMinLod(float value) { minLod = value; }
    void SetMaxLod(float value) { maxLod = value; }
    void SetLodBias(float value) { lodBias = value; }

    FilterMode GetFilterMode() const { return static_cast<FilterMode>(filterMode); }
    TextureAddressMode GetAddressU() const { return static_cast<TextureAddressMode>(addressU); }
    TextureAddressMode GetAddressV() const { return static_cast<TextureAddressMode>(addressV); }
    TextureAddressMode GetAddressW() const { return static_cast<TextureAddressMode>(addressW); }

    ComparisonFunction GetComparisonFunction() const {
        return static_cast<ComparisonFunction>(comparisonFunction);
    }

    TextureBorderColorType GetBorderColorType() const {
        return static_cast<TextureBorderColorType>(borderColorType);
    }

    int GetMaxAnisotropy() const { return maxAnisotropy; }
    float GetMinLod() const { return minLod; }
    float GetMaxLod() const { return maxLod; }
    float GetLodBias() const { return lodBias; }
};

}  // namespace nn::gfx