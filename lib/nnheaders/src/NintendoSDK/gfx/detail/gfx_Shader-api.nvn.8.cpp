#include <nn/gfx/detail/gfx_Shader-api.nvn.8.h>

#include <nn/gfx/detail/gfx_Device-api.nvn.8.h>
#include <nn/gfx/gfx_ResShaderData-api.nvn.h>
#include <nn/gfx/gfx_ResShaderData.h>
#include <nn/gfx/gfx_ShaderInfo.h>
#include <nn/os/os_Mutex.h>
#include <nn/util/util_BitUtil.h>
#include <nn/util/util_BytePtr.h>
#include <nn/util/util_ResDic.h>
#include <nvnTool/nvnTool_GlslcInterface.h>

#include <cstdlib>
#include <cstring>

#include "gfx_NvnHelper.h"

namespace nn::gfx::detail {

namespace {

template <typename TInterface>
int GetShaderSlot(const TInterface& piq, NVNshaderStage stage) {
    return piq.bindings[stage];
}

template <>
int GetShaderSlot<GLSLCProgramInputInfo>(const GLSLCProgramInputInfo& piq,
                                         [[maybe_unused]] NVNshaderStage stage) {
    return piq.location;
}

template <>
int GetShaderSlot<GLSLCProgramOutputInfo>(const GLSLCProgramOutputInfo& piq,
                                          [[maybe_unused]] NVNshaderStage stage) {
    return piq.location;
}

// figure out what this is called
template <typename TInterface>
bool InUbo(const TInterface&) {
    return false;
}

template <>
bool InUbo<GLSLCuniformInfo>(const GLSLCuniformInfo& piq) {
    return piq.isInUBO != 0;
}

class OnlineCompiledShader {
public:
    OnlineCompiledShader() {
        m_pMemory = nullptr;
        m_pOutput = nullptr;
    }

    ~OnlineCompiledShader() { Finalize(); }

    bool Initialize(DeviceImpl<ApiVariationNvn8>*, const GLSLCoutput*);
    void Finalize();

    NVNboolean SetShader(NVNprogram* pNvnProgram) const {
        return nvnProgramSetShaders(pNvnProgram, m_StageCount, m_NvnShaderData);
    }

    int GetInterfaceSlot(ShaderStage, ShaderInterfaceType, const char*) const;

    size_t GetScratchMemorySizePerWarp() const { return m_ScratchMemoryPerWarp; }

    void GetWorkGroupSize(int*, int*, int*) const;

private:
    template <typename TInterface>
    int SearchInterfaceSlot(const TInterface* pFirst, int count, const void* pStringPool,
                            const char* pName, NVNshaderStage stage) const {
        int stageBits = 1 << stage;
        for (int idx = 0; idx < count; ++idx) {
            const TInterface& piq = pFirst[idx];
            const GLSLCpiqName& nameInfo = piq.nameInfo;

            if (!InUbo(piq) && (piq.stagesReferencedIn & stageBits) &&
                strncmp(pName,
                        nn::util::ConstBytePtr(pStringPool, nameInfo.nameOffset).Get<const char>(),
                        nameInfo.nameLength) == 0) {
                int result = GetShaderSlot(piq, stage);
                if (result >= 0) {
                    return result;
                }
            }
        }

        return -1;
    }

    NVNmemoryPool m_NvnMemoryPool;
    void* m_pMemoryBase;
    void* m_pMemory;
    GLSLCoutput* m_pOutput;
    NVNshaderData m_NvnShaderData[6];
    int m_StageCount;
    size_t m_ScratchMemoryPerWarp;
    const GLSLCprogramReflectionHeader* m_pReflectionHeader;
};

bool OnlineCompiledShader::Initialize(DeviceImpl<ApiVariationNvn8>* pDevice,
                                      const GLSLCoutput* pOutput) {
    m_pOutput = static_cast<GLSLCoutput*>(malloc(pOutput->size));
    if (!m_pOutput) {
        return false;
    }
    memcpy(m_pOutput, pOutput, pOutput->size);

    size_t stageDataSize[6] = {};
    const void* pStageData[6] = {};
    m_StageCount = 0;
    size_t memoryPoolSize = 0;
    m_ScratchMemoryPerWarp = 0;

    for (int idxSection = 0; idxSection < static_cast<int>(m_pOutput->numSections); ++idxSection) {
        GLSLCsectionTypeEnum type = m_pOutput->headers[idxSection].genericHeader.common.type;
        if (type == GLSLC_SECTION_TYPE_GPU_CODE) {
            const GLSLCgpuCodeHeader& gpuCodeHeader = m_pOutput->headers[idxSection].gpuCodeHeader;

            memoryPoolSize += gpuCodeHeader.dataSize;
            memoryPoolSize = nn::util::align_up(
                memoryPoolSize, ShaderImpl<ApiVariationNvn8>::GetBinaryCodeAlignment(pDevice));

            const void* pData =
                nn::util::ConstBytePtr(m_pOutput, gpuCodeHeader.common.dataOffset).Get();

            stageDataSize[m_StageCount] = gpuCodeHeader.dataSize;
            pStageData[m_StageCount] =
                nn::util::ConstBytePtr(pData, gpuCodeHeader.dataOffset).Get();
            m_NvnShaderData[m_StageCount].control =
                nn::util::ConstBytePtr(pData, gpuCodeHeader.controlOffset).Get();

            ++m_StageCount;

            m_ScratchMemoryPerWarp = std::max(
                m_ScratchMemoryPerWarp, static_cast<size_t>(gpuCodeHeader.scratchMemBytesPerWarp));
        } else if (type == GLSLC_SECTION_TYPE_REFLECTION) {
            m_pReflectionHeader = &m_pOutput->headers[idxSection].programReflectionHeader;
        }
    }

    memoryPoolSize = nn::util::align_up(memoryPoolSize, 0x1000);
    m_pMemoryBase = malloc(memoryPoolSize + 0x1000);
    if (!m_pMemoryBase) {
        return false;
    }
    m_pMemory = nn::util::BytePtr(m_pMemoryBase).AlignUp(0x1000).Get();

    nn::util::BytePtr pDst(m_pMemory);
    for (int idxStage = 0; idxStage < m_StageCount; ++idxStage) {
        memcpy(pDst.Get(), pStageData[idxStage], stageDataSize[idxStage]);
        pDst.Advance(stageDataSize[idxStage])
            .AlignUp(ShaderImpl<ApiVariationNvn8>::GetBinaryCodeAlignment(pDevice));
    }

    NVNmemoryPoolBuilder memoryPoolBuilder;
    nvnMemoryPoolBuilderSetDevice(&memoryPoolBuilder, pDevice->ToData()->pNvnDevice);
    nvnMemoryPoolBuilderSetDefaults(&memoryPoolBuilder);
    nvnMemoryPoolBuilderSetFlags(&memoryPoolBuilder, NVN_MEMORY_POOL_FLAGS_SHADER_CODE |
                                                         NVN_MEMORY_POOL_FLAGS_GPU_CACHED |
                                                         NVN_MEMORY_POOL_FLAGS_CPU_NO_ACCESS);
    nvnMemoryPoolBuilderSetStorage(&memoryPoolBuilder, m_pMemory, memoryPoolSize);
    nvnMemoryPoolInitialize(&m_NvnMemoryPool, &memoryPoolBuilder);

    NVNbufferAddress address = nvnMemoryPoolGetBufferAddress(&m_NvnMemoryPool);

    ptrdiff_t offset = 0;
    for (int idxStage = 0; idxStage < m_StageCount; ++idxStage) {
        m_NvnShaderData[idxStage].data = offset + address;
        offset += stageDataSize[idxStage];
        offset = nn::util::align_up(offset,
                                    ShaderImpl<ApiVariationNvn8>::GetBinaryCodeAlignment(pDevice));
    }

    return true;
}

void OnlineCompiledShader::Finalize() {
    if (m_pMemoryBase) {
        nvnMemoryPoolFinalize(&m_NvnMemoryPool);
        free(m_pMemoryBase);
        m_pMemoryBase = nullptr;
        m_pMemory = nullptr;
    }

    if (m_pOutput) {
        free(m_pOutput);
        m_pOutput = nullptr;
    }

    m_pReflectionHeader = nullptr;
}

int OnlineCompiledShader::GetInterfaceSlot(ShaderStage stage, ShaderInterfaceType interfaceType,
                                           const char* pName) const {
    const void* pReflectionData =
        nn::util::ConstBytePtr(m_pOutput, m_pReflectionHeader->common.dataOffset).Get();
    const void* pStringPool =
        nn::util::ConstBytePtr(pReflectionData, m_pReflectionHeader->stringPoolOffset).Get();
    NVNshaderStage nvnStage = Nvn::GetShaderStage(stage);
    int ret = -1;

    switch (interfaceType) {
    case ShaderInterfaceType_Input:
        ret = SearchInterfaceSlot(
            nn::util::ConstBytePtr(pReflectionData, m_pReflectionHeader->programInputsOffset)
                .Get<GLSLCProgramInputInfo>(),
            m_pReflectionHeader->numProgramInputs, pStringPool, pName, nvnStage);
        break;

    case ShaderInterfaceType_Output:
        ret = SearchInterfaceSlot(
            nn::util::ConstBytePtr(pReflectionData, m_pReflectionHeader->programOutputsOffset)
                .Get<GLSLCProgramOutputInfo>(),
            m_pReflectionHeader->numProgramOutputs, pStringPool, pName, nvnStage);
        break;

    case ShaderInterfaceType_ConstantBuffer:
        ret = SearchInterfaceSlot(
            nn::util::ConstBytePtr(pReflectionData, m_pReflectionHeader->uniformBlockOffset)
                .Get<GLSLCuniformBlockInfo>(),
            m_pReflectionHeader->numUniformBlocks, pStringPool, pName, nvnStage);
        break;

    case ShaderInterfaceType_UnorderedAccessBuffer:
        ret = SearchInterfaceSlot(
            nn::util::ConstBytePtr(pReflectionData, m_pReflectionHeader->ssboOffset)
                .Get<GLSLCssboInfo>(),
            m_pReflectionHeader->numSsbo, pStringPool, pName, nvnStage);
        break;

    case ShaderInterfaceType_Sampler:
        ret = SearchInterfaceSlot(
            nn::util::ConstBytePtr(pReflectionData, m_pReflectionHeader->uniformOffset)
                .Get<GLSLCuniformInfo>(),
            m_pReflectionHeader->numUniforms, pStringPool, pName, nvnStage);
        break;

    case ShaderInterfaceType_Image:
        ret = SearchInterfaceSlot(
            nn::util::ConstBytePtr(pReflectionData, m_pReflectionHeader->uniformOffset)
                .Get<GLSLCuniformInfo>(),
            m_pReflectionHeader->numUniforms, pStringPool, pName, nvnStage);
        break;

    default:
        break;
    }

    return ret;
}

void OnlineCompiledShader::GetWorkGroupSize(int* pOutWorkGroupSizeX, int* pOutWorkGroupSizeY,
                                            int* pOutWorkGroupSizeZ) const {
    const void* pReflectionData =
        nn::util::ConstBytePtr(m_pOutput, m_pReflectionHeader->common.dataOffset).Get();
    const GLSLCperStageShaderInfo* pPerStageShaderInfo =
        nn::util::ConstBytePtr(pReflectionData, m_pReflectionHeader->shaderInfoOffset)
            .Get<GLSLCperStageShaderInfo>();
    const GLSLCshaderInfoCompute& shaderInfoCompute = pPerStageShaderInfo->shaderInfo[5].compute;

    *pOutWorkGroupSizeX = shaderInfoCompute.workGroupSize[0];
    *pOutWorkGroupSizeY = shaderInfoCompute.workGroupSize[1];
    *pOutWorkGroupSizeZ = shaderInfoCompute.workGroupSize[2];
}

ShaderInitializeResult NvnGlslcCompile(ShaderImpl<ApiVariationNvn8>* pThis, const ShaderInfo& info,
                                       DeviceImpl<ApiVariationNvn8>* pDevice) {
    class CompileObjectFinalizer {
    public:
        explicit CompileObjectFinalizer(GLSLCcompileObject* pCompileObject) {
            m_pCompileObject = pCompileObject;
        }

        ~CompileObjectFinalizer() { GlslcDll::GetInstance().GlslcFinalize(m_pCompileObject); }

    private:
        GLSLCcompileObject* m_pCompileObject;
    };

    GLSLCcompileObject compileObject;
    if (GlslcDll::GetInstance().GlslcInitialize(&compileObject) == 0 ||
        compileObject.initStatus != GLSLC_INIT_SUCCESS) {
        return ShaderInitializeResult_SetupFailed;
    }

    CompileObjectFinalizer compileObjectFinalizer(&compileObject);
    GLSLCoptions& options = compileObject.options;
    options.optionFlags.glslSeparable = info.IsSeparationEnabled();
    options.optionFlags.outputAssembly = 0;
    options.optionFlags.outputGpuBinaries = 1;
    options.optionFlags.outputPerfStats = 0;
    options.optionFlags.outputShaderReflection = 1;
    options.optionFlags.language = GLSLC_LANGUAGE_GLSL;
    options.optionFlags.outputDebugInfo = GLSLC_DEBUG_LEVEL_G0;
    options.optionFlags.spillControl = NO_SPILL;

    options.optionFlags.outputThinGpuBinaries = IsThinBinaryAvailable();
    options.optionFlags.tessellationAndPassthroughGS = 0;
    options.includeInfo.numPaths = 0;
    options.includeInfo.paths = nullptr;
    options.xfbVaryingInfo.numVaryings = 0;
    options.xfbVaryingInfo.varyings = nullptr;
    options.forceIncludeStdHeader = nullptr;

    std::string sources[6];
    const char* ppSources[6];
    NVNshaderStage stages[6];

    compileObject.input.sources = ppSources;
    compileObject.input.stages = stages;
    compileObject.input.count = 0;

    for (int idxStage = 0; idxStage < 6; ++idxStage) {
        ShaderStage stage = static_cast<ShaderStage>(idxStage);
        if (auto pShaderCode = static_cast<const ShaderCode*>(info.GetShaderCodePtr(stage))) {
            sources[compileObject.input.count].assign(static_cast<const char*>(pShaderCode->pCode),
                                                      pShaderCode->codeSize);
            ppSources[compileObject.input.count] = sources[compileObject.input.count].c_str();
            stages[compileObject.input.count] = Nvn::GetShaderStage(stage);
            ++compileObject.input.count;
        }
    }

    uint8_t compileResult = GlslcDll::GetInstance().GlslcCompile(&compileObject);
    const GLSLCcompilationStatus& compilationStatus =
        *compileObject.lastCompiledResults->compilationStatus;

    if (compilationStatus.allocError) {
        return ShaderInitializeResult_SetupFailed;
    }

    if (compileResult == 0 || !compilationStatus.success) {
        return ShaderInitializeResult_SetupFailed;
    }

    pThis->ToData()->pOnlineCompiledShader = malloc(sizeof(OnlineCompiledShader));
    OnlineCompiledShader* pOnlineCompiledShader =
        new (pThis->ToData()->pOnlineCompiledShader.ptr) OnlineCompiledShader();

    if (!pOnlineCompiledShader->Initialize(pDevice,
                                           compileObject.lastCompiledResults->glslcOutput)) {
        return ShaderInitializeResult_SetupFailed;
    }

    return ShaderInitializeResult_Success;
}

ShaderInitializeResult InitializeSourceShader(ShaderImpl<ApiVariationNvn8>* pThis,
                                              const ShaderInfo& info,
                                              DeviceImpl<ApiVariationNvn8>* pDevice) {
    class MutexLocker {
    public:
        explicit MutexLocker(os::Mutex* pMutex) {
            m_pMutex = pMutex;
            m_pMutex->Lock();
        }

        ~MutexLocker() { m_pMutex->Unlock(); }

    private:
        os::Mutex* m_pMutex;
    };

    static os::Mutex s_Mutex(false);
    MutexLocker locker(&s_Mutex);

    GLSLCversion version = GlslcDll::GetInstance().GlslcGetVersion();
    int majorVersionMinimum;
    int majorVersionMaximum;
    int minorVersionMinimum;
    int minorVersionMaximum;
    nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                        NVN_DEVICE_INFO_GLSLC_MIN_SUPPORTED_GPU_CODE_MAJOR_VERSION,
                        &majorVersionMinimum);
    nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                        NVN_DEVICE_INFO_GLSLC_MAX_SUPPORTED_GPU_CODE_MAJOR_VERSION,
                        &majorVersionMaximum);
    nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                        NVN_DEVICE_INFO_GLSLC_MIN_SUPPORTED_GPU_CODE_MINOR_VERSION,
                        &minorVersionMinimum);
    nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                        NVN_DEVICE_INFO_GLSLC_MAX_SUPPORTED_GPU_CODE_MINOR_VERSION,
                        &minorVersionMaximum);
    if (static_cast<int>(version.gpuCodeVersionMajor) < majorVersionMinimum ||
        static_cast<int>(version.gpuCodeVersionMajor) > majorVersionMaximum ||
        static_cast<int>(version.gpuCodeVersionMinor) < minorVersionMinimum ||
        static_cast<int>(version.gpuCodeVersionMinor) > minorVersionMaximum) {
        return ShaderInitializeResult_SetupFailed;
    }

    ShaderInitializeResult initializeResult = NvnGlslcCompile(pThis, info, pDevice);
    if (initializeResult != ShaderInitializeResult_Success) {
        return initializeResult;
    }

    if (static_cast<OnlineCompiledShader*>(pThis->ToData()->pOnlineCompiledShader)
            ->SetShader(pThis->ToData()->pNvnProgram) != true) {
        return ShaderInitializeResult_SetupFailed;
    }

    return ShaderInitializeResult_Success;
}

void ReassembleControlSection(void* pDestination,
                              const NvnDecomposedControlSection* pDecomposedControlSection) {
    struct ReassembleControlSectionInfo {
        int offsetDataOffset;
        int offsetDataSize;
        nn::util::BinTPtr<const void> NvnDecomposedControlSection::*pSrcData;
    };

    const ReassembleControlSectionInfo ReassembleControlSectionInfoArray[5] = {
        {20, 24, &NvnDecomposedControlSection::pAssemblyData},
        {32, 28, &NvnDecomposedControlSection::pAssemblyLocalsData},
        {1776, 1780, &NvnDecomposedControlSection::pSpecializationData},
        {1992, 1996, &NvnDecomposedControlSection::pPragmaData},
        {2024, 2028, &NvnDecomposedControlSection::pUniform64InfoData},
    };

    const void* const pMetaData = pDecomposedControlSection->pMetaData.Get();
    const int offsetAssemblyDataOffset = 20;
    ptrdiff_t assemblyDataOffset =
        *nn::util::ConstBytePtr(pMetaData, offsetAssemblyDataOffset).Get<int>();

    memcpy(pDestination, pMetaData, assemblyDataOffset);

    for (int idxSection = 0, sectionCount = 5; idxSection < sectionCount; ++idxSection) {
        const ReassembleControlSectionInfo& target = ReassembleControlSectionInfoArray[idxSection];
        if (const void* pSrcData = (pDecomposedControlSection->*target.pSrcData).Get()) {
            ptrdiff_t dataOffset =
                *nn::util::ConstBytePtr(pMetaData, target.offsetDataOffset).Get<int>();
            void* pDstData = nn::util::BytePtr(pDestination, dataOffset).Get();
            size_t dataSize = *nn::util::ConstBytePtr(pMetaData, target.offsetDataSize).Get<int>();

            memcpy(pDstData, pSrcData, dataSize);
        }
    }
}

ShaderInitializeResult InitializeBinaryShader(ShaderImpl<ApiVariationNvn8>* pThis,
                                              const ShaderInfo& info) {
    int nSources = 0;
    NVNshaderData sources[6];

    for (int idxStage = 0; idxStage < 6; ++idxStage) {
        auto stage = static_cast<ShaderStage>(idxStage);
        auto shaderData = static_cast<const NVNshaderData*>(info.GetShaderCodePtr(stage));

        if (shaderData) {
            sources[nSources++] = *shaderData;

            if (info.ToData()->flags.GetBit(info.ToData()->Flag_ResShader)) {
                auto pNvnShaderCode = reinterpret_cast<const NvnShaderCode*>(shaderData);
                if (const NvnDecomposedControlSection* pDecomposedControlSection =
                        pNvnShaderCode->pDecomposedControlSection.Get()) {
                    void* pControl = const_cast<void*>(pNvnShaderCode->pControl.Get());
                    ReassembleControlSection(pControl, pDecomposedControlSection);
                }
            }
        }
    }

    if (!nvnProgramSetShaders(pThis->ToData()->pNvnProgram, nSources, sources)) {
        return ShaderInitializeResult_SetupFailed;
    }

    if (info.ToData()->flags.GetBit(info.ToData()->Flag_ResShader)) {
        auto pResShaderProgram = nn::util::ConstBytePtr(&info, 0).Get<ResShaderProgramData>();
        pThis->ToData()->pReflection = pResShaderProgram->pShaderReflection.Get();
    }

    return ShaderInitializeResult_Success;
}

}  // namespace

size_t ShaderImpl<ApiVariationNvn8>::GetBinaryCodeAlignment(DeviceImpl<ApiVariationNvn8>*) {
    return 256;
}

ShaderImpl<ApiVariationNvn8>::ShaderImpl() {
    state = State_NotInitialized;
}

ShaderImpl<ApiVariationNvn8>::~ShaderImpl() {}

ShaderInitializeResult
ShaderImpl<ApiVariationNvn8>::Initialize(DeviceImpl<ApiVariationNvn8>* pDevice,
                                         const ShaderInfo& info) {
    pNvnProgram = &nvnProgram;
    flags = info.ToData()->flags;
    nvnProgramInitialize(pNvnProgram, pDevice->ToData()->pNvnDevice);
    ShaderInitializeResult result = ShaderInitializeResult_Success;

    switch (info.GetCodeType()) {
    case ShaderCodeType_Source:
        result = InitializeSourceShader(this, info, pDevice);
        break;

    case ShaderCodeType_Binary:
        result = InitializeBinaryShader(this, info);
        break;

    default:
        result = ShaderInitializeResult_InvalidType;
        break;
    }

    if (result == ShaderInitializeResult_Success) {
        if (!info.IsSeparationEnabled()) {
            nvnShaderStageBits = (info.GetShaderCodePtr(ShaderStage_Compute)) ?
                                     NVN_SHADER_STAGE_COMPUTE_BIT :
                                     NVN_SHADER_STAGE_ALL_GRAPHICS_BITS;
        }

        flags.SetBit(Flag_Shared, false);
        state = State_Initialized;
    }

    return result;
}

void ShaderImpl<ApiVariationNvn8>::Finalize(DeviceImpl<ApiVariationNvn8>*) {
    nvnProgramFinalize(pNvnProgram);
    pNvnProgram = nullptr;

    if (pOnlineCompiledShader) {
        // inlined, is this how it should be called?
        static_cast<OnlineCompiledShader*>(pOnlineCompiledShader)->~OnlineCompiledShader();
        free(pOnlineCompiledShader);
        pOnlineCompiledShader = nullptr;
    }

    state = State_NotInitialized;
}

int ShaderImpl<ApiVariationNvn8>::GetInterfaceSlot(ShaderStage stage,
                                                   ShaderInterfaceType shaderInterfaceType,
                                                   const char* pName) const {
    if (pOnlineCompiledShader) {
        return static_cast<const OnlineCompiledShader*>(pOnlineCompiledShader)
            ->GetInterfaceSlot(stage, shaderInterfaceType, pName);
    }

    static nn::util::BinTPtr<ResShaderReflectionStageData> const ResShaderReflectionData::*
        s_pResShaderReflectionStages[6] = {
            &ResShaderReflectionData::pVertexReflection,
            &ResShaderReflectionData::pHullReflection,
            &ResShaderReflectionData::pDomainReflection,
            &ResShaderReflectionData::pGeometryReflection,
            &ResShaderReflectionData::pPixelReflection,
            &ResShaderReflectionData::pComputeReflection,
        };

    static nn::util::BinTPtr<nn::util::ResDic> const ResShaderReflectionStageData::*
        s_pInterfaceDics[6] = {
            &ResShaderReflectionStageData::pShaderInputDic,
            &ResShaderReflectionStageData::pShaderOutputDic,
            &ResShaderReflectionStageData::pSamplerDic,
            &ResShaderReflectionStageData::pConstantBufferDic,
            &ResShaderReflectionStageData::pUnorderedAccessBufferDic,
            &ResShaderReflectionStageData::pImageDic,
        };

    static int32_t const ResShaderReflectionStageData::*s_pOffsets[6] = {
        nullptr,
        &ResShaderReflectionStageData::offsetShaderOutput,
        &ResShaderReflectionStageData::offsetSampler,
        &ResShaderReflectionStageData::offsetConstantBuffer,
        &ResShaderReflectionStageData::offsetUnorderedAccessBuffer,
        &ResShaderReflectionStageData::offsetImage,
    };

    static nn::util::BinTPtr<nn::util::ResDic> const ResShaderReflectionStageData2::*
        s_pInterfaceDics2[2] = {
            &ResShaderReflectionStageData2::pSeparateTextureDic,
            &ResShaderReflectionStageData2::pSeparateSamplerDic,
        };

    static int32_t const ResShaderReflectionStageData2::*s_pOffsets2[2] = {
        &ResShaderReflectionStageData2::offsetSeparateTexture,
        &ResShaderReflectionStageData2::offsetSeparateSampler,
    };

    auto pResShaderReflection = static_cast<const ResShaderReflectionData*>(pReflection);
    if (const ResShaderReflectionStageData* pResShaderReflectionStage =
            (pResShaderReflection->*s_pResShaderReflectionStages[stage]).Get()) {
        const nn::util::ResDic* pResDic = nullptr;
        int offset = 0;

        if (shaderInterfaceType <= ShaderInterfaceType_Image) {
            pResDic = (pResShaderReflectionStage->*s_pInterfaceDics[shaderInterfaceType]).Get();
            if (s_pOffsets[shaderInterfaceType] != nullptr)
                offset = pResShaderReflectionStage->*s_pOffsets[shaderInterfaceType];
        } else {
            if (const ResShaderReflectionStageData2* pResShaderReflectionStage2 =
                    pResShaderReflectionStage->pReflectionStageData2.Get()) {
                int shaderInterfaceType2 = shaderInterfaceType - 6;
                pResDic =
                    (pResShaderReflectionStage2->*s_pInterfaceDics2[shaderInterfaceType2]).Get();
                offset = pResShaderReflectionStage2->*s_pOffsets2[shaderInterfaceType2];
            }
        }

        if (pResDic) {
            int idxFound = pResDic->FindIndex(pName);
            if (idxFound >= 0) {
                return pResShaderReflectionStage->pShaderSlotArray.Get()[idxFound + offset];
            }
        }
    }

    return -1;
}

void ShaderImpl<ApiVariationNvn8>::GetWorkGroupSize(int* pOutWorkGroupSizeX,
                                                    int* pOutWorkGroupSizeY,
                                                    int* pOutWorkGroupSizeZ) const {
    if (pOnlineCompiledShader) {
        return static_cast<const OnlineCompiledShader*>(pOnlineCompiledShader)
            ->GetWorkGroupSize(pOutWorkGroupSizeX, pOutWorkGroupSizeY, pOutWorkGroupSizeZ);
    }
    const ResShaderReflectionData* pResShaderReflection = pReflection;

    const ResShaderReflectionStageData* pPerStageShaderInfo =
        pResShaderReflection->pComputeReflection.Get();

    *pOutWorkGroupSizeX = pPerStageShaderInfo->computeWorkGroupSizeX;
    *pOutWorkGroupSizeY = pPerStageShaderInfo->computeWorkGroupSizeY;
    *pOutWorkGroupSizeZ = pPerStageShaderInfo->computeWorkGroupSizeZ;
}

}  // namespace nn::gfx::detail