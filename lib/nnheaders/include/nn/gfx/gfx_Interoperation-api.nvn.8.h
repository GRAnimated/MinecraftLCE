// this file's name isn't confirmed, following the naming structure anyways

#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nvn/nvn.h>

namespace nn::gfx {

template <>
class TInteroperation<ApiVariationNvn8> {
    static void ConvertToGfxDevice(TDevice<ApiVariationNvn8>*, NVNdevice*);
    static void ConvertToGfxQueue(TQueue<ApiVariationNvn8>*, NVNqueue*, TDevice<ApiVariationNvn8>*);
    static void ConvertToGfxMemoryPool(TMemoryPool<ApiVariationNvn8>*, NVNmemoryPool*, void*);
    static void ConvertToGfxDescriptorPool(TDescriptorPool<ApiVariationNvn8>*, NVNtexturePool*);
    static void ConvertToGfxDescriptorPool(TDescriptorPool<ApiVariationNvn8>*, NVNsamplerPool*);
    static void ConvertToGfxBuffer(TBuffer<ApiVariationNvn8>*, NVNbuffer*);
    static void ConvertToGfxCommandBuffer(TCommandBuffer<ApiVariationNvn8>*,
                                          TDevice<ApiVariationNvn8>*, NVNcommandBuffer*);
    static void ConvertToGfxSampler(TSampler<ApiVariationNvn8>*, NVNsampler*);
    static void ConvertToGfxShader(TShader<ApiVariationNvn8>*, NVNprogram*, bool, int);
    static void ConvertToGfxTexture(TTexture<ApiVariationNvn8>*, NVNtexture*);
    static void ConvertToGfxTextureView(TTextureView<ApiVariationNvn8>*, NVNtexture*,
                                        NVNtextureView*);
    static void ConvertToGfxColorTargetView(TColorTargetView<ApiVariationNvn8>*, NVNtexture*,
                                            NVNtextureView*);
    static void ConvertToGfxDepthStencilView(TDepthStencilView<ApiVariationNvn8>*, NVNtexture*,
                                             NVNtextureView*);
    static NVNformat ConvertToNvnFormat(ImageFormat);
    static NVNformat ConvertToNvnFormat(AttributeFormat);
};

}  // namespace nn::gfx