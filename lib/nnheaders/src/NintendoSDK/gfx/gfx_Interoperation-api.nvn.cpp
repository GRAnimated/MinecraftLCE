#include <nn/gfx/gfx_Interoperation-api.nvn.8.h>

#include <nn/gfx/gfx_Buffer.h>
#include <nn/gfx/gfx_CommandBuffer.h>
#include <nn/gfx/gfx_DescriptorPool.h>
#include <nn/gfx/gfx_Device.h>
#include <nn/gfx/gfx_MemoryPool.h>
#include <nn/gfx/gfx_Queue.h>
#include <nn/gfx/gfx_Sampler.h>
#include <nn/gfx/gfx_Shader.h>
#include <nn/gfx/gfx_Texture.h>

#include "detail/gfx_CommonHelper.h"
#include "detail/gfx_NvnHelper.h"

namespace nn::gfx {

void TInteroperation<ApiVariationNvn8>::ConvertToGfxDevice(TDevice<ApiVariationNvn8>* pGfxDevice,
                                                           NVNdevice* pNvnDevice) {
    TDevice<ApiVariationNvn8>::DataType& obj = pGfxDevice->ToData();
    detail::UseMiddleWare();
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.pNvnDevice = pNvnDevice;
    obj.supportedFeatures = detail::Nvn::GetDeviceFeature(pNvnDevice);
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxQueue(TQueue<ApiVariationNvn8>* pGfxQueue,
                                                          NVNqueue* pNvnQueue,
                                                          TDevice<ApiVariationNvn8>* pDevice) {
    TQueue<ApiVariationNvn8>::DataType& obj = pGfxQueue->ToData();
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.pNvnQueue = pNvnQueue;
    obj.pNnDevice = pDevice;
    obj.pImpl = nullptr;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxMemoryPool(
    TMemoryPool<ApiVariationNvn8>* pGfxMemoryPool, NVNmemoryPool* pNvnMemoryPool, void* pMemory) {
    TMemoryPool<ApiVariationNvn8>::DataType& obj = pGfxMemoryPool->ToData();
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.pNvnMemoryPool = pNvnMemoryPool;
    obj.pMemory = pMemory;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxDescriptorPool(
    TDescriptorPool<ApiVariationNvn8>* pGfxDescriptorPool, NVNtexturePool* pNvnTexturePool) {
    TDescriptorPool<ApiVariationNvn8>::DataType& obj = pGfxDescriptorPool->ToData();
    obj.descriptorPoolType = DescriptorPoolType_TextureView;
    obj.slotCount = nvnTexturePoolGetSize(pNvnTexturePool);
    obj.pDescriptorPool = pNvnTexturePool;
    obj.reservedSlots = 256;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.state = obj.State_Initialized;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxDescriptorPool(
    TDescriptorPool<ApiVariationNvn8>* pGfxDescriptorPool, NVNsamplerPool* pNvnSamplerPool) {
    TDescriptorPool<ApiVariationNvn8>::DataType& obj = pGfxDescriptorPool->ToData();
    obj.descriptorPoolType = DescriptorPoolType_Sampler;
    obj.slotCount = nvnSamplerPoolGetSize(pNvnSamplerPool);
    obj.pDescriptorPool = pNvnSamplerPool;
    obj.reservedSlots = 256;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.state = obj.State_Initialized;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxBuffer(TBuffer<ApiVariationNvn8>* pGfxBuffer,
                                                           NVNbuffer* pNvnBuffer) {
    TBuffer<ApiVariationNvn8>::DataType& obj = pGfxBuffer->ToData();
    NVNmemoryPoolFlags memoryPoolFlags = nvnMemoryPoolGetFlags(nvnBufferGetMemoryPool(pNvnBuffer));
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_CpuCached, memoryPoolFlags & NVN_MEMORY_POOL_FLAGS_CPU_CACHED);
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.pNvnBuffer = pNvnBuffer;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxCommandBuffer(
    TCommandBuffer<ApiVariationNvn8>* pGfxCommandBuffer, TDevice<ApiVariationNvn8>* pDevice,
    NVNcommandBuffer* pNvnCommandBuffer) {
    TCommandBuffer<ApiVariationNvn8>::DataType& obj = pGfxCommandBuffer->ToData();
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.pNnDevice = pDevice;
    obj.pNvnCommandBuffer = pNvnCommandBuffer;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxSampler(TSampler<ApiVariationNvn8>* pGfxSampler,
                                                            NVNsampler* pNvnSampler) {
    TSampler<ApiVariationNvn8>::DataType& obj = pGfxSampler->ToData();
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.pNvnSampler = pNvnSampler;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxShader(TShader<ApiVariationNvn8>* pGfxShader,
                                                           NVNprogram* pNvnProgram,
                                                           bool enableSeperation, int shaderBits) {
    TShader<ApiVariationNvn8>::DataType& obj = pGfxShader->ToData();
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.flags.SetBit(obj.Flag_SeparationEnable, enableSeperation);
    obj.nvnShaderStageBits = (shaderBits & ShaderStageBit_Compute) ?
                                 NVN_SHADER_STAGE_COMPUTE_BIT :
                                 NVN_SHADER_STAGE_ALL_GRAPHICS_BITS;
    obj.pNvnProgram = pNvnProgram;
    obj.pReflection = nullptr;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxTexture(TTexture<ApiVariationNvn8>* pGfxTarget,
                                                            NVNtexture* pNvnTexture) {
    TTexture<ApiVariationNvn8>::DataType& obj = pGfxTarget->ToData();
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.pNvnTexture = pNvnTexture;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxTextureView(
    TTextureView<ApiVariationNvn8>* pGfxTargetView, NVNtexture* pNvnTexture,
    NVNtextureView* pNvnTextureView) {
    TTextureView<ApiVariationNvn8>::DataType& obj = pGfxTargetView->ToData();
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.pNvnTexture = pNvnTexture;
    obj.pNvnTextureView = pNvnTextureView;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxColorTargetView(
    TColorTargetView<ApiVariationNvn8>* pGfxTargetView, NVNtexture* pNvnTexture,
    NVNtextureView* pNvnTextureView) {
    TColorTargetView<ApiVariationNvn8>::DataType& obj = pGfxTargetView->ToData();
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.pNvnTexture = pNvnTexture;
    obj.pNvnTextureView = pNvnTextureView;
}

void TInteroperation<ApiVariationNvn8>::ConvertToGfxDepthStencilView(
    TDepthStencilView<ApiVariationNvn8>* pGfxDepthStencilView, NVNtexture* pNvnTexture,
    NVNtextureView* pNvnTextureView) {
    TDepthStencilView<ApiVariationNvn8>::DataType& obj = pGfxDepthStencilView->ToData();
    obj.state = obj.State_Initialized;
    obj.flags.SetBit(obj.Flag_Shared, true);
    obj.pNvnTexture = pNvnTexture;
    obj.pNvnTextureView = pNvnTextureView;
}

NVNformat TInteroperation<ApiVariationNvn8>::ConvertToNvnFormat(ImageFormat format) {
    return detail::Nvn::GetImageFormat(format);
}

NVNformat TInteroperation<ApiVariationNvn8>::ConvertToNvnFormat(AttributeFormat format) {
    return detail::Nvn::GetAttributeFormat(format);
}

}  // namespace nn::gfx