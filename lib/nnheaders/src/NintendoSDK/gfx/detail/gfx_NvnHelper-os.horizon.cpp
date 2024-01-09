#include "gfx_NvnHelper.h"

namespace nn::gfx::detail {

// todo: figure out where to put these?
GlslcDll::GlslcCompilePreSpecializedType GetGlslcCompilePreSpecializedFunction();
GlslcDll::GlslcCompileSpecializedType GetGlslcCompileSpecializedFunction();
GlslcDll::GlslcInitializeType GetGlslcInitializeFunction();
GlslcDll::GlslcFinalizeType GetGlslcFinalizeFunction();
GlslcDll::GlslcCompileType GetGlslcCompileFunction();
GlslcDll::GlslcGetVersionType GetGlslcGetVersionFunction();
GlslcDll::GlslcSetAllocatorType GetGlslcSetAllocatorFunction();
GlslcDll::GlslcGetDefaultOptionsType GetGlslcGetDefaultOptionsFunction();

int Nvn::GetFirstScanBufferIndex() {
    return 0;
}

void Nvn::SetPackagedTextureDataImpl(NVNtextureBuilder*, const TextureInfo&,
                                     MemoryPoolImpl<ApiVariationNvn8>*, ptrdiff_t, size_t) {}

void Nvn::SetTextureViewFormat(NVNtextureView* pTextureView, NVNformat value, const NVNtexture*) {
    nvnTextureViewSetFormat(pTextureView, value);
}

TimeSpan Nvn::ToTimeSpan(int64_t timestamp) {
    return TimeSpan::FromNanoSeconds((timestamp * 13) >> 3);
}

bool GlslcDll::Initialize() {
    GlslcCompilePreSpecialized = GetGlslcCompilePreSpecializedFunction();
    GlslcCompileSpecialized = GetGlslcCompileSpecializedFunction();
    GlslcInitialize = GetGlslcInitializeFunction();
    GlslcFinalize = GetGlslcFinalizeFunction();
    GlslcCompile = GetGlslcCompileFunction();
    GlslcGetVersion = GetGlslcGetVersionFunction();
    GlslcSetAllocator = GetGlslcSetAllocatorFunction();
    GlslcGetDefaultOptions = GetGlslcGetDefaultOptionsFunction();

    return GlslcCompilePreSpecialized && GlslcCompileSpecialized && GlslcInitialize &&
           GlslcFinalize && GlslcCompile && GlslcGetVersion && GlslcSetAllocator &&
           GlslcGetDefaultOptions;
}

void GlslcDll::Finalize() {}

bool GlslcDll::IsInitialized() const {
    return GlslcCompilePreSpecialized != nullptr;
}

bool IsThinBinaryAvailable() {
    return true;
}

}  // namespace nn::gfx::detail