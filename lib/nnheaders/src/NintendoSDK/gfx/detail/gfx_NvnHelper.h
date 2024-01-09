#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_GpuAddress.h>
#include <nn/time.h>
#include <nn/util.h>
#include <nn/util/util_BitPack.h>
#include <nvn/nvn.h>
#include <nvn/nvn_FuncPtrInline.h>
#include <nvnTool/nvnTool_GlslcInterface.h>

namespace nn::gfx {

struct ImageFormatProperty;
class TextureInfo;
class SwapChainInfo;

namespace detail {

enum NvnDeviceFeature {
    NvnDeviceFeature_SupportMinMaxFiltering,
    NvnDeviceFeature_SupportStencil8Format,
    NvnDeviceFeature_SupportAstcFormat,
    NvnDeviceFeature_SupportConservativeRaster,
    NvnDeviceFeature_SupportZeroFromUnmappedVirtualPoolPage,
    NvnDeviceFeature_SupportPassthroughGeometryShader,
    NvnDeviceFeature_SupportViewportSwizzle,
    NvnDeviceFeature_SupportSparseTiledPackagedTexture,
    NvnDeviceFeature_AdvancedBlendModes,
    NvnDeviceFeature_DrawTexture,
    NvnDeviceFeature_TargetIndependentRasterization,
    NvnDeviceFeature_FragmentCoverageToColor,
    NvnDeviceFeature_PostDepthCoverage,
    NvnDeviceFeature_ImagesUsingTextureHandles,
    NvnDeviceFeature_SampleLocations,
    NvnDeviceFeature_SupportFragmentShaderInterlock,
    NvnDeviceFeature_SupportsDebugLayer
};

class Nvn {
public:
    static int GetCpuMapAccess(int);
    static NVNformat GetImageFormat(ImageFormat);
    static NVNformat GetAttributeFormat(AttributeFormat);
    static NVNtextureTarget GetImageTarget(ImageDimension);
    static NVNdepthFunc GetDepthFunction(ComparisonFunction);
    static NVNstencilOp GetStencilOperation(StencilOperation);
    static NVNstencilFunc GetStencilFunction(ComparisonFunction);
    static NVNblendEquation GetBlendEquation(BlendFunction);
    static NVNblendFunc GetBlendFunction(BlendFactor);
    static NVNlogicOp GetLogicOperation(LogicOperation);
    static NVNfrontFace GetFrontFace(FrontFace);
    static NVNpolygonMode GetFillMode(FillMode);
    static NVNdrawPrimitive GetDrawPrimitive(PrimitiveTopology);
    static NVNminFilter GetMinFilter(FilterMode);
    static NVNmagFilter GetMagFilter(FilterMode);
    static NVNwrapMode GetWrapMode(TextureAddressMode);
    static NVNshaderStage GetShaderStage(ShaderStage);
    static int GetShaderStageBits(int);
    static NVNcompareFunc GetRComparisonFunction(ComparisonFunction);
    static NVNindexType GetIndexFormat(IndexFormat);
    static NVNface GetCullMode(CullMode);
    static int GetMemoryPoolFlags(int);
    static NVNbufferAddress GetBufferAddress(const GpuAddress);
    static NVNcounterType GetCounterType(QueryTarget);
    static nn::util::BitPack32 GetDeviceFeature(const NVNdevice*);
    static void SetupScanBufferTextureInfo(TextureInfo*, const SwapChainInfo&);
    static TimeSpan ToTimeSpan(int64_t);
    static ImageFormat GetGfxImageFormat(NVNformat);
    static void GetImageFormatProperty(ImageFormatProperty*, NVNformat);
    static int GetFirstScanBufferIndex();
    static void SetPackagedTextureDataImpl(NVNtextureBuilder*, const TextureInfo&,
                                           MemoryPoolImpl<ApiVariationNvn8>*, ptrdiff_t, size_t);
    static void SetTextureViewFormat(NVNtextureView*, NVNformat, const NVNtexture*);
    static void DebugCallback(NVNdebugCallbackSource, NVNdebugCallbackType, int,
                              NVNdebugCallbackSeverity, const char*, void*);
};

class GlslcDll {
    NN_NO_COPY(GlslcDll);

public:
    static GlslcDll& GetInstance();

    GlslcDll();
    ~GlslcDll();
    bool Initialize();
    void Finalize();
    bool IsInitialized() const;

    typedef bool (*GlslcCompilePreSpecializedType)(GLSLCcompileObject*);
    typedef const GLSLCoutput* const* (*GlslcCompileSpecializedType)(
        GLSLCcompileObject*, const GLSLCspecializationBatch*);
    typedef uint8_t (*GlslcInitializeType)(GLSLCcompileObject*);
    typedef void (*GlslcFinalizeType)(GLSLCcompileObject*);
    typedef uint8_t (*GlslcCompileType)(GLSLCcompileObject*);
    typedef GLSLCversion (*GlslcGetVersionType)();
    typedef void (*GlslcSetAllocatorType)(GLSLCallocateFunction, GLSLCfreeFunction,
                                          GLSLCreallocateFunction, void*);
    typedef GLSLCoptions (*GlslcGetDefaultOptionsType)();

    GlslcCompilePreSpecializedType GlslcCompilePreSpecialized;
    GlslcCompileSpecializedType GlslcCompileSpecialized;
    GlslcInitializeType GlslcInitialize;
    GlslcFinalizeType GlslcFinalize;
    GlslcInitializeType GlslcCompile;
    GlslcGetVersionType GlslcGetVersion;
    GlslcSetAllocatorType GlslcSetAllocator;
    GlslcGetDefaultOptionsType GlslcGetDefaultOptions;

private:
    void* m_hDll;
};

bool IsThinBinaryAvailable();

}  // namespace detail

}  // namespace nn::gfx