#pragma once

#include <nn/gfx/gfx_Common.h>

namespace nn::gfx {

typedef TBuffer<DefaultApi> Buffer;
typedef TCommandBuffer<DefaultApi> CommandBuffer;
typedef TDescriptorPool<DefaultApi> DescriptorPool;
typedef TDevice<DefaultApi> Device;
typedef TMemoryPool<DefaultApi> MemoryPool;
typedef TQueue<DefaultApi> Queue;
typedef TSampler<DefaultApi> Sampler;
typedef TShader<DefaultApi> Shader;

typedef TRasterizerState<DefaultApi> RasterizerState;
typedef TBlendState<DefaultApi> BlendState;
typedef TDepthStencilState<DefaultApi> DepthStencilState;
typedef TVertexState<DefaultApi> VertexState;
typedef TViewportScissorState<DefaultApi> ViewportScissorState;

typedef TSwapChain<DefaultApi> SwapChain;
typedef TFence<DefaultApi> Fence;
typedef TSemaphore<DefaultApi> Semaphore;

typedef TTexture<DefaultApi> Texture;
typedef TTextureView<DefaultApi> TextureView;
typedef TColorTargetView<DefaultApi> ColorTargetView;
typedef TDepthStencilView<DefaultApi> DepthStencilView;

}  // namespace nn::gfx