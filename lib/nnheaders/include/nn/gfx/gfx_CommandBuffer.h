#pragma once

#include <nn/gfx/detail/gfx_CommandBuffer-api.nvn.8.h>
#include <nn/gfx/gfx_Common.h>

namespace nn::gfx {
class CommandBufferInfo;

template <class TTarget>
class TCommandBuffer : public detail::CommandBufferImpl<TTarget> {
    NN_NO_COPY(TCommandBuffer);

    typedef void (*OutOfMemoryEventCallback)(TCommandBuffer<TTarget>*, const OutOfMemoryEventArg&);

public:
    typedef CommandBufferInfo InfoType;

    TCommandBuffer() {}

    static size_t GetCommandMemoryAlignment(TDevice<TTarget>*);
    static size_t GetControlMemoryAlignment(TDevice<TTarget>*);
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
    void AddCommandMemory(TMemoryPool<TTarget>*, ptrdiff_t, size_t);
    void AddControlMemory(void*, size_t);
    void SetOutOfCommandMemoryEventCallback(OutOfMemoryEventCallback);
    void SetOutOfControlMemoryEventCallback(OutOfMemoryEventCallback);
    void Reset();
    void Begin();
    void End();
    void Dispatch(int, int, int);
    void Draw(PrimitiveTopology, int, int);
    void Draw(PrimitiveTopology, int, int, int, int);
    void DrawIndexed(PrimitiveTopology, IndexFormat, const GpuAddress&, int, int);
    void DrawIndexed(PrimitiveTopology, IndexFormat, const GpuAddress&, int, int, int, int);
    void DispatchIndirect(const GpuAddress&);
    void DrawIndirect(PrimitiveTopology, const GpuAddress&);
    void DrawIndexedIndirect(PrimitiveTopology, IndexFormat, const GpuAddress&, const GpuAddress&);
    void SetPipeline(const TPipeline<TTarget>*);
    void SetRenderTargets(int, const TColorTargetView<TTarget>* const*,
                          const TDepthStencilView<TTarget>*);
    void SetVertexBuffer(int, const GpuAddress&, ptrdiff_t, size_t);
    void SetViewportScissorState(const TViewportScissorState<TTarget>*);
    void CopyBuffer(TBuffer<TTarget>*, ptrdiff_t, const TBuffer<TTarget>*, ptrdiff_t, size_t);
    void CopyImage(TTexture<TTarget>*, const TextureSubresource&, int, int, int,
                   const TTexture<TTarget>*, const TextureCopyRegion&);
    void CopyBufferToImage(TTexture<TTarget>*, const TBuffer<TTarget>*,
                           const BufferTextureCopyRegion&);
    void CopyBufferToImage(TTexture<TTarget>*, const TextureCopyRegion&, const TBuffer<TTarget>*,
                           ptrdiff_t);
    void CopyImageToBuffer(TBuffer<TTarget>*, const TTexture<TTarget>*,
                           const BufferTextureCopyRegion&);
    void CopyImageToBuffer(TBuffer<TTarget>*, ptrdiff_t, const TTexture<TTarget>*,
                           const TextureCopyRegion&);
    void BlitImage(TTexture<TTarget>*, const TextureCopyRegion&, const TTexture<TTarget>*,
                   const TextureCopyRegion&, int);
    void ClearBuffer(TBuffer<TTarget>*, ptrdiff_t, size_t, uint32_t);
    void ClearColor(TColorTargetView<TTarget>*, float, float, float, float,
                    const TextureArrayRange*);
    void ClearColorTarget(TColorTargetView<TTarget>*, const ClearColorValue&,
                          const TextureArrayRange*);
    void ClearDepthStencil(TDepthStencilView<TTarget>*, float, int, DepthStencilClearMode,
                           const TextureArrayRange*);
    void Resolve(TTexture<TTarget>*, int, int, const TColorTargetView<TTarget>*,
                 const TextureArrayRange*);
    void FlushMemory(int);
    void InvalidateMemory(int);
    void CallCommandBuffer(const TCommandBuffer<TTarget>*);
    void CopyCommandBuffer(const TCommandBuffer<TTarget>*);
    void SetBufferStateTransition(TBuffer<TTarget>*, int, int, int, int);
    void SetTextureStateTransition(TTexture<TTarget>*, TextureSubresourceRange*, int, int, int,
                                   int);
    void SetDescriptorPool(const TDescriptorPool<TTarget>*);
    void SetRootSignature(PipelineType, TRootSignature<TTarget>*);
    void SetRootBufferDescriptorTable(PipelineType, int, const DescriptorSlot&);
    void SetRootTextureAndSamplerDescriptorTable(PipelineType, int, const DescriptorSlot&,
                                                 const DescriptorSlot&);
    void SetRootConstantBuffer(PipelineType, int, const GpuAddress&, size_t);
    void SetRootUnorderedAccessBuffer(PipelineType, int, const GpuAddress&, size_t);
    void SetRootTextureAndSampler(PipelineType, int, const TTextureView<TTarget>*,
                                  const TSampler<TTarget>*);
    void BeginQuery(QueryTarget);
    void EndQuery(const GpuAddress&, QueryTarget);
    void SetDepthBounds(float, float);
    void SetLineWidth(float);
    void SetViewports(int, int, const ViewportStateInfo*);
    void SetScissors(int, int, const ScissorStateInfo*);
    void WriteTimestamp(const GpuAddress&);
    void UpdateBuffer(const GpuAddress&, size_t, ptrdiff_t, size_t, const void*);
    void SetConstantBuffer(int, ShaderStage, const DescriptorSlot&);
    void SetConstantBuffer(int, ShaderStage, const GpuAddress&, size_t);
    void SetUnorderedAccessBuffer(int, ShaderStage, const DescriptorSlot&);
    void SetUnorderedAccessBuffer(int, ShaderStage, const GpuAddress&, size_t);
    void SetTextureAndSampler(int, ShaderStage, const DescriptorSlot&, const DescriptorSlot&);
    void SetTextureAndSampler(int, ShaderStage, const TTextureView<TTarget>*,
                              const TSampler<TTarget>*);
    void SetTexture(int, ShaderStage, const DescriptorSlot&);
    void SetImage(int, ShaderStage, const DescriptorSlot&);
    void SetImage(int, ShaderStage, const TTextureView<TTarget>*);
    void SetShader(const TShader<TTarget>*, int);
    void SetRasterizerState(const TRasterizerState<TTarget>*);
    void SetBlendState(const TBlendState<TTarget>*);
    void SetDepthStencilState(const TDepthStencilState<TTarget>*);
    void SetVertexState(const TVertexState<TTarget>*);
    void SetTessellationState(const TTessellationState<TTarget>*);
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;

    typedef void (*Gl4UserCommandCallbackType)(const void*);
    void Gl4SetUserCommand(Gl4UserCommandCallbackType, const void*);
    void Gl4SetUserCommandDynamic(Gl4UserCommandCallbackType, const void*, size_t);
};

}  // namespace nn::gfx