#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_ShaderInfoData.h>

namespace nn::gfx {

class ShaderInfo : public detail::DataContainer<ShaderInfoData> {
public:
    ShaderInfo() {}

    void SetDefault();

    void SetSeparationEnabled(bool value) { flags.SetBit(Flag_SeparationEnable, value); }
    void SetCodeType(ShaderCodeType value) { codeType = value; }
    void SetSourceFormat(ShaderSourceFormat value) { sourceFormat = value; }
    void SetBinaryFormat(int value) { binaryFormat = value; }
    void SetShaderCodePtr(ShaderStage, const void*);

    bool IsSeparationEnabled() const { return flags.GetBit(Flag_SeparationEnable); }
    ShaderCodeType GetCodeType() const { return static_cast<ShaderCodeType>(codeType); }
    int GetBinaryFormat() const { return binaryFormat; }

    ShaderSourceFormat GetSourceFormat() const {
        return static_cast<ShaderSourceFormat>(sourceFormat);
    }

    const void* GetShaderCodePtr(ShaderStage) const;
};

}  // namespace nn::gfx