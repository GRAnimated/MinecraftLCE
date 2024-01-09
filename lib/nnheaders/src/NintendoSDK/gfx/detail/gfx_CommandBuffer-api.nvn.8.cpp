#include <nn/gfx/detail/gfx_CommandBuffer-api.nvn.8.h>

#include <nn/gfx/detail/gfx_Buffer-api.nvn.8.h>
#include <nn/gfx/detail/gfx_DescriptorPool-api.nvn.8.h>
#include <nn/gfx/detail/gfx_Device-api.nvn.8.h>
#include <nn/gfx/detail/gfx_MemoryPool-api.nvn.8.h>
#include <nn/gfx/detail/gfx_Pipeline-api.nvn.8.h>
#include <nn/gfx/detail/gfx_RootSignature-api.nvn.8.h>
#include <nn/gfx/detail/gfx_Shader-api.nvn.8.h>
#include <nn/gfx/detail/gfx_State-api.nvn.8.h>
#include <nn/gfx/detail/gfx_Texture-api.nvn.8.h>
#include <nn/gfx/gfx_DescriptorSlot.h>
#include <nn/gfx/gfx_StateInfo.h>
#include <nn/gfx/gfx_TextureInfo.h>
#include <nn/util/util_BytePtr.h>

#include <algorithm>

#include "gfx_CommonHelper.h"
#include "gfx_NvnHelper.h"

namespace nn::gfx::detail {

namespace {

template <typename T>
T* ToPtr(const DescriptorSlot& slot) {
    return reinterpret_cast<T*>(slot.ToData()->value);
}

void GetNvnCopyRegion(int* pOffsetY, int* pHeight, int* pOffsetZ, int* pDepth,
                      const TextureCopyRegion& region, NVNtextureTarget target) {
    *pOffsetY = region.GetOffsetV();
    *pHeight = region.GetHeight();
    *pOffsetZ = region.GetOffsetW();
    *pDepth = region.GetDepth();

    switch (target) {
    case NVN_TEXTURE_TARGET_1D_ARRAY:
        *pOffsetY = region.GetSubresource().GetArrayIndex();
        *pHeight = std::max(region.GetArrayLength(), 1);
        break;

    case NVN_TEXTURE_TARGET_2D_ARRAY:
    case NVN_TEXTURE_TARGET_2D_MULTISAMPLE_ARRAY:
        *pOffsetZ = region.GetSubresource().GetArrayIndex();
        *pDepth = std::max(region.GetArrayLength(), 1);
        break;

    default:
        break;
    }
}

void GetNvnCopyStride(ptrdiff_t* pRowStride, ptrdiff_t* pImageStride,
                      const BufferTextureCopyRegion& region, NVNtexture* pTexture) {
    ptrdiff_t rowStride = 0;
    ptrdiff_t imageStride = 0;

    if (region.GetBufferImageWidth() != 0 || region.GetBufferImageHeight() != 0) {
        NVNformat nvnFormat = nvnTextureGetFormat(pTexture);
        ImageFormat imageFormat = Nvn::GetGfxImageFormat(nvnFormat);
        ChannelFormat channelFormat = GetChannelFormat(imageFormat);

        int width =
            ((region.GetBufferImageWidth() != 0) ? region.GetBufferImageWidth() :
                                                   region.GetTextureCopyRegion().GetWidth());
        rowStride = width * GetBytePerPixel(channelFormat);

        if (IsCompressedFormat(channelFormat)) {
            rowStride /= GetBlockWidth(channelFormat) * GetBlockHeight(channelFormat);
        }
    }

    if (region.GetBufferImageHeight() != 0) {
        imageStride = region.GetBufferImageHeight() * rowStride;
    }

    *pRowStride = rowStride;
    *pImageStride = imageStride;
}

void SetTextureAndSampler(CommandBufferImpl<ApiVariationNvn8>* pNnCb, ShaderStage stage, int slot,
                          unsigned int nvnTextureID, unsigned int nvnSamplerID) {
    const DeviceImpl<ApiVariationNvn8>* pNnDevice = pNnCb->ToData()->pNnDevice;
    NVNtextureHandle textureHandle =
        nvnDeviceGetTextureHandle(pNnDevice->ToData()->pNvnDevice, nvnTextureID, nvnSamplerID);

    nvnCommandBufferBindTexture(pNnCb->ToData()->pNvnCommandBuffer, Nvn::GetShaderStage(stage),
                                slot, textureHandle);
}

void CommandBufferMemoryCallbackProcedure([[maybe_unused]] NVNcommandBuffer* pNvnCommandBuffer,
                                          NVNcommandBufferMemoryEvent event, size_t minSize,
                                          void* pCallbackData) {
    auto pThis = static_cast<CommandBufferImpl<ApiVariationNvn8>*>(pCallbackData);
    CommandBufferImpl<ApiVariationNvn8>::DataType& obj = pThis->ToData();

    auto pCommandBuffer = reinterpret_cast<TCommandBuffer<ApiVariationNvn8>*>(pThis);
    OutOfMemoryEventArg arg{minSize};

    switch (event) {
    case NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_COMMAND_MEMORY:
        reinterpret_cast<CommandBufferImpl<ApiVariationNvn8>::OutOfMemoryEventCallback>(
            obj.pOutOfCommandMemoryCallback.ptr)(pCommandBuffer, arg);
        break;

    case NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_CONTROL_MEMORY:
        reinterpret_cast<CommandBufferImpl<ApiVariationNvn8>::OutOfMemoryEventCallback>(
            obj.pOutOfControlMemoryCallback.ptr)(pCommandBuffer, arg);
        break;

    default:
        NN_UNEXPECTED_DEFAULT;
        break;
    }
}

}  // namespace

size_t CommandBufferImpl<ApiVariationNvn8>::GetCommandMemoryAlignment(
    DeviceImpl<ApiVariationNvn8>* pDevice) {
    int align;
    nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                        NVN_DEVICE_INFO_COMMAND_BUFFER_COMMAND_ALIGNMENT, &align);
    return align;
}

size_t CommandBufferImpl<ApiVariationNvn8>::GetControlMemoryAlignment(
    DeviceImpl<ApiVariationNvn8>* pDevice) {
    int align;
    nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                        NVN_DEVICE_INFO_COMMAND_BUFFER_CONTROL_ALIGNMENT, &align);
    return align;
}

CommandBufferImpl<ApiVariationNvn8>::CommandBufferImpl() {
    state = State_NotInitialized;
}

CommandBufferImpl<ApiVariationNvn8>::~CommandBufferImpl() {}

void CommandBufferImpl<ApiVariationNvn8>::Initialize(DeviceImpl<ApiVariationNvn8>* pDevice,
                                                     [[maybe_unused]] const InfoType& info) {
    pNnDevice = pDevice;
    NVNdevice* pNvnDevice = pDevice->ToData()->pNvnDevice;

    pNvnCommandBuffer = &nvnCommandBuffer;

    nvnCommandBufferInitialize(pNvnCommandBuffer, pNvnDevice);

    pOutOfCommandMemoryCallback = nullptr;
    pOutOfControlMemoryCallback = nullptr;

    nvnCommandBufferSetMemoryCallback(pNvnCommandBuffer, CommandBufferMemoryCallbackProcedure);
    nvnCommandBufferSetMemoryCallbackData(pNvnCommandBuffer, this);

    hNvnCommandBuffer = 0;

    flags.SetBit(Flag_ConservativeRasterSupported, pDevice->ToData()->supportedFeatures.GetBit(
                                                       NvnDeviceFeature_SupportConservativeRaster));
    flags.SetBit(Flag_Shared, false);

    state = State_Initialized;
}

void CommandBufferImpl<ApiVariationNvn8>::Finalize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice) {
    if (hNvnCommandBuffer != 0) {
        nvnDeviceFinalizeCommandHandle(pNnDevice->ToData()->pNvnDevice, hNvnCommandBuffer);
        hNvnCommandBuffer = 0;
    }

    nvnCommandBufferFinalize(pNvnCommandBuffer);
    state = State_NotInitialized;
}

void CommandBufferImpl<ApiVariationNvn8>::AddCommandMemory(MemoryPoolImpl<ApiVariationNvn8>* pool,
                                                           ptrdiff_t ptr, size_t size) {
    nvnCommandBufferAddCommandMemory(pNvnCommandBuffer, pool->ToData()->pNvnMemoryPool, ptr, size);
}

void CommandBufferImpl<ApiVariationNvn8>::AddControlMemory(void* ptr, size_t size) {
    nvnCommandBufferAddControlMemory(pNvnCommandBuffer, ptr, size);
}

void CommandBufferImpl<ApiVariationNvn8>::SetOutOfCommandMemoryEventCallback(
    OutOfMemoryEventCallback callback) {
    pOutOfCommandMemoryCallback = reinterpret_cast<void (*)()>(callback);
}

void CommandBufferImpl<ApiVariationNvn8>::SetOutOfControlMemoryEventCallback(
    OutOfMemoryEventCallback callback) {
    pOutOfControlMemoryCallback = reinterpret_cast<void (*)()>(callback);
}

void CommandBufferImpl<ApiVariationNvn8>::Reset() {}

void CommandBufferImpl<ApiVariationNvn8>::Begin() {
    if (hNvnCommandBuffer != 0) {
        nvnDeviceFinalizeCommandHandle(pNnDevice->ToData()->pNvnDevice, hNvnCommandBuffer);
        hNvnCommandBuffer = 0;
    }

    nvnCommandBufferBeginRecording(pNvnCommandBuffer);
    state = State_Begun;
}

void CommandBufferImpl<ApiVariationNvn8>::End() {
    hNvnCommandBuffer = nvnCommandBufferEndRecording(pNvnCommandBuffer);
    state = State_Initialized;
}

void CommandBufferImpl<ApiVariationNvn8>::Dispatch(int a, int b, int c) {
    nvnCommandBufferDispatchCompute(pNvnCommandBuffer, a, b, c);
}

void CommandBufferImpl<ApiVariationNvn8>::Draw(PrimitiveTopology primitiveTopology, int vertexCount,
                                               int vertexOffset) {
    nvnCommandBufferDrawArrays(pNvnCommandBuffer, Nvn::GetDrawPrimitive(primitiveTopology),
                               vertexOffset, vertexCount);
}

void CommandBufferImpl<ApiVariationNvn8>::Draw(PrimitiveTopology primitiveTopology,
                                               int vertexCountPerInstance, int vertexOffset,
                                               int instanceCount, int baseInstance) {
    nvnCommandBufferDrawArraysInstanced(pNvnCommandBuffer, Nvn::GetDrawPrimitive(primitiveTopology),
                                        vertexOffset, vertexCountPerInstance, baseInstance,
                                        instanceCount);
}

void CommandBufferImpl<ApiVariationNvn8>::DrawIndexed(PrimitiveTopology primitiveTopology,
                                                      IndexFormat indexFormat,
                                                      const GpuAddress& indexBufferAddress,
                                                      int indexCount, int baseVertex) {
    nvnCommandBufferDrawElementsBaseVertex(pNvnCommandBuffer,
                                           Nvn::GetDrawPrimitive(primitiveTopology),
                                           Nvn::GetIndexFormat(indexFormat), indexCount,
                                           Nvn::GetBufferAddress(indexBufferAddress), baseVertex);
}

void CommandBufferImpl<ApiVariationNvn8>::DrawIndexed(PrimitiveTopology primitiveTopology,
                                                      IndexFormat indexFormat,
                                                      const GpuAddress& indexBufferAddress,
                                                      int indexCountPerInstance, int baseVertex,
                                                      int instanceCount, int baseInstance) {
    nvnCommandBufferDrawElementsInstanced(
        pNvnCommandBuffer, Nvn::GetDrawPrimitive(primitiveTopology),
        Nvn::GetIndexFormat(indexFormat), indexCountPerInstance,
        Nvn::GetBufferAddress(indexBufferAddress), baseVertex, baseInstance, instanceCount);
}

void CommandBufferImpl<ApiVariationNvn8>::DispatchIndirect(const GpuAddress& addr) {
    nvnCommandBufferDispatchComputeIndirect(pNvnCommandBuffer, Nvn::GetBufferAddress(addr));
}

void CommandBufferImpl<ApiVariationNvn8>::DrawIndirect(PrimitiveTopology top,
                                                       const GpuAddress& addr) {
    nvnCommandBufferDrawArraysIndirect(pNvnCommandBuffer, Nvn::GetDrawPrimitive(top),
                                       Nvn::GetBufferAddress(addr));
}

void CommandBufferImpl<ApiVariationNvn8>::DrawIndexedIndirect(PrimitiveTopology top,
                                                              IndexFormat index,
                                                              const GpuAddress& addr1,
                                                              const GpuAddress& addr2) {
    nvnCommandBufferDrawElementsIndirect(pNvnCommandBuffer, Nvn::GetDrawPrimitive(top),
                                         Nvn::GetIndexFormat(index), Nvn::GetBufferAddress(addr1),
                                         Nvn::GetBufferAddress(addr2));
}

void CommandBufferImpl<ApiVariationNvn8>::SetPipeline(const PipelineImpl<ApiVariationNvn8>* pPipe) {
    const PipelineImplData<ApiVariationNvn8>& pipe = pPipe->ToData();

    if (pipe.nnPipelineType == pipe.PipelineType_Graphics) {
        SetRasterizerState(nn::gfx::DataToAccessor(pipe.nnRasterizerState));
        SetBlendState(nn::gfx::DataToAccessor(pipe.nnBlendState));
        SetDepthStencilState(nn::gfx::DataToAccessor(pipe.nnDepthStencilState));
        SetVertexState(nn::gfx::DataToAccessor(pipe.nnVertexState));

        if (pipe.flags.GetBit(pipe.Flag_HasTessellationState)) {
            SetTessellationState(nn::gfx::DataToAccessor(pipe.nnTessellationState));
        }
    }

    SetShader(pipe.pShader, ShaderStageBit_All);
}

void CommandBufferImpl<ApiVariationNvn8>::SetRasterizerState(
    const RasterizerStateImpl<ApiVariationNvn8>* pRast) {
    const RasterizerStateImplData<ApiVariationNvn8>& rast = pRast->ToData();

    nvnCommandBufferBindPolygonState(
        pNvnCommandBuffer, reinterpret_cast<const NVNpolygonState*>(&rast.nvnPolygonState));
    nvnCommandBufferSetPolygonOffsetClamp(pNvnCommandBuffer, rast.nvnSlopeScaledDepthBias,
                                          rast.nvnDepthBias, rast.nvnDepthBiasClamp);
    nvnCommandBufferBindMultisampleState(
        pNvnCommandBuffer, reinterpret_cast<const NVNmultisampleState*>(&rast.nvnMultisampleState));

    if (rast.flags.GetBit(rast.Flag_MultisampleEnabled)) {
        nvnCommandBufferSetSampleMask(pNvnCommandBuffer, rast.nvnSampleMask);
    }

    nvnCommandBufferSetDepthClamp(pNvnCommandBuffer,
                                  !rast.flags.GetBit(rast.Flag_DepthClipEnabled));
    nvnCommandBufferSetRasterizerDiscard(pNvnCommandBuffer,
                                         !rast.flags.GetBit(rast.Flag_RasterEnabled));

    if (flags.GetBit(Flag_ConservativeRasterSupported)) {
        nvnCommandBufferSetConservativeRasterEnable(
            pNvnCommandBuffer, rast.flags.GetBit(rast.Flag_ConservativeRasterEnabled));
    }
}

void CommandBufferImpl<ApiVariationNvn8>::SetBlendState(
    const BlendStateImpl<ApiVariationNvn8>* pBlendState) {
    const BlendStateImplData<ApiVariationNvn8>& blendState = pBlendState->ToData();
    const NVNblendState* pBlendStates = blendState.pNvnBlendStateData;

    for (int i = 0, targetCount = blendState.targetCount; i < targetCount; ++i) {
        nvnCommandBufferBindBlendState(pNvnCommandBuffer, pBlendStates + i);
    }

    nvnCommandBufferBindChannelMaskState(
        pNvnCommandBuffer,
        reinterpret_cast<const NVNchannelMaskState*>(&blendState.nvnChannelMaskState));
    nvnCommandBufferBindColorState(
        pNvnCommandBuffer, reinterpret_cast<const NVNcolorState*>(&blendState.nvnColorState));
    nvnCommandBufferSetBlendColor(pNvnCommandBuffer, blendState.nvnBlendConstant);
}

void CommandBufferImpl<ApiVariationNvn8>::SetDepthStencilState(
    const DepthStencilStateImpl<ApiVariationNvn8>* pDepth) {
    const DepthStencilStateImplData<ApiVariationNvn8>& depth = pDepth->ToData();

    nvnCommandBufferBindDepthStencilState(
        pNvnCommandBuffer,
        reinterpret_cast<const NVNdepthStencilState*>(depth.nvnDepthStencilState));
    nvnCommandBufferSetStencilValueMask(pNvnCommandBuffer, NVN_FACE_FRONT_AND_BACK,
                                        depth.nvnStencilValueMask);
    nvnCommandBufferSetStencilMask(pNvnCommandBuffer, NVN_FACE_FRONT_AND_BACK,
                                   depth.nvnStencilMask);
    nvnCommandBufferSetStencilRef(pNvnCommandBuffer, NVN_FACE_BACK, depth.nvnStencilBackRef);
    nvnCommandBufferSetStencilRef(pNvnCommandBuffer, NVN_FACE_FRONT, depth.nvnStencilFrontRef);

    if (!depth.flag.GetBit(depth.Flag_DepthBoundsTestEnable))
        nvnCommandBufferSetDepthBounds(pNvnCommandBuffer, false, 0.0f, 1.0f);
}

void CommandBufferImpl<ApiVariationNvn8>::SetVertexState(
    const VertexStateImpl<ApiVariationNvn8>* pVert) {
    const VertexStateImplData<ApiVariationNvn8>& vert = pVert->ToData();

    nvnCommandBufferBindVertexAttribState(pNvnCommandBuffer, vert.vertexAttributeStateCount,
                                          vert.pNvnVertexAttribState);
    nvnCommandBufferBindVertexStreamState(pNvnCommandBuffer, vert.vertexStreamStateCount,
                                          vert.pNvnVertexStreamState);
}

void CommandBufferImpl<ApiVariationNvn8>::SetTessellationState(
    const TessellationStateImpl<ApiVariationNvn8>* pTess) {
    const TessellationStateImplData<ApiVariationNvn8>& tess = pTess->ToData();

    nvnCommandBufferSetPatchSize(pNvnCommandBuffer, tess.patchSize);
}

void CommandBufferImpl<ApiVariationNvn8>::SetShader(const ShaderImpl<ApiVariationNvn8>* pShader,
                                                    int stageBits) {
    NVNprogram* pProgram = nullptr;
    int shaderStageBits = 0;

    if (pShader) {
        pProgram = pShader->ToData()->pNvnProgram;
    }

    if (pShader && !pShader->ToData()->flags.GetBit(pShader->ToData()->Flag_SeparationEnable)) {
        shaderStageBits = pShader->ToData()->nvnShaderStageBits;
    } else {
        shaderStageBits = Nvn::GetShaderStageBits(stageBits);
    }

    nvnCommandBufferBindProgram(pNvnCommandBuffer, pProgram, shaderStageBits);
}

void CommandBufferImpl<ApiVariationNvn8>::SetRenderTargets(
    int colorTargetCount, const ColorTargetViewImpl<ApiVariationNvn8>* const* ppColorTargets,
    const DepthStencilViewImpl<ApiVariationNvn8>* pDepthStencil) {
    const int MaxRenderTarget = 8;

    NVNtexture* pNvnColorTargets[MaxRenderTarget];
    NVNtextureView* pNvnColorTargetViews[MaxRenderTarget];

    for (int idxTarget = 0; idxTarget < colorTargetCount; ++idxTarget) {
        pNvnColorTargets[idxTarget] = ppColorTargets[idxTarget]->ToData()->pNvnTexture;
        pNvnColorTargetViews[idxTarget] = ppColorTargets[idxTarget]->ToData()->pNvnTextureView;
    }

    NVNtexture* pDepthTarget = nullptr;
    NVNtextureView* pDepthTargetView = nullptr;

    if (pDepthStencil) {
        pDepthTarget = pDepthStencil->ToData()->pNvnTexture;
        pDepthTargetView = pDepthStencil->ToData()->pNvnTextureView;
    }

    nvnCommandBufferSetRenderTargets(pNvnCommandBuffer, colorTargetCount, pNvnColorTargets,
                                     pNvnColorTargetViews, pDepthTarget, pDepthTargetView);
}

void CommandBufferImpl<ApiVariationNvn8>::SetVertexBuffer(int bufferIndex,
                                                          const GpuAddress& vertexBuffer,
                                                          [[maybe_unused]] ptrdiff_t stride,
                                                          size_t size) {
    nvnCommandBufferBindVertexBuffer(pNvnCommandBuffer, bufferIndex,
                                     Nvn::GetBufferAddress(vertexBuffer), size);
}

void CommandBufferImpl<ApiVariationNvn8>::SetViewportScissorState(
    const ViewportScissorStateImpl<ApiVariationNvn8>* pView) {
    const ViewportScissorStateImplData<ApiVariationNvn8>& view = pView->ToData();

    nvnCommandBufferSetDepthRange(pNvnCommandBuffer, view.depthRange[0], view.depthRange[1]);
    nvnCommandBufferSetViewports(pNvnCommandBuffer, 0, 1, view.viewport);
    nvnCommandBufferSetScissors(pNvnCommandBuffer, 0, 1, view.scissor);

    int viewportCount = view.viewportCount;
    if (viewportCount > 1) {
        int extraViewportCount = viewportCount - 1;

        nn::util::BytePtr ptr(view.pWorkMemory.ptr);

        auto* viewportArray = ptr.Get<float>();
        auto* depthRangeArray = ptr.Advance(16 * extraViewportCount).Get<float>();
        auto* scissorArray = ptr.Advance(8 * extraViewportCount).Get<int32_t>();

        nvnCommandBufferSetViewports(pNvnCommandBuffer, 1, extraViewportCount, viewportArray);
        nvnCommandBufferSetDepthRanges(pNvnCommandBuffer, 1, extraViewportCount, depthRangeArray);
        nvnCommandBufferSetScissors(pNvnCommandBuffer, 1, extraViewportCount, scissorArray);
    }
}

void CommandBufferImpl<ApiVariationNvn8>::CopyBuffer(BufferImpl<ApiVariationNvn8>* pDstBuffer,
                                                     ptrdiff_t dstOffset,
                                                     const BufferImpl<ApiVariationNvn8>* pSrcBuffer,
                                                     ptrdiff_t srcOffset, size_t size) {
    NVNbufferAddress src = nvnBufferGetAddress(pSrcBuffer->ToData()->pNvnBuffer) + srcOffset;
    NVNbufferAddress dst = nvnBufferGetAddress(pDstBuffer->ToData()->pNvnBuffer) + dstOffset;
    nvnCommandBufferCopyBufferToBuffer(pNvnCommandBuffer, src, dst, size, NVN_COPY_FLAGS_NONE);
}

void CommandBufferImpl<ApiVariationNvn8>::CopyImage(
    TextureImpl<ApiVariationNvn8>* pDstTexture, const TextureSubresource& dstSubresource,
    int dstOffsetU, int dstOffsetV, int dstOffsetW,
    const TextureImpl<ApiVariationNvn8>* pSrcTexture, const TextureCopyRegion& srcCopyRegion) {
    NVNtextureTarget target = nvnTextureGetTarget(pSrcTexture->ToData()->pNvnTexture);

    int srcV;
    int srcHeight;
    int srcW;
    int srcDepth;
    GetNvnCopyRegion(&srcV, &srcHeight, &srcW, &srcDepth, srcCopyRegion, target);

    NVNcopyRegion srcRegion;
    srcRegion.xoffset = srcCopyRegion.GetOffsetU();
    srcRegion.yoffset = srcV;
    srcRegion.zoffset = srcW;
    srcRegion.width = srcCopyRegion.GetWidth();
    srcRegion.height = srcHeight;
    srcRegion.depth = srcDepth;

    NVNcopyRegion dstRegion;
    dstRegion.xoffset = dstOffsetU;
    dstRegion.yoffset =
        (target == NVN_TEXTURE_TARGET_1D_ARRAY) ? dstSubresource.GetArrayIndex() : dstOffsetV;
    dstRegion.zoffset = (target == NVN_TEXTURE_TARGET_2D_ARRAY ||
                         target == NVN_TEXTURE_TARGET_2D_MULTISAMPLE_ARRAY) ?
                            dstSubresource.GetArrayIndex() :
                            dstOffsetW;
    dstRegion.width = srcRegion.width;
    dstRegion.height = srcRegion.height;
    dstRegion.depth = srcRegion.depth;

    NVNtextureView srcView;
    nvnTextureViewSetDefaults(&srcView);
    nvnTextureViewSetLevels(&srcView, srcCopyRegion.GetSubresource().GetMipLevel(), 1);

    NVNtextureView dstView;
    nvnTextureViewSetDefaults(&dstView);
    nvnTextureViewSetLevels(&dstView, dstSubresource.GetMipLevel(), 1);

    nvnCommandBufferCopyTextureToTexture(pNvnCommandBuffer, pSrcTexture->ToData()->pNvnTexture,
                                         &srcView, &srcRegion, pDstTexture->ToData()->pNvnTexture,
                                         &dstView, &dstRegion, NVN_COPY_FLAGS_NONE);
}

void CommandBufferImpl<ApiVariationNvn8>::CopyBufferToImage(
    TextureImpl<ApiVariationNvn8>* pDstTexture, const BufferImpl<ApiVariationNvn8>* pSrcBuffer,
    const BufferTextureCopyRegion& copyRegion) {
    NVNtextureTarget target = nvnTextureGetTarget(pDstTexture->ToData()->pNvnTexture);

    const TextureCopyRegion& dstRegion = copyRegion.GetTextureCopyRegion();

    int offsetY;
    int height;
    int offsetZ;
    int depth;
    GetNvnCopyRegion(&offsetY, &height, &offsetZ, &depth, dstRegion, target);

    NVNcopyRegion region;
    region.xoffset = copyRegion.GetTextureCopyRegion().GetOffsetU();
    region.yoffset = offsetY;
    region.zoffset = offsetZ;
    region.width = copyRegion.GetTextureCopyRegion().GetWidth();
    region.height = height;
    region.depth = depth;

    NVNtextureView view;
    nvnTextureViewSetDefaults(&view);
    nvnTextureViewSetLevels(&view, copyRegion.GetTextureCopyRegion().GetSubresource().GetMipLevel(),
                            1);

    NVNbufferAddress bufferAddress =
        nvnBufferGetAddress(pSrcBuffer->ToData()->pNvnBuffer) + copyRegion.GetBufferOffset();

    ptrdiff_t rowStride;
    ptrdiff_t imageStride;
    GetNvnCopyStride(&rowStride, &imageStride, copyRegion, pDstTexture->ToData()->pNvnTexture);

    nvnCommandBufferSetCopyRowStride(pNvnCommandBuffer, rowStride);
    nvnCommandBufferSetCopyImageStride(pNvnCommandBuffer, imageStride);
    nvnCommandBufferCopyBufferToTexture(pNvnCommandBuffer, bufferAddress,
                                        pDstTexture->ToData()->pNvnTexture, &view, &region,
                                        NVN_COPY_FLAGS_NONE);
}

void CommandBufferImpl<ApiVariationNvn8>::CopyImageToBuffer(
    BufferImpl<ApiVariationNvn8>* pDstBuffer, const TextureImpl<ApiVariationNvn8>* pSrcTexture,
    const BufferTextureCopyRegion& copyRegion) {
    NVNtextureTarget target = nvnTextureGetTarget(pSrcTexture->ToData()->pNvnTexture);

    const TextureCopyRegion& srcRegion = copyRegion.GetTextureCopyRegion();

    int offsetY;
    int height;
    int offsetZ;
    int depth;
    GetNvnCopyRegion(&offsetY, &height, &offsetZ, &depth, srcRegion, target);

    NVNcopyRegion region;
    region.xoffset = srcRegion.GetOffsetU();
    region.yoffset = offsetY;
    region.zoffset = offsetZ;
    region.width = srcRegion.GetWidth();
    region.height = height;
    region.depth = depth;

    NVNtextureView view;
    nvnTextureViewSetDefaults(&view);
    nvnTextureViewSetLevels(&view, srcRegion.GetSubresource().GetMipLevel(), 1);

    NVNbufferAddress bufferAddress =
        nvnBufferGetAddress(pDstBuffer->ToData()->pNvnBuffer) + copyRegion.GetBufferOffset();

    ptrdiff_t rowStride;
    ptrdiff_t imageStride;
    GetNvnCopyStride(&rowStride, &imageStride, copyRegion, pSrcTexture->ToData()->pNvnTexture);

    nvnCommandBufferSetCopyRowStride(pNvnCommandBuffer, rowStride);
    nvnCommandBufferSetCopyImageStride(pNvnCommandBuffer, imageStride);
    nvnCommandBufferCopyTextureToBuffer(pNvnCommandBuffer, pSrcTexture->ToData()->pNvnTexture,
                                        &view, &region, bufferAddress, NVN_COPY_FLAGS_NONE);
}

void CommandBufferImpl<ApiVariationNvn8>::CopyBufferToImage(
    TextureImpl<ApiVariationNvn8>* pDstTexture, const TextureCopyRegion& dstRegion,
    const BufferImpl<ApiVariationNvn8>* pSrcBuffer, ptrdiff_t srcOffset) {
    NVNtextureTarget target = nvnTextureGetTarget(pDstTexture->ToData()->pNvnTexture);

    int offsetY;
    int height;
    int offsetZ;
    int depth;
    GetNvnCopyRegion(&offsetY, &height, &offsetZ, &depth, dstRegion, target);

    NVNcopyRegion region;
    region.xoffset = dstRegion.GetOffsetU();
    region.yoffset = offsetY;
    region.zoffset = offsetZ;
    region.width = dstRegion.GetWidth();
    region.height = height;
    region.depth = depth;

    NVNtextureView view;
    nvnTextureViewSetDefaults(&view);
    nvnTextureViewSetLevels(&view, dstRegion.GetSubresource().GetMipLevel(), 1);

    NVNbufferAddress bufferAddress =
        nvnBufferGetAddress(pSrcBuffer->ToData()->pNvnBuffer) + srcOffset;

    nvnCommandBufferSetCopyRowStride(pNvnCommandBuffer, 0);
    nvnCommandBufferSetCopyImageStride(pNvnCommandBuffer, 0);
    nvnCommandBufferCopyBufferToTexture(pNvnCommandBuffer, bufferAddress,
                                        pDstTexture->ToData()->pNvnTexture, &view, &region,
                                        NVN_COPY_FLAGS_NONE);
}

void CommandBufferImpl<ApiVariationNvn8>::CopyImageToBuffer(
    BufferImpl<ApiVariationNvn8>* pDstBuffer, ptrdiff_t dstOffset,
    const TextureImpl<ApiVariationNvn8>* pSrcTexture, const TextureCopyRegion& srcRegion) {
    NVNtextureTarget target = nvnTextureGetTarget(pSrcTexture->ToData()->pNvnTexture);

    int offsetY;
    int height;
    int offsetZ;
    int depth;
    GetNvnCopyRegion(&offsetY, &height, &offsetZ, &depth, srcRegion, target);

    NVNcopyRegion region;
    region.xoffset = srcRegion.GetOffsetU();
    region.yoffset = offsetY;
    region.zoffset = offsetZ;
    region.width = srcRegion.GetWidth();
    region.height = height;
    region.depth = depth;

    NVNtextureView view;
    nvnTextureViewSetDefaults(&view);
    nvnTextureViewSetLevels(&view, srcRegion.GetSubresource().GetMipLevel(), 1);

    NVNbufferAddress bufferAddress =
        nvnBufferGetAddress(pDstBuffer->ToData()->pNvnBuffer) + dstOffset;

    nvnCommandBufferSetCopyRowStride(pNvnCommandBuffer, 0);
    nvnCommandBufferSetCopyImageStride(pNvnCommandBuffer, 0);
    nvnCommandBufferCopyTextureToBuffer(pNvnCommandBuffer, pSrcTexture->ToData()->pNvnTexture,
                                        &view, &region, bufferAddress, NVN_COPY_FLAGS_NONE);
}

void CommandBufferImpl<ApiVariationNvn8>::BlitImage(
    TextureImpl<ApiVariationNvn8>* pDstTexture, const TextureCopyRegion& dstCopyRegion,
    const TextureImpl<ApiVariationNvn8>* pSrcTexture, const TextureCopyRegion& srcCopyRegion,
    int copyFlags) {
    NVNtextureTarget dstTarget = nvnTextureGetTarget(pDstTexture->ToData()->pNvnTexture);

    int dstV;
    int dstHeight;
    int dstW;
    int dstDepth;
    GetNvnCopyRegion(&dstV, &dstHeight, &dstW, &dstDepth, dstCopyRegion, dstTarget);

    NVNtextureTarget srcTarget = nvnTextureGetTarget(pSrcTexture->ToData()->pNvnTexture);

    int srcV;
    int srcHeight;
    int srcW;
    int srcDepth;
    GetNvnCopyRegion(&srcV, &srcHeight, &srcW, &srcDepth, srcCopyRegion, srcTarget);

    NVNcopyRegion dstRegion;
    dstRegion.xoffset = dstCopyRegion.GetOffsetU();
    dstRegion.yoffset = dstV;
    dstRegion.zoffset = dstW;
    dstRegion.width = dstCopyRegion.GetWidth();
    dstRegion.height = dstHeight;
    dstRegion.depth = dstDepth;

    NVNcopyRegion srcRegion;
    srcRegion.xoffset = srcCopyRegion.GetOffsetU();
    srcRegion.yoffset = srcV;
    srcRegion.zoffset = srcW;
    srcRegion.width = srcCopyRegion.GetWidth();
    srcRegion.height = srcHeight;
    srcRegion.depth = srcDepth;

    NVNtextureView dstView;
    nvnTextureViewSetDefaults(&dstView);
    nvnTextureViewSetLevels(&dstView, dstCopyRegion.GetSubresource().GetMipLevel(), 1);

    NVNtextureView srcView;
    nvnTextureViewSetDefaults(&srcView);
    nvnTextureViewSetLevels(&srcView, srcCopyRegion.GetSubresource().GetMipLevel(), 1);

    int nvnCopyFlags = 0;
    nvnCopyFlags |= copyFlags & 1;  // todo: figure out this conversion?
    nvnCommandBufferCopyTextureToTexture(pNvnCommandBuffer, pSrcTexture->ToData()->pNvnTexture,
                                         &srcView, &srcRegion, pDstTexture->ToData()->pNvnTexture,
                                         &dstView, &dstRegion, nvnCopyFlags);
}

void CommandBufferImpl<ApiVariationNvn8>::ClearBuffer(BufferImpl<ApiVariationNvn8>* pBuffer,
                                                      ptrdiff_t offset, size_t size,
                                                      uint32_t value) {
    NVNbufferAddress bufferAddress = nvnBufferGetAddress(pBuffer->ToData()->pNvnBuffer) + offset;
    nvnCommandBufferClearBuffer(pNvnCommandBuffer, bufferAddress, size, value);
}

void CommandBufferImpl<ApiVariationNvn8>::ClearColor(
    ColorTargetViewImpl<ApiVariationNvn8>* pColorTarget, float r, float g, float b, float a,
    const TextureArrayRange* pArrayRange) {
    ClearColorValue clearColor{{r, g, b, a}};
    ClearColorTarget(pColorTarget, clearColor, pArrayRange);
}

void CommandBufferImpl<ApiVariationNvn8>::ClearColorTarget(
    ColorTargetViewImpl<ApiVariationNvn8>* pColorTarget, const ClearColorValue& clearColor,
    const TextureArrayRange* pArrayRange) {
    const NVNtexture* const pNvnTexture = pColorTarget->ToData()->pNvnTexture;
    const NVNtextureView* const pNvnTextureView = pColorTarget->ToData()->pNvnTextureView;

    NVNcopyRegion region{};

    int level;
    NVNtextureTarget target;

    if (pNvnTextureView) {
        int levelCount;
        NVNboolean result;

        result = nvnTextureViewGetLevels(pNvnTextureView, &level, &levelCount);
        result = nvnTextureViewGetTarget(pNvnTextureView, &target);
    } else {
        level = 0;
        target = nvnTextureGetTarget(pNvnTexture);
    }

    region.width = nvnTextureGetWidth(pNvnTexture);
    region.height = nvnTextureGetHeight(pNvnTexture);
    region.depth = nvnTextureGetDepth(pNvnTexture);

    region.width = std::max(region.width >> level, 1);
    if (target != NVN_TEXTURE_TARGET_1D && target != NVN_TEXTURE_TARGET_1D_ARRAY) {
        region.height = std::max(region.height >> level, 1);
        if (target == NVN_TEXTURE_TARGET_3D) {
            region.depth = std::max(region.depth >> level, 1);
        }
    }

    if (pArrayRange) {
        if (target == NVN_TEXTURE_TARGET_1D_ARRAY) {
            region.yoffset = pArrayRange->GetBaseArrayIndex();
            region.height = pArrayRange->GetArrayLength();
        } else if (target == NVN_TEXTURE_TARGET_2D_ARRAY ||
                   target == NVN_TEXTURE_TARGET_2D_MULTISAMPLE_ARRAY) {
            region.zoffset = pArrayRange->GetBaseArrayIndex();
            region.depth = pArrayRange->GetArrayLength();
        }
    }

    nvnCommandBufferClearTexture(pNvnCommandBuffer, pNvnTexture, pNvnTextureView, &region,
                                 clearColor.valueFloat, NVN_CLEAR_COLOR_MASK_RGBA);
}

void CommandBufferImpl<ApiVariationNvn8>::ClearDepthStencil(
    DepthStencilViewImpl<ApiVariationNvn8>* pDepthStencil, float depth, int stencil,
    DepthStencilClearMode clearMode, [[maybe_unused]] const TextureArrayRange* pArrayRange) {
    const NVNtexture* const pNvnTexture = pDepthStencil->ToData()->pNvnTexture;
    const NVNtextureView* const pNvnTextureView = pDepthStencil->ToData()->pNvnTextureView;

    nvnCommandBufferSetScissor(pNvnCommandBuffer, 0, 0, 0x7FFFFFFF, 0x7FFFFFFF);
    nvnCommandBufferSetRenderTargets(pNvnCommandBuffer, 0, nullptr, nullptr, pNvnTexture,
                                     pNvnTextureView);
    switch (clearMode) {
    case DepthStencilClearMode_Depth:
        nvnCommandBufferClearDepthStencil(pNvnCommandBuffer, depth, true, stencil, 0);
        break;
    case DepthStencilClearMode_Stencil:
        nvnCommandBufferClearDepthStencil(pNvnCommandBuffer, depth, false, stencil, -1);
        break;
    case DepthStencilClearMode_DepthStencil:
        nvnCommandBufferClearDepthStencil(pNvnCommandBuffer, depth, true, stencil, -1);
        break;

    default:
        NN_UNEXPECTED_DEFAULT;
        break;
    }
}

void CommandBufferImpl<ApiVariationNvn8>::Resolve(
    TextureImpl<ApiVariationNvn8>* pDstTexture, [[maybe_unused]] int dstMipLevel,
    [[maybe_unused]] int dstStartArrayIndex,
    const ColorTargetViewImpl<ApiVariationNvn8>* pSrcColorTarget,
    [[maybe_unused]] const TextureArrayRange* pSrcArrayRange) {
    const NVNtexture* pSrcNvnTexture = pSrcColorTarget->ToData()->pNvnTexture;

    nvnCommandBufferDownsample(pNvnCommandBuffer, pSrcNvnTexture,
                               pDstTexture->ToData()->pNvnTexture);
}

void CommandBufferImpl<ApiVariationNvn8>::FlushMemory(int gpuAccessFlags) {
    int barrier = 0;  // const value of 1 in dwarf
    barrier |= (gpuAccessFlags & (GpuAccess_Image | GpuAccess_QueryBuffer | GpuAccess_DepthStencil |
                                  GpuAccess_ColorBuffer | GpuAccess_UnorderedAccessBuffer)) ?
                   NVN_BARRIER_ORDER_PRIMITIVES_BIT :
                   0;
    if (barrier) {
        nvnCommandBufferBarrier(pNvnCommandBuffer, barrier);
    }
}

void CommandBufferImpl<ApiVariationNvn8>::InvalidateMemory(int gpuAccessFlags) {
    int barrier = 0;

    barrier |=
        (gpuAccessFlags & (GpuAccess_IndirectBuffer)) ? NVN_BARRIER_ORDER_INDIRECT_DATA_BIT : 0;

    barrier |= (gpuAccessFlags & (GpuAccess_Image | GpuAccess_Texture)) ?
                   NVN_BARRIER_INVALIDATE_TEXTURE_BIT :
                   0;

    barrier |= (gpuAccessFlags & (GpuAccess_ShaderCode | GpuAccess_UnorderedAccessBuffer |
                                  GpuAccess_ConstantBuffer)) ?
                   NVN_BARRIER_INVALIDATE_SHADER_BIT :
                   0;

    barrier |= (gpuAccessFlags & (GpuAccess_Descriptor)) ?
                   NVN_BARRIER_INVALIDATE_TEXTURE_DESCRIPTOR_BIT :
                   0;

    if (barrier) {
        nvnCommandBufferBarrier(pNvnCommandBuffer, barrier);
    }
}

void CommandBufferImpl<ApiVariationNvn8>::CallCommandBuffer(
    const CommandBufferImpl<ApiVariationNvn8>* pNestedCommandBuffer) {
    NVNcommandHandle nvnCommandHandle = pNestedCommandBuffer->ToData()->hNvnCommandBuffer;

    nvnCommandBufferCallCommands(pNvnCommandBuffer, 1, &nvnCommandHandle);
}

void CommandBufferImpl<ApiVariationNvn8>::CopyCommandBuffer(
    const CommandBufferImpl<ApiVariationNvn8>* pNestedCommandBuffer) {
    NVNcommandHandle nvnCommandHandle = pNestedCommandBuffer->ToData()->hNvnCommandBuffer;

    nvnCommandBufferCopyCommands(pNvnCommandBuffer, 1, &nvnCommandHandle);
}

void CommandBufferImpl<ApiVariationNvn8>::SetBufferStateTransition(
    BufferImpl<ApiVariationNvn8>*, int oldState, [[maybe_unused]] int oldStageBits, int newState,
    int newStageBits) {
    int barrier = 0;

    if ((oldState & (BufferState_QueryBuffer | BufferState_UnorderedAccessBuffer)) ||
        (newState & (BufferState_QueryBuffer | BufferState_UnorderedAccessBuffer))) {
        barrier |=
            (newStageBits & (PipelineStageBit_ComputeShader | PipelineStageBit_GeometryShader |
                             PipelineStageBit_DomainShader | PipelineStageBit_HullShader |
                             PipelineStageBit_VertexShader | PipelineStageBit_VertexInput)) ?
                NVN_BARRIER_ORDER_PRIMITIVES_BIT :
                0;

        barrier |= (newStageBits & (PipelineStageBit_RenderTarget | PipelineStageBit_PixelShader)) ?
                       NVN_BARRIER_ORDER_FRAGMENTS_BIT :
                       0;

        barrier |=
            (newState & BufferState_IndirectArgument) ? NVN_BARRIER_ORDER_INDIRECT_DATA_BIT : 0;
    }

    barrier |= (newState & (BufferState_UnorderedAccessBuffer | BufferState_ConstantBuffer)) ?
                   NVN_BARRIER_INVALIDATE_SHADER_BIT :
                   0;

    nvnCommandBufferBarrier(pNvnCommandBuffer, barrier);
}

void CommandBufferImpl<ApiVariationNvn8>::SetTextureStateTransition(
    TextureImpl<ApiVariationNvn8>*, const TextureSubresourceRange*, int oldState,
    [[maybe_unused]] int oldStageBits, int newState, int newStageBits) {
    int barrier = 0;

    if ((oldState &
         (TextureState_DepthWrite | TextureState_ColorTarget | TextureState_ShaderWrite)) ||
        (newState &
         (TextureState_DepthWrite | TextureState_ColorTarget | TextureState_ShaderWrite))) {
        barrier |=
            (newStageBits & (PipelineStageBit_ComputeShader | PipelineStageBit_GeometryShader |
                             PipelineStageBit_DomainShader | PipelineStageBit_HullShader |
                             PipelineStageBit_VertexShader | PipelineStageBit_VertexInput)) ?
                NVN_BARRIER_ORDER_PRIMITIVES_BIT :
                0;

        barrier |= (newStageBits & (PipelineStageBit_RenderTarget | PipelineStageBit_PixelShader)) ?
                       NVN_BARRIER_ORDER_FRAGMENTS_BIT :
                       0;

        barrier |= (newState & (TextureState_DepthWrite | TextureState_DepthRead)) ?
                       NVN_BARRIER_ORDER_PRIMITIVES_BIT :
                       0;
    }

    barrier |= (newState & (TextureState_ShaderRead)) ? NVN_BARRIER_INVALIDATE_TEXTURE_BIT : 0;

    nvnCommandBufferBarrier(pNvnCommandBuffer, barrier);
}

void CommandBufferImpl<ApiVariationNvn8>::SetDescriptorPool(
    const DescriptorPoolImpl<ApiVariationNvn8>* pDescriptorPool) {
    switch (pDescriptorPool->ToData()->descriptorPoolType) {
    case DescriptorPoolType_TextureView:
        nvnCommandBufferSetTexturePool(pNvnCommandBuffer,
                                       pDescriptorPool->ToData()->pDescriptorPool);
        break;
    case DescriptorPoolType_Sampler:
        nvnCommandBufferSetSamplerPool(pNvnCommandBuffer,
                                       pDescriptorPool->ToData()->pDescriptorPool);
        break;
    default:
        break;
    }
}

void CommandBufferImpl<ApiVariationNvn8>::SetRootSignature(
    [[maybe_unused]] PipelineType pipelineType,
    RootSignatureImpl<ApiVariationNvn8>* pRootSignature) {
    pGfxRootSignature = pRootSignature;
}

void CommandBufferImpl<ApiVariationNvn8>::SetRootBufferDescriptorTable(
    PipelineType pipelineType, int indexDescriptorTable,
    const DescriptorSlot& startBufferDescriptorSlot) {
    nn::gfx::detail::SetRootBufferDescriptorTable<ApiVariationNvn8>(
        this, pipelineType, indexDescriptorTable, startBufferDescriptorSlot,
        DescriptorPoolImpl<ApiVariationNvn8>::GetDescriptorSlotIncrementSize(
            pNnDevice, DescriptorPoolType_BufferView));
}

void CommandBufferImpl<ApiVariationNvn8>::SetRootTextureAndSamplerDescriptorTable(
    PipelineType pipelineType, int indexDescriptorTable,
    const DescriptorSlot& startTextureDescriptorSlot,
    const DescriptorSlot& startSamplerDescriptorSlot) {
    nn::gfx::detail::SetRootTextureAndSamplerDescriptorTable(
        this, pipelineType, indexDescriptorTable, startTextureDescriptorSlot,
        startSamplerDescriptorSlot,
        DescriptorPoolImpl<ApiVariationNvn8>::GetDescriptorSlotIncrementSize(
            pNnDevice, DescriptorPoolType_TextureView),
        DescriptorPoolImpl<ApiVariationNvn8>::GetDescriptorSlotIncrementSize(
            pNnDevice, DescriptorPoolType_Sampler));
}

void CommandBufferImpl<ApiVariationNvn8>::SetRootConstantBuffer(
    PipelineType pipelineType, int indexDynamicDescriptor, const GpuAddress& constantBufferAddress,
    size_t size) {
    nn::gfx::detail::SetRootConstantBuffer(this, pipelineType, indexDynamicDescriptor,
                                           constantBufferAddress, size);
}

void CommandBufferImpl<ApiVariationNvn8>::SetRootUnorderedAccessBuffer(
    PipelineType pipelineType, int indexDynamicDescriptor,
    const GpuAddress& unorderedAccessBufferAddress, size_t size) {
    nn::gfx::detail::SetRootUnorderedAccessBuffer(this, pipelineType, indexDynamicDescriptor,
                                                  unorderedAccessBufferAddress, size);
}

void CommandBufferImpl<ApiVariationNvn8>::SetRootTextureAndSampler(
    PipelineType pipelineType, int indexDynamicDescriptor,
    const TextureViewImpl<ApiVariationNvn8>* pTextureView,
    const SamplerImpl<ApiVariationNvn8>* pSampler) {
    nn::gfx::detail::SetRootTextureAndSampler(this, pipelineType, indexDynamicDescriptor,
                                              pTextureView, pSampler);
}

void CommandBufferImpl<ApiVariationNvn8>::BeginQuery(QueryTarget target) {
    if (target != QueryTarget_ComputeShaderInvocations) {
        NVNcounterType counterType = Nvn::GetCounterType(target);
        nvnCommandBufferResetCounter(pNvnCommandBuffer, counterType);
    }
}

void CommandBufferImpl<ApiVariationNvn8>::EndQuery(const GpuAddress& dstBufferAddress,
                                                   QueryTarget target) {
    if (target != QueryTarget_ComputeShaderInvocations) {
        NVNcounterType counterType = Nvn::GetCounterType(target);
        nvnCommandBufferReportCounter(pNvnCommandBuffer, counterType,
                                      Nvn::GetBufferAddress(dstBufferAddress));
    }
}

void CommandBufferImpl<ApiVariationNvn8>::WriteTimestamp(const GpuAddress& dstBufferAddress) {
    nvnCommandBufferReportCounter(pNvnCommandBuffer, NVN_COUNTER_TYPE_TIMESTAMP,
                                  Nvn::GetBufferAddress(dstBufferAddress));
}

void CommandBufferImpl<ApiVariationNvn8>::SetDepthBounds(float minDepthBounds,
                                                         float maxDepthBounds) {
    nvnCommandBufferSetDepthBounds(pNvnCommandBuffer, true, minDepthBounds, maxDepthBounds);
}

void CommandBufferImpl<ApiVariationNvn8>::SetLineWidth(float lineWidth) {
    nvnCommandBufferSetLineWidth(pNvnCommandBuffer, lineWidth);
}

void CommandBufferImpl<ApiVariationNvn8>::SetViewports(int firstViewport, int viewportCount,
                                                       const ViewportStateInfo* pViewports) {
    const int maxViewports = 16;

    float viewports[maxViewports * 4];
    float depthRanges[maxViewports * 2];
    float* pViewport = viewports;
    float* pDepthRange = depthRanges;

    for (int idxViewport = 0; idxViewport < viewportCount; ++idxViewport) {
        const ViewportStateInfo& viewport = pViewports[idxViewport];

        *pViewport++ = viewport.GetOriginX();
        *pViewport++ = viewport.GetOriginY();
        *pViewport++ = viewport.GetWidth();
        *pViewport++ = viewport.GetHeight();
        *pDepthRange++ = viewport.GetMinDepth();
        *pDepthRange++ = viewport.GetMaxDepth();
    }

    nvnCommandBufferSetViewports(pNvnCommandBuffer, firstViewport, viewportCount, viewports);
    nvnCommandBufferSetDepthRanges(pNvnCommandBuffer, firstViewport, viewportCount, depthRanges);
}

void CommandBufferImpl<ApiVariationNvn8>::SetScissors(int firstScissor, int scissorCount,
                                                      const ScissorStateInfo* pScissors) {
    const int maxScissors = 16;

    int scissors[maxScissors * 4];
    int* pScissor = scissors;

    for (int idxScissor = 0; idxScissor < scissorCount; ++idxScissor) {
        const ScissorStateInfo& scissor = pScissors[idxScissor];

        *pScissor++ = scissor.GetOriginX();
        *pScissor++ = scissor.GetOriginY();
        *pScissor++ = scissor.GetWidth();
        *pScissor++ = scissor.GetHeight();
    }

    nvnCommandBufferSetScissors(pNvnCommandBuffer, firstScissor, scissorCount, scissors);
}

void CommandBufferImpl<ApiVariationNvn8>::SetConstantBuffer(
    int slot, ShaderStage stage, const DescriptorSlot& constantBufferDescriptor) {
    nn::util::ConstBytePtr pDescriptor(ToPtr<void*>(constantBufferDescriptor));
    NVNbufferAddress address = *pDescriptor.Get<NVNbufferAddress>();
    size_t size = *pDescriptor.Advance(8).Get<size_t>();

    nvnCommandBufferBindUniformBuffer(pNvnCommandBuffer, Nvn::GetShaderStage(stage), slot, address,
                                      size);
}

void CommandBufferImpl<ApiVariationNvn8>::SetUnorderedAccessBuffer(
    int slot, ShaderStage stage, const DescriptorSlot& unorderedAccessBufferDescriptor) {
    nn::util::ConstBytePtr pDescriptor(ToPtr<void*>(unorderedAccessBufferDescriptor));
    NVNbufferAddress address = *pDescriptor.Get<NVNbufferAddress>();
    size_t size = *pDescriptor.Advance(8).Get<size_t>();

    nvnCommandBufferBindStorageBuffer(pNvnCommandBuffer, Nvn::GetShaderStage(stage), slot, address,
                                      size);
}

void CommandBufferImpl<ApiVariationNvn8>::SetTextureAndSampler(
    int slot, ShaderStage stage, const DescriptorSlot& textureDescriptor,
    const DescriptorSlot& samplerDescriptor) {
    detail::SetTextureAndSampler(this, stage, slot, textureDescriptor.ToData()->value,
                                 samplerDescriptor.ToData()->value);
}

void CommandBufferImpl<ApiVariationNvn8>::SetTexture(int slot, ShaderStage stage,
                                                     const DescriptorSlot& textureDescriptor) {
    NVNtextureHandle textureHandle = nvnDeviceGetTexelFetchHandle(
        pNnDevice->ToData()->pNvnDevice, textureDescriptor.ToData()->value);

    nvnCommandBufferBindTexture(pNvnCommandBuffer, Nvn::GetShaderStage(stage), slot, textureHandle);
}

void CommandBufferImpl<ApiVariationNvn8>::SetImage(int slot, ShaderStage stage,
                                                   const DescriptorSlot& imageDescriptor) {
    NVNtextureHandle imageHandle =
        nvnDeviceGetImageHandle(pNnDevice->ToData()->pNvnDevice, imageDescriptor.ToData()->value);

    nvnCommandBufferBindImage(pNvnCommandBuffer, Nvn::GetShaderStage(stage), slot, imageHandle);
}

void CommandBufferImpl<ApiVariationNvn8>::SetConstantBuffer(int slot, ShaderStage stage,
                                                            const GpuAddress& constantBufferAddress,
                                                            size_t size) {
    nvnCommandBufferBindUniformBuffer(pNvnCommandBuffer, Nvn::GetShaderStage(stage), slot,
                                      Nvn::GetBufferAddress(constantBufferAddress), size);
}

void CommandBufferImpl<ApiVariationNvn8>::SetUnorderedAccessBuffer(
    int slot, ShaderStage stage, const GpuAddress& unorderedAccessBufferAddress, size_t size) {
    nvnCommandBufferBindStorageBuffer(pNvnCommandBuffer, Nvn::GetShaderStage(stage), slot,
                                      Nvn::GetBufferAddress(unorderedAccessBufferAddress), size);
}

void CommandBufferImpl<ApiVariationNvn8>::SetTextureAndSampler(
    int, ShaderStage, const TextureViewImpl<ApiVariationNvn8>*,
    const SamplerImpl<ApiVariationNvn8>*) {}

void CommandBufferImpl<ApiVariationNvn8>::SetImage(int, ShaderStage,
                                                   const TextureViewImpl<ApiVariationNvn8>*) {}

}  // namespace nn::gfx::detail