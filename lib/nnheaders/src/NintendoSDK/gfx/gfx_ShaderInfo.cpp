#include <nn/gfx/gfx_ShaderInfo.h>

namespace nn::gfx {

namespace {

static detail::Ptr<const void> ShaderInfoData::*const g_pShaderCodes[] = {
    &ShaderInfoData::pVertexShaderCode, &ShaderInfoData::pHullShaderCode,
    &ShaderInfoData::pDomainShaderCode, &ShaderInfoData::pGeometryShaderCode,
    &ShaderInfoData::pPixelShaderCode,  &ShaderInfoData::pComputeShaderCode,
};

}

void ShaderInfo::SetDefault() {
    SetSeparationEnabled(false);
    SetCodeType(ShaderCodeType_Source);
    SetSourceFormat(ShaderSourceFormat_Glsl);
    SetBinaryFormat(0);
    SetShaderCodePtr(ShaderStage_Vertex, nullptr);
    SetShaderCodePtr(ShaderStage_Hull, nullptr);
    SetShaderCodePtr(ShaderStage_Domain, nullptr);
    SetShaderCodePtr(ShaderStage_Geometry, nullptr);
    SetShaderCodePtr(ShaderStage_Pixel, nullptr);
    SetShaderCodePtr(ShaderStage_Compute, nullptr);
}

void ShaderInfo::SetShaderCodePtr(ShaderStage shaderStage, const void* pCode) {
    this->*g_pShaderCodes[shaderStage] = pCode;
}

const void* ShaderInfo::GetShaderCodePtr(ShaderStage shaderStage) const {
    return this->*g_pShaderCodes[shaderStage];
}

}  // namespace nn::gfx