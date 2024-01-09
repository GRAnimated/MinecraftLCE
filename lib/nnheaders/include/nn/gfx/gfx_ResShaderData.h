#pragma once

#include <nn/gfx/gfx_ShaderInfo.h>
#include <nn/util.h>
#include <nn/util/util_BinaryFormat.h>

namespace nn {

namespace util {
class ResDic;
}

namespace gfx {

struct ResShaderVariationData;
struct ResShaderReflectionData;
struct ResShaderContainerData;
struct nngfxToolShaderCompilerShaderReflection;
struct ResShaderReflectionStageData2;

struct ResShaderProgramData {
    ShaderInfoData info;
    uint32_t objSize;
    char reserved2[4];
    nn::util::BinTPtr<void> pObj;
    nn::util::BinTPtr<ResShaderVariationData> pParent;
    nn::util::BinTPtr<ResShaderReflectionData> pShaderReflection;
    nn::util::BinTPtr<nngfxToolShaderCompilerShaderReflection> pShaderCompilerReflection;
    char reserved[24];
};

struct ResShaderVariationData {
    nn::util::BinTPtr<ResShaderProgramData> pSourceProgram;
    nn::util::BinTPtr<ResShaderProgramData> pIntermediateLanguageProgram;
    nn::util::BinTPtr<ResShaderProgramData> pBinaryProgram;
    nn::util::BinTPtr<ResShaderContainerData> pParent;
    char reserved[32];
};

struct ResShaderContainerData {
    nn::util::BinaryBlockHeader blockHeader;
    uint16_t targetApiType;
    uint16_t targetApiVersion;
    uint8_t targetCodeType;
    char reserved2[3];
    uint32_t compilerVersion;
    uint32_t shaderVariationCount;
    nn::util::BinTPtr<ResShaderVariationData> pShaderVariationArray;
    nn::util::BinTPtr<void> pShaderBinaryPool;
    uint64_t lowLevelCompilerVersion;
    char reserved[40];
};

struct ResShaderFileData {
    nn::util::BinaryFileHeader fileHeader;
    char reserved[64];
};

struct ResShaderReflectionStageData {
    nn::util::BinTPtr<nn::util::ResDic> pShaderInputDic;
    nn::util::BinTPtr<nn::util::ResDic> pShaderOutputDic;
    nn::util::BinTPtr<nn::util::ResDic> pSamplerDic;
    nn::util::BinTPtr<nn::util::ResDic> pConstantBufferDic;
    nn::util::BinTPtr<nn::util::ResDic> pUnorderedAccessBufferDic;
    int32_t offsetShaderOutput;
    int32_t offsetSampler;
    int32_t offsetConstantBuffer;
    int32_t offsetUnorderedAccessBuffer;
    nn::util::BinTPtr<int> pShaderSlotArray;
    uint32_t computeWorkGroupSizeX;
    uint32_t computeWorkGroupSizeY;
    uint32_t computeWorkGroupSizeZ;
    int32_t offsetImage;
    nn::util::BinTPtr<nn::util::ResDic> pImageDic;
    nn::util::BinTPtr<ResShaderReflectionStageData2> pReflectionStageData2;
};

struct ResShaderReflectionStageData2 {
    nn::util::BinTPtr<nn::util::ResDic> pSeparateTextureDic;
    nn::util::BinTPtr<nn::util::ResDic> pSeparateSamplerDic;
    int32_t offsetSeparateTexture;
    int32_t offsetSeparateSampler;
    char reserved[24];
};

struct ResShaderReflectionData {
    nn::util::BinTPtr<ResShaderReflectionStageData> pVertexReflection;
    nn::util::BinTPtr<ResShaderReflectionStageData> pHullReflection;
    nn::util::BinTPtr<ResShaderReflectionStageData> pDomainReflection;
    nn::util::BinTPtr<ResShaderReflectionStageData> pGeometryReflection;
    nn::util::BinTPtr<ResShaderReflectionStageData> pPixelReflection;
    nn::util::BinTPtr<ResShaderReflectionStageData> pComputeReflection;
    char reserved[16];
};
}  // namespace gfx

}  // namespace nn