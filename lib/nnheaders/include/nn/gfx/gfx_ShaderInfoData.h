#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/nn_BitTypes.h>
#include <nn/util/util_BitPack.h>

namespace nn::gfx {

struct ShaderInfoData {
    enum { Flag_SeparationEnable, Flag_ResShader };

    nn::util::BitPack8 flags;
    Bit8 codeType;
    Bit8 sourceFormat;
    char reserved2;
    Bit32 binaryFormat;
    detail::Ptr<const void> pVertexShaderCode;
    detail::Ptr<const void> pHullShaderCode;
    detail::Ptr<const void> pDomainShaderCode;
    detail::Ptr<const void> pGeometryShaderCode;
    detail::Ptr<const void> pPixelShaderCode;
    detail::Ptr<const void> pComputeShaderCode;
    char reserved[40];
};

struct ShaderCode {
    uint32_t codeSize;
    uint32_t decompressedCodeSize;
    detail::Ptr<const void> pCode;
    char reserved[16];
};

}  // namespace nn::gfx