#pragma once

#include <nn/gfx/detail/gfx_RequiredMemory.h>
#include <nn/gfx/detail/gfx_State-api.nvn.8.h>

namespace nn::gfx {

template <class TTarget>
class TRasterizerState : public detail::RasterizerStateImpl<TTarget> {
    NN_NO_COPY(TRasterizerState);

public:
    typedef RasterizerStateInfo InfoType;

    TRasterizerState();

    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
};

template <class TTarget>
class TBlendState : public detail::BlendStateImpl<TTarget>,
                    private detail::RequiredMemory<detail::BlendStateImpl<TTarget>> {
    NN_NO_COPY(TBlendState);

public:
    typedef BlendStateInfo InfoType;

    static size_t GetRequiredMemorySize(const InfoType&);

    TBlendState();
    void SetMemory(void*, size_t);
    void* GetMemory();
    const void* GetMemory() const;
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
};

template <class TTarget>
class TDepthStencilState : public detail::DepthStencilStateImpl<TTarget> {
    NN_NO_COPY(TDepthStencilState);

public:
    typedef DepthStencilStateInfo InfoType;

    TDepthStencilState();
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
};

template <class TTarget>
class TVertexState : public detail::VertexStateImpl<TTarget>,
                     private detail::RequiredMemory<detail::VertexStateImpl<TTarget>> {
    NN_NO_COPY(TVertexState);

public:
    typedef VertexStateInfo InfoType;

    static size_t GetRequiredMemorySize(const InfoType&);

    TVertexState();
    void SetMemory(void*, size_t);
    void* GetMemory();
    const void* GetMemory() const;
    void Initialize(TDevice<TTarget>*, const InfoType&, const TShader<TTarget>*);
    void Finalize(TDevice<TTarget>*);
};

template <class TTarget>
class TViewportScissorState
    : public detail::ViewportScissorStateImpl<TTarget>,
      private detail::RequiredMemory<detail::ViewportScissorStateImpl<TTarget>> {
    NN_NO_COPY(TViewportScissorState);

public:
    typedef ViewportScissorStateInfo InfoType;

    static size_t GetRequiredMemorySize(const InfoType&);

    TViewportScissorState();
    void SetMemory(void*, size_t);
    void* GetMemory();
    const void* GetMemory() const;
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
};

}  // namespace nn::gfx