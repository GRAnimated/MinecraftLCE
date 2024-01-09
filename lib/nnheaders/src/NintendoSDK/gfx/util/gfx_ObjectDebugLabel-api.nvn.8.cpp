#include <nn/gfx/gfx_Common.h>

#include <nn/gfx/gfx_Buffer.h>
#include <nn/gfx/gfx_MemoryPool.h>
#include <nn/gfx/gfx_Sampler.h>
#include <nn/gfx/gfx_Texture.h>

#include <nvn/nvn_FuncPtrInline.h>

namespace nn::gfx::util {

template <>
void SetMemoryPoolDebugLabel<ApiVariationNvn8>(TMemoryPool<ApiVariationNvn8>* pMemoryPool,
                                               const char* label) {
    nvnMemoryPoolSetDebugLabel(pMemoryPool->ToData()->pNvnMemoryPool, label);
}

template <>
void SetBufferDebugLabel<ApiVariationNvn8>(TBuffer<ApiVariationNvn8>* pBuffer, const char* label) {
    nvnBufferSetDebugLabel(pBuffer->ToData()->pNvnBuffer, label);
}

template <>
void SetTextureDebugLabel<ApiVariationNvn8>(TTexture<ApiVariationNvn8>* pTexture,
                                            const char* label) {
    nvnTextureSetDebugLabel(pTexture->ToData()->pNvnTexture, label);
}

template <>
void SetSamplerDebugLabel<ApiVariationNvn8>(TSampler<ApiVariationNvn8>* pSampler,
                                            const char* label) {
    nvnSamplerSetDebugLabel(pSampler->ToData()->pNvnSampler, label);
}

}  // namespace nn::gfx::util