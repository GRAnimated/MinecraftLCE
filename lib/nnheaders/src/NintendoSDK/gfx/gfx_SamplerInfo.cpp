#include <nn/gfx/gfx_SamplerInfo.h>

namespace nn::gfx {

void SamplerInfo::SetDefault() {
    SetFilterMode(FilterMode_MinLinear_MagLinear_MipLinear);
    SetAddressU(TextureAddressMode_ClampToEdge);
    SetAddressV(TextureAddressMode_ClampToEdge);
    SetAddressW(TextureAddressMode_ClampToEdge);
    SetComparisonFunction(ComparisonFunction_Never);
    SetBorderColorType(TextureBorderColorType_White);
    SetMaxAnisotropy(1);
    SetMinLod(-1000.0f);
    SetMaxLod(1000.0f);
    SetLodBias(0.0f);
}

}  // namespace nn::gfx