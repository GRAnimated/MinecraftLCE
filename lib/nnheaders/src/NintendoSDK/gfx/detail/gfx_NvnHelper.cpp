#include "gfx_NvnHelper.h"

#include <nn/gfx/gfx_SwapChainInfo.h>
#include <nn/gfx/gfx_TextureInfo.h>
#include <nvn/nvn_FuncPtrImpl.h>

#include <algorithm>

namespace nn::gfx::detail {

namespace {

struct ImageFormatAndNvnFormat {
    ImageFormat imageFormat;
    NVNformat nvnFormat;
};

ImageFormatAndNvnFormat s_NvnTextureFormatList[] = {
    {ImageFormat_R8_Unorm, NVN_FORMAT_R8},
    {ImageFormat_R8_Snorm, NVN_FORMAT_R8SN},
    {ImageFormat_R8_Uint, NVN_FORMAT_R8UI},
    {ImageFormat_R8_Sint, NVN_FORMAT_R8I},
    {ImageFormat_R4_G4_B4_A4_Unorm, NVN_FORMAT_RGBA4},
    {ImageFormat_R5_G5_B5_A1_Unorm, NVN_FORMAT_RGB5A1},
    {ImageFormat_A1_B5_G5_R5_Unorm, NVN_FORMAT_A1BGR5},
    {ImageFormat_R5_G6_B5_Unorm, NVN_FORMAT_RGB565},
    {ImageFormat_B5_G6_R5_Unorm, NVN_FORMAT_BGR565},
    {ImageFormat_R8_G8_Unorm, NVN_FORMAT_RG8},
    {ImageFormat_R8_G8_Snorm, NVN_FORMAT_RG8SN},
    {ImageFormat_R8_G8_Uint, NVN_FORMAT_RG8UI},
    {ImageFormat_R8_G8_Sint, NVN_FORMAT_RG8I},
    {ImageFormat_R16_Unorm, NVN_FORMAT_R16},
    {ImageFormat_R16_Snorm, NVN_FORMAT_R16SN},
    {ImageFormat_R16_Uint, NVN_FORMAT_R16UI},
    {ImageFormat_R16_Sint, NVN_FORMAT_R16I},
    {ImageFormat_R16_Float, NVN_FORMAT_R16F},
    {ImageFormat_D16_Unorm, NVN_FORMAT_DEPTH16},
    {ImageFormat_R8_G8_B8_A8_Unorm, NVN_FORMAT_RGBA8},
    {ImageFormat_R8_G8_B8_A8_Snorm, NVN_FORMAT_RGBA8SN},
    {ImageFormat_R8_G8_B8_A8_Uint, NVN_FORMAT_RGBA8UI},
    {ImageFormat_R8_G8_B8_A8_Sint, NVN_FORMAT_RGBA8I},
    {ImageFormat_R8_G8_B8_A8_UnormSrgb, NVN_FORMAT_RGBA8_SRGB},
    {ImageFormat_B8_G8_R8_A8_Unorm, NVN_FORMAT_BGRA8},
    {ImageFormat_B8_G8_R8_A8_UnormSrgb, NVN_FORMAT_BGRA8_SRGB},
    {ImageFormat_R9_G9_B9_E5_SharedExp, NVN_FORMAT_RGB9E5F},
    {ImageFormat_R10_G10_B10_A2_Unorm, NVN_FORMAT_RGB10A2},
    {ImageFormat_R10_G10_B10_A2_Uint, NVN_FORMAT_RGB10A2UI},
    {ImageFormat_R11_G11_B10_Float, NVN_FORMAT_R11G11B10F},
    {ImageFormat_R16_G16_Unorm, NVN_FORMAT_RG16},
    {ImageFormat_R16_G16_Snorm, NVN_FORMAT_RG16SN},
    {ImageFormat_R16_G16_Uint, NVN_FORMAT_RG16UI},
    {ImageFormat_R16_G16_Sint, NVN_FORMAT_RG16I},
    {ImageFormat_R16_G16_Float, NVN_FORMAT_RG16F},
    {ImageFormat_D24_Unorm_S8_Uint, NVN_FORMAT_DEPTH24_STENCIL8},
    {ImageFormat_R32_Uint, NVN_FORMAT_R32UI},
    {ImageFormat_R32_Sint, NVN_FORMAT_R32I},
    {ImageFormat_R32_Float, NVN_FORMAT_R32F},
    {ImageFormat_D32_Float, NVN_FORMAT_DEPTH32F},
    {ImageFormat_R16_G16_B16_A16_Unorm, NVN_FORMAT_RGBA16},
    {ImageFormat_R16_G16_B16_A16_Snorm, NVN_FORMAT_RGBA16SN},
    {ImageFormat_R16_G16_B16_A16_Uint, NVN_FORMAT_RGBA16UI},
    {ImageFormat_R16_G16_B16_A16_Sint, NVN_FORMAT_RGBA16I},
    {ImageFormat_R16_G16_B16_A16_Float, NVN_FORMAT_RGBA16F},
    {ImageFormat_D32_Float_S8_Uint_X24, NVN_FORMAT_DEPTH32F_STENCIL8},
    {ImageFormat_R32_G32_Uint, NVN_FORMAT_RG32UI},
    {ImageFormat_R32_G32_Sint, NVN_FORMAT_RG32I},
    {ImageFormat_R32_G32_Float, NVN_FORMAT_RG32F},
    {ImageFormat_R32_G32_B32_Uint, NVN_FORMAT_RGB32UI},
    {ImageFormat_R32_G32_B32_Sint, NVN_FORMAT_RGB32I},
    {ImageFormat_R32_G32_B32_Float, NVN_FORMAT_RGB32F},
    {ImageFormat_R32_G32_B32_A32_Uint, NVN_FORMAT_RGBA32UI},
    {ImageFormat_R32_G32_B32_A32_Sint, NVN_FORMAT_RGBA32I},
    {ImageFormat_R32_G32_B32_A32_Float, NVN_FORMAT_RGBA32F},
    {ImageFormat_Bc1_Unorm, NVN_FORMAT_RGBA_DXT1},
    {ImageFormat_Bc1_UnormSrgb, NVN_FORMAT_RGBA_DXT1_SRGB},
    {ImageFormat_Bc2_Unorm, NVN_FORMAT_RGBA_DXT3},
    {ImageFormat_Bc2_UnormSrgb, NVN_FORMAT_RGBA_DXT3_SRGB},
    {ImageFormat_Bc3_Unorm, NVN_FORMAT_RGBA_DXT5},
    {ImageFormat_Bc3_UnormSrgb, NVN_FORMAT_RGBA_DXT5_SRGB},
    {ImageFormat_Bc4_Unorm, NVN_FORMAT_RGTC1_UNORM},
    {ImageFormat_Bc4_Snorm, NVN_FORMAT_RGTC1_SNORM},
    {ImageFormat_Bc5_Unorm, NVN_FORMAT_RGTC2_UNORM},
    {ImageFormat_Bc5_Snorm, NVN_FORMAT_RGTC2_SNORM},
    {ImageFormat_Bc6_Float, NVN_FORMAT_BPTC_SFLOAT},
    {ImageFormat_Bc6_Ufloat, NVN_FORMAT_BPTC_UFLOAT},
    {ImageFormat_Bc7_Unorm, NVN_FORMAT_BPTC_UNORM},
    {ImageFormat_Bc7_UnormSrgb, NVN_FORMAT_BPTC_UNORM_SRGB},
    {ImageFormat_Astc_4x4_Unorm, NVN_FORMAT_RGBA_ASTC_4x4},
    {ImageFormat_Astc_4x4_UnormSrgb, NVN_FORMAT_RGBA_ASTC_4x4_SRGB},
    {ImageFormat_Astc_5x4_Unorm, NVN_FORMAT_RGBA_ASTC_5x4},
    {ImageFormat_Astc_5x4_UnormSrgb, NVN_FORMAT_RGBA_ASTC_5x4_SRGB},
    {ImageFormat_Astc_5x5_Unorm, NVN_FORMAT_RGBA_ASTC_5x5},
    {ImageFormat_Astc_5x5_UnormSrgb, NVN_FORMAT_RGBA_ASTC_5x5_SRGB},
    {ImageFormat_Astc_6x5_Unorm, NVN_FORMAT_RGBA_ASTC_6x5},
    {ImageFormat_Astc_6x5_UnormSrgb, NVN_FORMAT_RGBA_ASTC_6x5_SRGB},
    {ImageFormat_Astc_6x6_Unorm, NVN_FORMAT_RGBA_ASTC_6x6},
    {ImageFormat_Astc_6x6_UnormSrgb, NVN_FORMAT_RGBA_ASTC_6x6_SRGB},
    {ImageFormat_Astc_8x5_Unorm, NVN_FORMAT_RGBA_ASTC_8x5},
    {ImageFormat_Astc_8x5_UnormSrgb, NVN_FORMAT_RGBA_ASTC_8x5_SRGB},
    {ImageFormat_Astc_8x6_Unorm, NVN_FORMAT_RGBA_ASTC_8x6},
    {ImageFormat_Astc_8x6_UnormSrgb, NVN_FORMAT_RGBA_ASTC_8x6_SRGB},
    {ImageFormat_Astc_8x8_Unorm, NVN_FORMAT_RGBA_ASTC_8x8},
    {ImageFormat_Astc_8x8_UnormSrgb, NVN_FORMAT_RGBA_ASTC_8x8_SRGB},
    {ImageFormat_Astc_10x5_Unorm, NVN_FORMAT_RGBA_ASTC_10x5},
    {ImageFormat_Astc_10x5_UnormSrgb, NVN_FORMAT_RGBA_ASTC_10x5_SRGB},
    {ImageFormat_Astc_10x6_Unorm, NVN_FORMAT_RGBA_ASTC_10x6},
    {ImageFormat_Astc_10x6_UnormSrgb, NVN_FORMAT_RGBA_ASTC_10x6_SRGB},
    {ImageFormat_Astc_10x8_Unorm, NVN_FORMAT_RGBA_ASTC_10x8},
    {ImageFormat_Astc_10x8_UnormSrgb, NVN_FORMAT_RGBA_ASTC_10x8_SRGB},
    {ImageFormat_Astc_10x10_Unorm, NVN_FORMAT_RGBA_ASTC_10x10},
    {ImageFormat_Astc_10x10_UnormSrgb, NVN_FORMAT_RGBA_ASTC_10x10_SRGB},
    {ImageFormat_Astc_12x10_Unorm, NVN_FORMAT_RGBA_ASTC_12x10},
    {ImageFormat_Astc_12x10_UnormSrgb, NVN_FORMAT_RGBA_ASTC_12x10_SRGB},
    {ImageFormat_Astc_12x12_Unorm, NVN_FORMAT_RGBA_ASTC_12x12},
    {ImageFormat_Astc_12x12_UnormSrgb, NVN_FORMAT_RGBA_ASTC_12x12_SRGB},
    {ImageFormat_B5_G5_R5_A1_Unorm, NVN_FORMAT_BGR5A1},
};

struct AttributeFormatAndNvnFormat {
    AttributeFormat attributeFormat;
    NVNformat nvnFormat;
};

AttributeFormatAndNvnFormat s_NvnAttributeFormatList[] = {
    {AttributeFormat_4_4_Unorm, NVN_FORMAT_NONE},
    {AttributeFormat_8_Unorm, NVN_FORMAT_R8},
    {AttributeFormat_8_Snorm, NVN_FORMAT_R8SN},
    {AttributeFormat_8_Uint, NVN_FORMAT_R8UI},
    {AttributeFormat_8_Sint, NVN_FORMAT_R8I},
    {AttributeFormat_8_UintToFloat, NVN_FORMAT_R8_UI2F},
    {AttributeFormat_8_SintToFloat, NVN_FORMAT_R8_I2F},
    {AttributeFormat_8_8_Unorm, NVN_FORMAT_RG8},
    {AttributeFormat_8_8_Snorm, NVN_FORMAT_RG8SN},
    {AttributeFormat_8_8_Uint, NVN_FORMAT_RG8UI},
    {AttributeFormat_8_8_Sint, NVN_FORMAT_RG8I},
    {AttributeFormat_8_8_UintToFloat, NVN_FORMAT_RG8_UI2F},
    {AttributeFormat_8_8_SintToFloat, NVN_FORMAT_RG8_I2F},
    {AttributeFormat_16_Unorm, NVN_FORMAT_R16},
    {AttributeFormat_16_Snorm, NVN_FORMAT_R16SN},
    {AttributeFormat_16_Uint, NVN_FORMAT_R16UI},
    {AttributeFormat_16_Sint, NVN_FORMAT_R16I},
    {AttributeFormat_16_Float, NVN_FORMAT_R16F},
    {AttributeFormat_16_UintToFloat, NVN_FORMAT_R16_UI2F},
    {AttributeFormat_16_SintToFloat, NVN_FORMAT_R16_I2F},
    {AttributeFormat_8_8_8_8_Unorm, NVN_FORMAT_RGBA8},
    {AttributeFormat_8_8_8_8_Snorm, NVN_FORMAT_RGBA8SN},
    {AttributeFormat_8_8_8_8_Uint, NVN_FORMAT_RGBA8UI},
    {AttributeFormat_8_8_8_8_Sint, NVN_FORMAT_RGBA8I},
    {AttributeFormat_8_8_8_8_UintToFloat, NVN_FORMAT_RGBA8_UI2F},
    {AttributeFormat_8_8_8_8_SintToFloat, NVN_FORMAT_RGBA8_I2F},
    {AttributeFormat_10_10_10_2_Unorm, NVN_FORMAT_RGB10A2},
    {AttributeFormat_10_10_10_2_Snorm, NVN_FORMAT_RGB10A2SN},
    {AttributeFormat_10_10_10_2_Uint, NVN_FORMAT_RGB10A2UI},
    {AttributeFormat_10_10_10_2_Sint, NVN_FORMAT_RGB10A2I},
    {AttributeFormat_16_16_Unorm, NVN_FORMAT_RG16},
    {AttributeFormat_16_16_Snorm, NVN_FORMAT_RG16SN},
    {AttributeFormat_16_16_Uint, NVN_FORMAT_RG16UI},
    {AttributeFormat_16_16_Sint, NVN_FORMAT_RG16I},
    {AttributeFormat_16_16_Float, NVN_FORMAT_RG16F},
    {AttributeFormat_16_16_UintToFloat, NVN_FORMAT_RG16_UI2F},
    {AttributeFormat_16_16_SintToFloat, NVN_FORMAT_RG16_I2F},
    {AttributeFormat_32_Uint, NVN_FORMAT_R32UI},
    {AttributeFormat_32_Sint, NVN_FORMAT_R32I},
    {AttributeFormat_32_Float, NVN_FORMAT_R32F},
    {AttributeFormat_16_16_16_16_Unorm, NVN_FORMAT_RGBA16},
    {AttributeFormat_16_16_16_16_Snorm, NVN_FORMAT_RGBA16SN},
    {AttributeFormat_16_16_16_16_Uint, NVN_FORMAT_RGBA16UI},
    {AttributeFormat_16_16_16_16_Sint, NVN_FORMAT_RGBA16I},
    {AttributeFormat_16_16_16_16_Float, NVN_FORMAT_RGBA16F},
    {AttributeFormat_16_16_16_16_UintToFloat, NVN_FORMAT_RGBA16_UI2F},
    {AttributeFormat_16_16_16_16_SintToFloat, NVN_FORMAT_RGBA16_I2F},
    {AttributeFormat_32_32_Uint, NVN_FORMAT_RG32UI},
    {AttributeFormat_32_32_Sint, NVN_FORMAT_RG32I},
    {AttributeFormat_32_32_Float, NVN_FORMAT_RG32F},
    {AttributeFormat_32_32_32_Uint, NVN_FORMAT_RGB32UI},
    {AttributeFormat_32_32_32_Sint, NVN_FORMAT_RGB32I},
    {AttributeFormat_32_32_32_Float, NVN_FORMAT_RGB32F},
    {AttributeFormat_32_32_32_32_Uint, NVN_FORMAT_RGBA32UI},
    {AttributeFormat_32_32_32_32_Sint, NVN_FORMAT_RGBA32I},
    {AttributeFormat_32_32_32_32_Float, NVN_FORMAT_RGBA32F},
};

struct ImageFormatAndProperty {
    ImageFormat format;
    ImageFormatProperty property;
};

ImageFormatAndProperty g_ImageFormatAndPropetyTable[] = {
    {ImageFormat_Undefined, {0}},
    {ImageFormat_R8_Unorm, {3}},
    {ImageFormat_R8_Snorm, {3}},
    {ImageFormat_R8_Uint, {3}},
    {ImageFormat_R8_Sint, {3}},
    {ImageFormat_R16_Float, {3}},
    {ImageFormat_R16_Unorm, {3}},
    {ImageFormat_R16_Snorm, {3}},
    {ImageFormat_R16_Uint, {3}},
    {ImageFormat_R16_Sint, {3}},
    {ImageFormat_R32_Float, {3}},
    {ImageFormat_R32_Uint, {3}},
    {ImageFormat_R32_Sint, {3}},
    {ImageFormat_R8_G8_Unorm, {3}},
    {ImageFormat_R8_G8_Snorm, {3}},
    {ImageFormat_R8_G8_Uint, {3}},
    {ImageFormat_R8_G8_Sint, {3}},
    {ImageFormat_R16_G16_Float, {3}},
    {ImageFormat_R16_G16_Unorm, {3}},
    {ImageFormat_R16_G16_Snorm, {3}},
    {ImageFormat_R16_G16_Uint, {3}},
    {ImageFormat_R16_G16_Sint, {3}},
    {ImageFormat_R32_G32_Float, {3}},
    {ImageFormat_R32_G32_Uint, {3}},
    {ImageFormat_R32_G32_Sint, {3}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_R32_G32_B32_Float, {1}},
    {ImageFormat_R32_G32_B32_Uint, {1}},
    {ImageFormat_R32_G32_B32_Sint, {1}},
    {ImageFormat_R8_G8_B8_A8_Unorm, {3}},
    {ImageFormat_R8_G8_B8_A8_Snorm, {3}},
    {ImageFormat_R8_G8_B8_A8_Uint, {3}},
    {ImageFormat_R8_G8_B8_A8_Sint, {3}},
    {ImageFormat_R16_G16_B16_A16_Float, {3}},
    {ImageFormat_R16_G16_B16_A16_Unorm, {3}},
    {ImageFormat_R16_G16_B16_A16_Snorm, {3}},
    {ImageFormat_R16_G16_B16_A16_Uint, {3}},
    {ImageFormat_R16_G16_B16_A16_Sint, {3}},
    {ImageFormat_R32_G32_B32_A32_Float, {3}},
    {ImageFormat_R32_G32_B32_A32_Uint, {3}},
    {ImageFormat_R32_G32_B32_A32_Sint, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_D16_Unorm, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_D32_Float, {3}},
    {ImageFormat_D24_Unorm_S8_Uint, {3}},
    {ImageFormat_D32_Float_S8_Uint_X24, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_R8_G8_B8_A8_UnormSrgb, {3}},
    {ImageFormat_R4_G4_B4_A4_Unorm, {1}},
    {ImageFormat_Undefined, {1}},
    {ImageFormat_R5_G5_B5_A1_Unorm, {1}},
    {ImageFormat_R5_G6_B5_Unorm, {1}},
    {ImageFormat_R10_G10_B10_A2_Unorm, {3}},
    {ImageFormat_R10_G10_B10_A2_Uint, {3}},
    {ImageFormat_R11_G11_B10_Float, {3}},
    {ImageFormat_R9_G9_B9_E5_SharedExp, {1}},
    {ImageFormat_Undefined, {1}},
    {ImageFormat_Bc1_Unorm, {1}},
    {ImageFormat_Bc2_Unorm, {1}},
    {ImageFormat_Bc3_Unorm, {1}},
    {ImageFormat_Undefined, {1}},
    {ImageFormat_Bc1_UnormSrgb, {1}},
    {ImageFormat_Bc2_UnormSrgb, {1}},
    {ImageFormat_Bc3_UnormSrgb, {1}},
    {ImageFormat_Bc4_Unorm, {1}},
    {ImageFormat_Bc4_Snorm, {1}},
    {ImageFormat_Bc5_Unorm, {1}},
    {ImageFormat_Bc5_Snorm, {1}},
    {ImageFormat_Bc7_Unorm, {1}},
    {ImageFormat_Bc7_UnormSrgb, {1}},
    {ImageFormat_Bc6_Float, {1}},
    {ImageFormat_Bc6_Ufloat, {1}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {0}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_Astc_4x4_Unorm, {1}},
    {ImageFormat_Astc_5x4_Unorm, {1}},
    {ImageFormat_Astc_5x5_Unorm, {1}},
    {ImageFormat_Astc_6x5_Unorm, {1}},
    {ImageFormat_Astc_6x6_Unorm, {1}},
    {ImageFormat_Astc_8x5_Unorm, {1}},
    {ImageFormat_Astc_8x6_Unorm, {1}},
    {ImageFormat_Astc_8x8_Unorm, {1}},
    {ImageFormat_Astc_10x5_Unorm, {1}},
    {ImageFormat_Astc_10x6_Unorm, {1}},
    {ImageFormat_Astc_10x8_Unorm, {1}},
    {ImageFormat_Astc_10x10_Unorm, {1}},
    {ImageFormat_Astc_12x10_Unorm, {1}},
    {ImageFormat_Astc_12x12_Unorm, {1}},
    {ImageFormat_Astc_4x4_UnormSrgb, {1}},
    {ImageFormat_Astc_5x4_UnormSrgb, {1}},
    {ImageFormat_Astc_5x5_UnormSrgb, {1}},
    {ImageFormat_Astc_6x5_UnormSrgb, {1}},
    {ImageFormat_Astc_6x6_UnormSrgb, {1}},
    {ImageFormat_Astc_8x5_UnormSrgb, {1}},
    {ImageFormat_Astc_8x6_UnormSrgb, {1}},
    {ImageFormat_Astc_8x8_UnormSrgb, {1}},
    {ImageFormat_Astc_10x5_UnormSrgb, {1}},
    {ImageFormat_Astc_10x6_UnormSrgb, {1}},
    {ImageFormat_Astc_10x8_UnormSrgb, {1}},
    {ImageFormat_Astc_10x10_UnormSrgb, {1}},
    {ImageFormat_Astc_12x10_UnormSrgb, {1}},
    {ImageFormat_Astc_12x12_UnormSrgb, {1}},
    {ImageFormat_B5_G6_R5_Unorm, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_B5_G5_R5_A1_Unorm, {3}},
    {ImageFormat_A1_B5_G5_R5_Unorm, {1}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_B8_G8_R8_A8_Unorm, {3}},
    {ImageFormat_Undefined, {3}},
    {ImageFormat_B8_G8_R8_A8_UnormSrgb, {3}},
};

}  // namespace

NVNformat Nvn::GetImageFormat(ImageFormat format) {
    struct Comp {
        bool operator()(const ImageFormatAndNvnFormat& format1, ImageFormat format2) {
            return format1.imageFormat < format2;
        }
    };

    ImageFormatAndNvnFormat* pEnd = std::end(s_NvnTextureFormatList);
    ImageFormatAndNvnFormat* pFound =
        std::lower_bound(s_NvnTextureFormatList, pEnd, format, Comp());
    if (pFound != pEnd && format >= pFound->imageFormat) {
        return pFound->nvnFormat;
    }

    return NVN_FORMAT_NONE;
}

NVNformat Nvn::GetAttributeFormat(AttributeFormat format) {
    struct Comp {
        bool operator()(const AttributeFormatAndNvnFormat& format1, AttributeFormat format2) {
            return format1.attributeFormat < format2;
        }
    };

    AttributeFormatAndNvnFormat* pEnd = std::end(s_NvnAttributeFormatList);
    AttributeFormatAndNvnFormat* pFound =
        std::lower_bound(s_NvnAttributeFormatList, pEnd, format, Comp());
    if (pFound != pEnd && format >= pFound->attributeFormat) {
        return pFound->nvnFormat;
    }

    return NVN_FORMAT_NONE;
}

NVNtextureTarget Nvn::GetImageTarget(ImageDimension dimension) {
    const NVNtextureTarget s_TargetTable[] = {
        NVN_TEXTURE_TARGET_1D,
        NVN_TEXTURE_TARGET_2D,
        NVN_TEXTURE_TARGET_3D,
        NVN_TEXTURE_TARGET_CUBEMAP,
        NVN_TEXTURE_TARGET_1D_ARRAY,
        NVN_TEXTURE_TARGET_2D_ARRAY,
        NVN_TEXTURE_TARGET_2D_MULTISAMPLE,
        NVN_TEXTURE_TARGET_2D_MULTISAMPLE_ARRAY,
        NVN_TEXTURE_TARGET_CUBEMAP_ARRAY,
        NVN_TEXTURE_TARGET_RECTANGLE,
    };

    return s_TargetTable[dimension];
}

NVNdepthFunc Nvn::GetDepthFunction(ComparisonFunction compare) {
    const NVNdepthFunc s_DepthFunction[] = {
        NVN_DEPTH_FUNC_NEVER,  NVN_DEPTH_FUNC_LESS,    NVN_DEPTH_FUNC_EQUAL,
        NVN_DEPTH_FUNC_LEQUAL, NVN_DEPTH_FUNC_GREATER, NVN_DEPTH_FUNC_NOTEQUAL,
        NVN_DEPTH_FUNC_GEQUAL, NVN_DEPTH_FUNC_ALWAYS,
    };

    return s_DepthFunction[compare];
}

NVNstencilOp Nvn::GetStencilOperation(StencilOperation operation) {
    const NVNstencilOp s_StencilOperation[] = {
        NVN_STENCIL_OP_KEEP,      NVN_STENCIL_OP_ZERO,      NVN_STENCIL_OP_REPLACE,
        NVN_STENCIL_OP_INCR,      NVN_STENCIL_OP_DECR,      NVN_STENCIL_OP_INVERT,
        NVN_STENCIL_OP_INCR_WRAP, NVN_STENCIL_OP_DECR_WRAP,
    };

    return s_StencilOperation[operation];
}

NVNstencilFunc Nvn::GetStencilFunction(ComparisonFunction compare) {
    const NVNstencilFunc s_StencilFunction[] = {
        NVN_STENCIL_FUNC_NEVER,  NVN_STENCIL_FUNC_LESS,    NVN_STENCIL_FUNC_EQUAL,
        NVN_STENCIL_FUNC_LEQUAL, NVN_STENCIL_FUNC_GREATER, NVN_STENCIL_FUNC_NOTEQUAL,
        NVN_STENCIL_FUNC_GEQUAL, NVN_STENCIL_FUNC_ALWAYS,
    };

    return s_StencilFunction[compare];
}

NVNblendEquation Nvn::GetBlendEquation(BlendFunction a) {
    const NVNblendEquation eqs[] = {
        NVN_BLEND_EQUATION_ADD, NVN_BLEND_EQUATION_SUB, NVN_BLEND_EQUATION_REVERSE_SUB,
        NVN_BLEND_EQUATION_MIN, NVN_BLEND_EQUATION_MAX,
    };

    return eqs[a];
}

NVNblendFunc Nvn::GetBlendFunction(BlendFactor a) {
    const NVNblendFunc funcs[] = {
        NVN_BLEND_FUNC_ZERO,
        NVN_BLEND_FUNC_ONE,
        NVN_BLEND_FUNC_SRC_COLOR,
        NVN_BLEND_FUNC_ONE_MINUS_SRC_COLOR,
        NVN_BLEND_FUNC_DST_COLOR,
        NVN_BLEND_FUNC_ONE_MINUS_DST_COLOR,
        NVN_BLEND_FUNC_SRC_ALPHA,
        NVN_BLEND_FUNC_ONE_MINUS_SRC_ALPHA,
        NVN_BLEND_FUNC_DST_ALPHA,
        NVN_BLEND_FUNC_ONE_MINUS_DST_ALPHA,
        NVN_BLEND_FUNC_CONSTANT_COLOR,
        NVN_BLEND_FUNC_ONE_MINUS_CONSTANT_COLOR,
        NVN_BLEND_FUNC_CONSTANT_ALPHA,
        NVN_BLEND_FUNC_ONE_MINUS_CONSTANT_ALPHA,
        NVN_BLEND_FUNC_SRC_ALPHA_SATURATE,
        NVN_BLEND_FUNC_SRC1_COLOR,
        NVN_BLEND_FUNC_ONE_MINUS_SRC1_COLOR,
        NVN_BLEND_FUNC_SRC1_ALPHA,
        NVN_BLEND_FUNC_ONE_MINUS_SRC1_ALPHA,
    };

    return funcs[a];
}

NVNlogicOp Nvn::GetLogicOperation(LogicOperation a) {
    const NVNlogicOp ops[] = {
        NVN_LOGIC_OP_CLEAR,         NVN_LOGIC_OP_AND,          NVN_LOGIC_OP_AND_REVERSE,
        NVN_LOGIC_OP_COPY,          NVN_LOGIC_OP_AND_INVERTED, NVN_LOGIC_OP_NOOP,
        NVN_LOGIC_OP_XOR,           NVN_LOGIC_OP_OR,           NVN_LOGIC_OP_NOR,
        NVN_LOGIC_OP_EQUIV,         NVN_LOGIC_OP_INVERT,       NVN_LOGIC_OP_OR_REVERSE,
        NVN_LOGIC_OP_COPY_INVERTED, NVN_LOGIC_OP_OR_INVERTED,  NVN_LOGIC_OP_NAND,
        NVN_LOGIC_OP_SET,
    };

    return ops[a];
}

NVNfrontFace Nvn::GetFrontFace(FrontFace a) {
    const NVNfrontFace faces[] = {
        NVN_FRONT_FACE_CCW,
        NVN_FRONT_FACE_CW,
    };

    return faces[a];
}

NVNpolygonMode Nvn::GetFillMode(FillMode a) {
    const NVNpolygonMode faces[] = {
        NVN_POLYGON_MODE_POINT,
        NVN_POLYGON_MODE_LINE,
        NVN_POLYGON_MODE_FILL,
    };

    return faces[a];
}

NVNdrawPrimitive Nvn::GetDrawPrimitive(PrimitiveTopology a) {
    const NVNdrawPrimitive prims[] = {
        NVN_DRAW_PRIMITIVE_POINTS,
        NVN_DRAW_PRIMITIVE_LINES,
        NVN_DRAW_PRIMITIVE_LINE_STRIP,
        NVN_DRAW_PRIMITIVE_TRIANGLES,
        NVN_DRAW_PRIMITIVE_TRIANGLE_STRIP,
        NVN_DRAW_PRIMITIVE_LINES_ADJACENCY,
        NVN_DRAW_PRIMITIVE_LINE_STRIP_ADJACENCY,
        NVN_DRAW_PRIMITIVE_TRIANGLES_ADJACENCY,
        NVN_DRAW_PRIMITIVE_TRIANGLE_STRIP_ADJACENCY,
        NVN_DRAW_PRIMITIVE_PATCHES,
    };

    return prims[a];
}

NVNminFilter Nvn::GetMinFilter(FilterMode filterMode) {
    switch ((filterMode & FilterModeBit_MinFilterMask) >> FilterModeBit_MinFilterShift) {
    case FilterModeBit_Point:
        switch ((filterMode & FilterModeBit_MipFilterMask) >> FilterModeBit_MipFilterShift) {
        case FilterModeBit_Point:
            return NVN_MIN_FILTER_NEAREST_MIPMAP_NEAREST;

        case FilterModeBit_Linear:
            return NVN_MIN_FILTER_NEAREST_MIPMAP_LINEAR;

        default:
            return NVN_MIN_FILTER_NEAREST;
        }
        break;

    case FilterModeBit_Linear:
        switch ((filterMode & FilterModeBit_MipFilterMask) >> FilterModeBit_MipFilterShift) {
        case FilterModeBit_Point:
            return NVN_MIN_FILTER_LINEAR_MIPMAP_NEAREST;

        case FilterModeBit_Linear:
            return NVN_MIN_FILTER_LINEAR_MIPMAP_LINEAR;

        default:
            return NVN_MIN_FILTER_LINEAR;
        }
        break;

    default:
        NN_UNEXPECTED_DEFAULT;
        break;
    }
}

NVNmagFilter Nvn::GetMagFilter(nn::gfx::FilterMode filterMode) {
    switch ((filterMode & FilterModeBit_MagFilterMask) >> FilterModeBit_MagFilterShift) {
    case FilterModeBit_Point:
        return NVN_MAG_FILTER_NEAREST;

    case FilterModeBit_Linear:
        return NVN_MAG_FILTER_LINEAR;

    default:
        NN_UNEXPECTED_DEFAULT;
        break;
    }
}

NVNwrapMode Nvn::GetWrapMode(TextureAddressMode wrapMode) {
    const NVNwrapMode s_WrapMode[] = {
        NVN_WRAP_MODE_REPEAT,
        NVN_WRAP_MODE_MIRRORED_REPEAT,
        NVN_WRAP_MODE_CLAMP_TO_EDGE,
        NVN_WRAP_MODE_CLAMP_TO_BORDER,
        NVN_WRAP_MODE_MIRROR_CLAMP_TO_EDGE,
    };

    return s_WrapMode[wrapMode];
}

NVNshaderStage Nvn::GetShaderStage(ShaderStage stage) {
    const NVNshaderStage s_Stage[] = {
        NVN_SHADER_STAGE_VERTEX,   NVN_SHADER_STAGE_TESS_CONTROL, NVN_SHADER_STAGE_TESS_EVALUATION,
        NVN_SHADER_STAGE_GEOMETRY, NVN_SHADER_STAGE_FRAGMENT,     NVN_SHADER_STAGE_COMPUTE,
    };

    return s_Stage[stage];
}

int Nvn::GetShaderStageBits(int shaderStageBits) {
    const NVNshaderStageBits s_ShaderStageBitTable[] = {
        NVN_SHADER_STAGE_VERTEX_BIT,          NVN_SHADER_STAGE_TESS_CONTROL_BIT,
        NVN_SHADER_STAGE_TESS_EVALUATION_BIT, NVN_SHADER_STAGE_GEOMETRY_BIT,
        NVN_SHADER_STAGE_FRAGMENT_BIT,        NVN_SHADER_STAGE_COMPUTE_BIT,
    };

    int ret = 0;
    for (int idxStage = 0, mask = 1; idxStage < ShaderStage_End; ++idxStage, mask <<= 1) {
        if (shaderStageBits & mask) {
            ret |= s_ShaderStageBitTable[idxStage];
        }
    }
    return ret;
}

NVNcompareFunc Nvn::GetRComparisonFunction(ComparisonFunction compare) {
    const NVNcompareFunc s_ComparisonFunction[] = {
        NVN_COMPARE_FUNC_NEVER,  NVN_COMPARE_FUNC_LESS,    NVN_COMPARE_FUNC_EQUAL,
        NVN_COMPARE_FUNC_LEQUAL, NVN_COMPARE_FUNC_GREATER, NVN_COMPARE_FUNC_NOTEQUAL,
        NVN_COMPARE_FUNC_GEQUAL, NVN_COMPARE_FUNC_ALWAYS,
    };

    return s_ComparisonFunction[compare];
}

NVNindexType Nvn::GetIndexFormat(IndexFormat a) {
    const NVNindexType formats[] = {
        NVN_INDEX_TYPE_UNSIGNED_BYTE,
        NVN_INDEX_TYPE_UNSIGNED_SHORT,
        NVN_INDEX_TYPE_UNSIGNED_INT,
    };

    return formats[a];
}

NVNface Nvn::GetCullMode(CullMode a) {
    const NVNface culls[] = {
        NVN_FACE_NONE,
        NVN_FACE_FRONT,
        NVN_FACE_BACK,
    };

    return culls[a];
}

int Nvn::GetMemoryPoolFlags(int memoryPoolProperty) {
    return memoryPoolProperty;
}

NVNbufferAddress Nvn::GetBufferAddress(GpuAddress addr) {
    return addr.ToData()->value;
}

void Nvn::SetupScanBufferTextureInfo(TextureInfo* pOutInfo, const SwapChainInfo& info) {
    pOutInfo->SetImageStorageDimension(ImageStorageDimension_2d);
    pOutInfo->SetTileMode(TileMode_Optimal);
    pOutInfo->SetSwizzle(0);
    pOutInfo->SetMipCount(1);
    pOutInfo->SetMultiSampleCount(1);
    pOutInfo->SetImageFormat(info.GetFormat());
    pOutInfo->SetGpuAccessFlags(GpuAccess_ScanBuffer | GpuAccess_ColorBuffer);
    pOutInfo->SetWidth(info.GetWidth());
    pOutInfo->SetHeight(info.GetHeight());
    pOutInfo->SetDepth(1);
    pOutInfo->SetArrayLength(1);
}

NVNcounterType Nvn::GetCounterType(QueryTarget target) {
    const NVNcounterType s_CounterTypeTable[] = {
        NVN_COUNTER_TYPE_TIMESTAMP,
        NVN_COUNTER_TYPE_SAMPLES_PASSED,
        NVN_COUNTER_TYPE_INPUT_VERTICES,
        NVN_COUNTER_TYPE_INPUT_PRIMITIVES,
        NVN_COUNTER_TYPE_VERTEX_SHADER_INVOCATIONS,
        NVN_COUNTER_TYPE_GEOMETRY_SHADER_INVOCATIONS,
        NVN_COUNTER_TYPE_GEOMETRY_SHADER_PRIMITIVES,
        NVN_COUNTER_TYPE_CLIPPER_INPUT_PRIMITIVES,
        NVN_COUNTER_TYPE_CLIPPER_OUTPUT_PRIMITIVES,
        NVN_COUNTER_TYPE_FRAGMENT_SHADER_INVOCATIONS,
        NVN_COUNTER_TYPE_TESS_CONTROL_SHADER_INVOCATIONS,
        NVN_COUNTER_TYPE_TESS_EVALUATION_SHADER_INVOCATIONS,
        static_cast<NVNcounterType>(-1),  //???
    };

    return s_CounterTypeTable[target];
}

nn::util::BitPack32 Nvn::GetDeviceFeature(const NVNdevice* device) {
    nn::util::BitPack32 feature;
    feature.Clear();

    int supported;

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_MIN_MAX_FILTERING, &supported);
    feature.SetBit(NvnDeviceFeature_SupportMinMaxFiltering, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_STENCIL8_FORMAT, &supported);
    feature.SetBit(NvnDeviceFeature_SupportStencil8Format, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_ASTC_FORMATS, &supported);
    feature.SetBit(NvnDeviceFeature_SupportAstcFormat, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_CONSERVATIVE_RASTER, &supported);
    feature.SetBit(NvnDeviceFeature_SupportConservativeRaster, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_ZERO_FROM_UNMAPPED_VIRTUAL_POOL_PAGES,
                        &supported);
    feature.SetBit(NvnDeviceFeature_SupportZeroFromUnmappedVirtualPoolPage, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_PASSTHROUGH_GEOMETRY_SHADERS, &supported);
    feature.SetBit(NvnDeviceFeature_SupportPassthroughGeometryShader, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_VIEWPORT_SWIZZLE, &supported);
    feature.SetBit(NvnDeviceFeature_SupportViewportSwizzle, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_SPARSE_TILED_PACKAGED_TEXTURES,
                        &supported);
    feature.SetBit(NvnDeviceFeature_SupportSparseTiledPackagedTexture, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_ADVANCED_BLEND_MODES, &supported);
    feature.SetBit(NvnDeviceFeature_AdvancedBlendModes, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_DRAW_TEXTURE, &supported);
    feature.SetBit(NvnDeviceFeature_DrawTexture, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_TARGET_INDEPENDENT_RASTERIZATION,
                        &supported);
    feature.SetBit(NvnDeviceFeature_TargetIndependentRasterization, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_FRAGMENT_COVERAGE_TO_COLOR, &supported);
    feature.SetBit(NvnDeviceFeature_FragmentCoverageToColor, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_POST_DEPTH_COVERAGE, &supported);
    feature.SetBit(NvnDeviceFeature_PostDepthCoverage, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_IMAGES_USING_TEXTURE_HANDLES, &supported);
    feature.SetBit(NvnDeviceFeature_ImagesUsingTextureHandles, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_SAMPLE_LOCATIONS, &supported);
    feature.SetBit(NvnDeviceFeature_SampleLocations, supported);

    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_FRAGMENT_SHADER_INTERLOCK, &supported);
    feature.SetBit(NvnDeviceFeature_SupportFragmentShaderInterlock, supported);

#if NN_SDK_VER > NN_MAKE_VER(3, 5, 1)
    nvnDeviceGetInteger(device, NVN_DEVICE_INFO_SUPPORTS_DEBUG_LAYER, &supported);
    feature.SetBit(NvnDeviceFeature_SupportsDebugLayer, supported);
#endif

    return feature;
}

void Nvn::GetImageFormatProperty(ImageFormatProperty* pOutImageFormatProperty,
                                 NVNformat nvnFormat) {
    *pOutImageFormatProperty = g_ImageFormatAndPropetyTable[nvnFormat].property;
}

ImageFormat Nvn::GetGfxImageFormat(NVNformat nvnFormat) {
    return g_ImageFormatAndPropetyTable[nvnFormat].format;
}

void Nvn::DebugCallback([[maybe_unused]] NVNdebugCallbackSource source, NVNdebugCallbackType type,
                        [[maybe_unused]] int id, [[maybe_unused]] NVNdebugCallbackSeverity severity,
                        [[maybe_unused]] const char* message, void*) {
    switch (type) {
    case NVN_DEBUG_CALLBACK_TYPE_API_ERROR:
    case NVN_DEBUG_CALLBACK_TYPE_API_WARNING:
        break;

    default:
        NN_UNEXPECTED_DEFAULT;
        break;
    }
}

GlslcDll& GlslcDll::GetInstance() {
    static GlslcDll s_GlslcDll;

    if (!s_GlslcDll.IsInitialized()) {
        s_GlslcDll.Initialize();
    }

    return s_GlslcDll;
}

GlslcDll::GlslcDll() {
    GlslcCompilePreSpecialized = nullptr;
    GlslcCompileSpecialized = nullptr;
    GlslcInitialize = nullptr;
    GlslcFinalize = nullptr;
    GlslcCompile = nullptr;
    GlslcGetVersion = nullptr;
    GlslcSetAllocator = nullptr;
    GlslcGetDefaultOptions = nullptr;
    m_hDll = nullptr;
}

GlslcDll::~GlslcDll() {
    Finalize();
}

}  // namespace nn::gfx::detail