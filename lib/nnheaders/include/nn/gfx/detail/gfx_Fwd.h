// todo: validate the existance of this file and figure out what it's named

#pragma once

#include <nn/gfx/gfx_Enum.h>

namespace nn::gfx {

template <typename TTarget>
class TDevice;

template <typename TTarget>
class TCommandBuffer;

template <typename TTarget>
class TMemoryPool;

template <typename TTarget>
class TTexture;

template <typename TTarget>
class TPipeline;

template <typename TTarget>
class TColorTargetView;

template <typename TTarget>
class TDepthStencilView;

template <typename TTarget>
class TViewportScissorState;

template <typename TTarget>
class TBuffer;

template <typename TTarget>
class TDescriptorPool;

template <typename TTarget>
class TRootSignature;

template <typename TTarget>
class TTextureView;

template <typename TTarget>
class TSampler;

template <typename TTarget>
class TShader;

template <typename TTarget>
class TRasterizerState;

template <typename TTarget>
class TBlendState;

template <typename TTarget>
class TDepthStencilState;

template <typename TTarget>
class TVertexState;

template <typename TTarget>
class TTessellationState;

template <typename TTarget>
class TQueue;

template <typename TTarget>
class TInteroperation;

template <typename TTarget>
class TFence;

template <typename TTarget>
class TSemaphore;

template <typename TTarget>
class TSwapChain;

template <typename TTarget>
class TColorTargetView;

template <typename TTarget>
class TBufferTextureView;

template <typename TTarget>
struct BufferImplData;

template <typename TTarget>
struct BufferTextureViewImplData;

template <typename TTarget>
struct CommandBufferImplData;

template <typename TTarget>
struct RasterizerStateImplData;

template <typename TTarget>
struct BlendStateImplData;

template <typename TTarget>
struct DepthStencilStateImplData;

template <typename TTarget>
struct VertexStateImplData;

template <typename TTarget>
struct TessellationStateImplData;

template <typename TTarget>
struct ViewportScissorStateImplData;

template <typename TTarget>
struct PipelineImplData;

template <typename TTarget>
struct ShaderImplData;

template <typename TTarget>
struct TextureImplData;

template <typename TTarget>
struct TextureViewImplData;

template <typename TTarget>
struct ColorTargetViewImplData;

template <typename TTarget>
struct DepthStencilViewImplData;

template <typename TTarget>
struct MemoryPoolImplData;

template <typename TTarget>
struct DeviceImplData;

template <typename TTarget>
struct DescriptorPoolImplData;

template <class TTarget>
struct SamplerImplData;

template <class TTarget>
struct QueueImplData;

template <class TTarget>
struct SwapChainImplData;

template <class TTarget>
struct FenceImplData;

template <class TTarget>
struct SemaphoreImplData;

struct ImageFormatProperty;

namespace detail {

template <typename TTarget>
class MemoryPoolImpl;

template <typename TTarget>
class DeviceImpl;

template <typename TTarget>
class BufferImpl;

template <typename TTarget>
class BufferTextureViewImpl;

template <typename TTarget>
class CommandBufferImpl;

template <typename TTarget>
class PipelineImpl;

template <typename TTarget>
class RootSignatureImpl;

template <typename TTarget>
class ShaderImpl;

template <typename TTarget>
class TextureImpl;

template <typename TTarget>
class DescriptorPoolImpl;

template <typename TTarget>
class SamplerImpl;

template <typename TTarget>
class RasterizerStateImpl;

template <typename TTarget>
class BlendStateImpl;

template <typename TTarget>
class DepthStencilStateImpl;

template <typename TTarget>
class VertexStateImpl;

template <typename TTarget>
class TessellationStateImpl;

template <typename TTarget>
class ViewportScissorStateImpl;

template <typename TTarget>
class ColorTargetViewImpl;

template <typename TTarget>
class DepthStencilViewImpl;

template <typename TTarget>
class TextureViewImpl;

template <typename TTarget>
class BufferTextureViewImpl;

template <typename TTarget>
class QueueImpl;

template <typename TTarget>
class FenceImpl;

template <typename TTarget>
class SemaphoreImpl;

template <typename TTarget>
class SwapChainImpl;

// todo: figure out where to put this
template <typename TTarget>
void GetImageFormatProperty(ImageFormatProperty*, DeviceImpl<TTarget>*, ImageFormat);

}  // namespace detail

namespace util {
// todo: figure out where to put these
template <typename TTarget>
void SetMemoryPoolDebugLabel(TMemoryPool<TTarget>*, const char*);
template <typename TTarget>
void SetBufferDebugLabel(TBuffer<TTarget>*, const char*);
template <typename TTarget>
void SetTextureDebugLabel(TTexture<TTarget>*, const char*);
template <typename TTarget>
void SetSamplerDebugLabel(TSampler<TTarget>*, const char*);
}  // namespace util
}  // namespace nn::gfx