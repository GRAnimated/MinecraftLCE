#pragma once

#include <nn/gfx/gfx_MemoryPoolInfoData.h>
#include <nn/util/util_BinTypes.h>

namespace nn::gfx {

struct NvnDecomposedControlSection {
    nn::util::BinTPtr<const void> pMetaData;
    nn::util::BinTPtr<const void> pAssemblyData;
    nn::util::BinTPtr<const void> pSpecializationData;
    nn::util::BinTPtr<const void> pPragmaData;
    nn::util::BinTPtr<const void> pAssemblyLocalsData;
    nn::util::BinTPtr<const void> pUniform64InfoData;
    char reserved[16];
};

struct NvnShaderCode {
    uint64_t dataAddress;
    nn::util::BinTPtr<const void> pControl;
    nn::util::BinTPtr<const void> pData;
    uint32_t dataSize;
    uint32_t controlSize;
    nn::util::BinTPtr<const NvnDecomposedControlSection> pDecomposedControlSection;
    uint32_t scratchMemoryRecommended;
    uint32_t scratchMemoryPerWarp;
    char reserved[16];
};

struct NvnShaderPool {
    MemoryPoolInfoData memoryPoolInfo;
    nn::util::BinTPtr<void> pMemoryPool;
    char reserved2[8];
    nn::util::BinTPtr<void> pCurrentMemoryPool;
    char reserved[24];
};

}  // namespace nn::gfx