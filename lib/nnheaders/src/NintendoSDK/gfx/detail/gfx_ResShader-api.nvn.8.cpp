#include <nn/gfx/detail/gfx_MemoryPool-api.nvn.8.h>
#include <nn/gfx/detail/gfx_ResShaderImpl.h>
#include <nn/gfx/gfx_Device.h>
#include <nn/gfx/gfx_MemoryPoolInfo.h>
#include <nn/gfx/gfx_ResShader.h>
#include <nn/gfx/gfx_ResShaderData-api.nvn.h>

#include "gfx_NvnHelper.h"

namespace nn::gfx {
namespace detail {

template <>
size_t ResShaderProgramImpl::NvnGetRecommendedScrachMemorySize<ApiVariationNvn8>(
    const ResShaderProgram* pThis, DeviceImpl<ApiVariationNvn8>* pDevice) {
    static detail::Ptr<const void> ShaderInfoData::*s_pStageCodes[] = {
        &ShaderInfoData::pVertexShaderCode, &ShaderInfoData::pHullShaderCode,
        &ShaderInfoData::pDomainShaderCode, &ShaderInfoData::pGeometryShaderCode,
        &ShaderInfoData::pPixelShaderCode,  &ShaderInfoData::pComputeShaderCode,
    };

    const ResShaderProgram::value_type& data = pThis->ToData();
    uint32_t maxSizeRecommended = 0;
    uint32_t maxSizePerWarp = 0;

    for (int idxStage = 0; idxStage < ShaderStage_End; ++idxStage) {
        const NvnShaderCode* pNvnShaderData = data.info.*s_pStageCodes[idxStage];
        if (pNvnShaderData) {
            maxSizeRecommended =
                std::max(maxSizeRecommended, pNvnShaderData->scratchMemoryRecommended);
            maxSizePerWarp = std::max(maxSizePerWarp, pNvnShaderData->scratchMemoryPerWarp);
        }
    }

    uint32_t maxSize = 0;

    if (maxSizeRecommended != 0) {
        maxSize = maxSizeRecommended;
    } else if (maxSizePerWarp != 0) {
        int scaleFactor;
        nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                            NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_SCALE_FACTOR_RECOMMENDED,
                            &scaleFactor);
        maxSize = scaleFactor * maxSizePerWarp;
    } else {
        return maxSize;
    }

    int granularity;
    nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                        NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_GRANULARITY, &granularity);
    return (maxSize + granularity - 1) / granularity * granularity;
}

template <>
void ResShaderContainerImpl::Initialize<ApiVariationNvn8>(
    ResShaderContainer* pThis, DeviceImpl<ApiVariationNvn8>* pDevice,
    MemoryPoolImpl<ApiVariationNvn8>* pMemoryPool, ptrdiff_t memoryPoolOffset,
    [[maybe_unused]] size_t memoryPoolSize) {
    ResShaderContainer::value_type& data = pThis->ToData();
    NvnShaderPool* pShaderPool = static_cast<NvnShaderPool*>(data.pShaderBinaryPool.Get());
    MemoryPoolInfo& memoryPoolInfo = DataToAccessor(pShaderPool->memoryPoolInfo);

    NVNbufferAddress headAddress;

    if (pMemoryPool) {
        pShaderPool->pCurrentMemoryPool.Set(pMemoryPool);
        ptrdiff_t offset = memoryPoolOffset +
                           nn::util::BytePtr(pThis).Distance(pShaderPool->memoryPoolInfo.pMemory);
        headAddress = nvnMemoryPoolGetBufferAddress(pMemoryPool->ToData()->pNvnMemoryPool);
        headAddress += offset;
    } else {
        auto pInternalMemoryPool =
            static_cast<MemoryPoolImpl<ApiVariationNvn8>*>(pShaderPool->pMemoryPool.Get());
        pInternalMemoryPool->Initialize(pDevice, memoryPoolInfo);
        pShaderPool->pCurrentMemoryPool.Set(pInternalMemoryPool);
        headAddress = nvnMemoryPoolGetBufferAddress(pInternalMemoryPool->ToData()->pNvnMemoryPool);
    }

    for (int idxVariation = 0, variationCount = pThis->GetShaderVariationCount();
         idxVariation < variationCount; ++idxVariation) {
        ResShaderVariation* pResShaderVariation = pThis->GetResShaderVariation(idxVariation);
        if (ResShaderProgram* pResShaderProgram =
                pResShaderVariation->GetResShaderProgram(ShaderCodeType_Binary)) {
            ShaderInfo* pShaderInfo = pResShaderProgram->GetShaderInfo();
            for (int idxStage = 0; idxStage < 6; ++idxStage) {
                if (auto pNvnShaderCode =
                        const_cast<NvnShaderCode*>(static_cast<const NvnShaderCode*>(
                            pShaderInfo->GetShaderCodePtr(static_cast<ShaderStage>(idxStage))))) {
                    pNvnShaderCode->dataAddress =
                        headAddress + nn::util::BytePtr(memoryPoolInfo.GetPoolMemory())
                                          .Distance(pNvnShaderCode->pData.Get());
                }
            }
        }
    }

    pThis->ToData().targetCodeType = ShaderCodeType_Binary;
}

template <>
void ResShaderContainerImpl::Finalize<ApiVariationNvn8>(ResShaderContainer* pThis,
                                                        DeviceImpl<ApiVariationNvn8>* pDevice) {
    ResShaderContainer::value_type& data = pThis->ToData();
    NvnShaderPool* pShaderPool = static_cast<NvnShaderPool*>(data.pShaderBinaryPool.Get());

    auto pCurrentMemoryPool =
        static_cast<MemoryPoolImpl<ApiVariationNvn8>*>(pShaderPool->pCurrentMemoryPool.Get());

    if (pCurrentMemoryPool == pShaderPool->pMemoryPool.Get()) {
        pCurrentMemoryPool->Finalize(pDevice);
    }
    pShaderPool->pCurrentMemoryPool.Set(nullptr);
}

}  // namespace detail

template <>
size_t NvnGetMaxRecommendedScratchMemorySize<ApiVariationNvn8>(
    TDevice<ApiVariationNvn8>* pDevice, const ResShaderFile* const* ppResShaderFileArray,
    int shaderFileCount) {
    static detail::Ptr<const void> ShaderInfoData::*s_pStageCodes[] = {
        &ShaderInfoData::pVertexShaderCode, &ShaderInfoData::pHullShaderCode,
        &ShaderInfoData::pDomainShaderCode, &ShaderInfoData::pGeometryShaderCode,
        &ShaderInfoData::pPixelShaderCode,  &ShaderInfoData::pComputeShaderCode,
    };

    uint32_t maxSizeRecommended = 0;
    uint32_t maxSizePerWarp = 0;

    for (int idxResShaderFile = 0; idxResShaderFile < shaderFileCount; ++idxResShaderFile) {
        if (const ResShaderContainer* pResShaderContainer =
                ppResShaderFileArray[idxResShaderFile]->GetShaderContainer()) {
            for (int idxVariation = 0,
                     variationCount = pResShaderContainer->GetShaderVariationCount();
                 idxVariation < variationCount; ++idxVariation) {
                const ResShaderVariation* pResShaderVariation =
                    pResShaderContainer->GetResShaderVariation(idxVariation);
                if (const ResShaderProgram* pResShaderProgram =
                        pResShaderVariation->GetResShaderProgram(ShaderCodeType_Binary)) {
                    for (int idxStage = 0; idxStage < 6; ++idxStage) {
                        if (auto pNvnShaderData = static_cast<const NvnShaderCode*>(
                                pResShaderProgram->ToData().info.*s_pStageCodes[idxStage])) {
                            maxSizeRecommended = std::max(maxSizeRecommended,
                                                          pNvnShaderData->scratchMemoryRecommended);
                            maxSizePerWarp =
                                std::max(maxSizePerWarp, pNvnShaderData->scratchMemoryPerWarp);
                        }
                    }
                }
            }
        }
    }

    uint32_t maxSize = 0;

    if (maxSizeRecommended != 0) {
        maxSize = maxSizeRecommended;
    } else if (maxSizePerWarp != 0) {
        int scaleFactor;
        nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                            NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_SCALE_FACTOR_RECOMMENDED,
                            &scaleFactor);
        maxSize = scaleFactor * maxSizePerWarp;
    } else {
        return maxSize;
    }

    int granularity;
    nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                        NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_GRANULARITY, &granularity);
    return (maxSize + granularity - 1) / granularity * granularity;
}
}  // namespace nn::gfx