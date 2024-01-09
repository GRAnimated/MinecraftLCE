#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_CommandBufferData-api.nvn.8.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>

namespace nn::gfx {

class CommandBufferInfo;
class GpuAddress;
class TextureSubresource;
class TextureCopyRegion;
class BufferTextureCopyRegion;
class TextureArrayRange;
class TextureSubresourceRange;
class DescriptorSlot;
class ViewportStateInfo;
class ScissorStateInfo;

namespace detail {

template <>
class CommandBufferImpl<ApiVariationNvn8>
    : public DataContainer<CommandBufferImplData<ApiVariationNvn8>> {
    NN_NO_COPY(CommandBufferImpl);

public:
    typedef CommandBufferInfo InfoType;

    typedef void (*OutOfMemoryEventCallback)(TCommandBuffer<ApiVariationNvn8>*,
                                             const OutOfMemoryEventArg&);

    static size_t GetCommandMemoryAlignment(DeviceImpl<ApiVariationNvn8>*);
    static size_t GetControlMemoryAlignment(DeviceImpl<ApiVariationNvn8>*);

    CommandBufferImpl();
    ~CommandBufferImpl();

    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);

    void AddCommandMemory(MemoryPoolImpl<ApiVariationNvn8>*, ptrdiff_t, size_t);
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

    void SetPipeline(const PipelineImpl<ApiVariationNvn8>*);
    void SetRenderTargets(int, const ColorTargetViewImpl<ApiVariationNvn8>* const*,
                          const DepthStencilViewImpl<ApiVariationNvn8>*);
    void SetVertexBuffer(int, const GpuAddress&, ptrdiff_t, size_t);
    void SetViewportScissorState(const ViewportScissorStateImpl<ApiVariationNvn8>*);

    void CopyBuffer(BufferImpl<ApiVariationNvn8>*, ptrdiff_t, const BufferImpl<ApiVariationNvn8>*,
                    ptrdiff_t, size_t);
    void CopyImage(TextureImpl<ApiVariationNvn8>*, const TextureSubresource&, int, int, int,
                   const TextureImpl<ApiVariationNvn8>*, const TextureCopyRegion&);
    void CopyBufferToImage(TextureImpl<ApiVariationNvn8>*, const BufferImpl<ApiVariationNvn8>*,
                           const BufferTextureCopyRegion&);
    void CopyBufferToImage(TextureImpl<ApiVariationNvn8>*, const TextureCopyRegion&,
                           const BufferImpl<ApiVariationNvn8>*, ptrdiff_t);
    void CopyImageToBuffer(BufferImpl<ApiVariationNvn8>*, const TextureImpl<ApiVariationNvn8>*,
                           const BufferTextureCopyRegion&);
    void CopyImageToBuffer(BufferImpl<ApiVariationNvn8>*, ptrdiff_t,
                           const TextureImpl<ApiVariationNvn8>*, const TextureCopyRegion&);
    void BlitImage(TextureImpl<ApiVariationNvn8>*, const TextureCopyRegion&,
                   const TextureImpl<ApiVariationNvn8>*, const TextureCopyRegion&, int);
    void ClearBuffer(BufferImpl<ApiVariationNvn8>*, ptrdiff_t, size_t, uint32_t);
    void ClearColor(ColorTargetViewImpl<ApiVariationNvn8>*, float, float, float, float,
                    const TextureArrayRange*);
    void ClearColorTarget(ColorTargetViewImpl<ApiVariationNvn8>*, const ClearColorValue&,
                          const TextureArrayRange*);
    void ClearDepthStencil(DepthStencilViewImpl<ApiVariationNvn8>*, float, int,
                           DepthStencilClearMode, const TextureArrayRange*);

    void Resolve(TextureImpl<ApiVariationNvn8>*, int, int,
                 const ColorTargetViewImpl<ApiVariationNvn8>*, const TextureArrayRange*);
    void FlushMemory(int);
    void InvalidateMemory(int);

    void CallCommandBuffer(const CommandBufferImpl<ApiVariationNvn8>*);
    void CopyCommandBuffer(const CommandBufferImpl<ApiVariationNvn8>*);

    void SetBufferStateTransition(BufferImpl<ApiVariationNvn8>*, int, int, int, int);
    void SetTextureStateTransition(TextureImpl<ApiVariationNvn8>*, const TextureSubresourceRange*,
                                   int, int, int, int);
    void SetDescriptorPool(const DescriptorPoolImpl<ApiVariationNvn8>*);
    void SetRootSignature(PipelineType, RootSignatureImpl<ApiVariationNvn8>*);
    void SetRootBufferDescriptorTable(PipelineType, int, const DescriptorSlot&);
    void SetRootTextureAndSamplerDescriptorTable(PipelineType, int, const DescriptorSlot&,
                                                 const DescriptorSlot&);
    void SetRootConstantBuffer(PipelineType, int, const GpuAddress&, size_t);
    void SetRootUnorderedAccessBuffer(PipelineType, int, const GpuAddress&, size_t);
    void SetRootTextureAndSampler(PipelineType, int, const TextureViewImpl<ApiVariationNvn8>*,
                                  const SamplerImpl<ApiVariationNvn8>*);

    void BeginQuery(QueryTarget);
    void EndQuery(const GpuAddress&, QueryTarget);
    void WriteTimestamp(const GpuAddress&);

    void SetDepthBounds(float, float);
    void SetLineWidth(float);
    void SetViewports(int, int, const ViewportStateInfo*);
    void SetScissors(int, int, const ScissorStateInfo*);

    void SetConstantBuffer(int, ShaderStage, const DescriptorSlot&);
    void SetUnorderedAccessBuffer(int, ShaderStage, const DescriptorSlot&);
    void SetTextureAndSampler(int, ShaderStage, const DescriptorSlot&, const DescriptorSlot&);
    void SetTexture(int, ShaderStage, const DescriptorSlot&);
    void SetImage(int, ShaderStage, const DescriptorSlot&);

    void SetConstantBuffer(int, ShaderStage, const GpuAddress&, size_t);
    void SetUnorderedAccessBuffer(int, ShaderStage, const GpuAddress&, size_t);
    void SetTextureAndSampler(int, ShaderStage, const TextureViewImpl<ApiVariationNvn8>*,
                              const SamplerImpl<ApiVariationNvn8>*);
    void SetImage(int, ShaderStage, const TextureViewImpl<ApiVariationNvn8>*);

    void SetShader(const ShaderImpl<ApiVariationNvn8>*, int);
    void SetRasterizerState(const RasterizerStateImpl<ApiVariationNvn8>*);
    void SetBlendState(const BlendStateImpl<ApiVariationNvn8>*);
    void SetDepthStencilState(const DepthStencilStateImpl<ApiVariationNvn8>*);
    void SetVertexState(const VertexStateImpl<ApiVariationNvn8>*);
    void SetTessellationState(const TessellationStateImpl<ApiVariationNvn8>*);
};

}  // namespace detail

}  // namespace nn::gfx
