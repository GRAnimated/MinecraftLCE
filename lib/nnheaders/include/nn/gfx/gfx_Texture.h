#pragma once

#include <nn/gfx/detail/gfx_Texture-api.nvn.8.h>
#include <nn/gfx/gfx_Common.h>

namespace nn::gfx {

template <class TTarget>
class TTexture : public detail::TextureImpl<TTarget> {
    NN_NO_COPY(TTexture);

public:
    typedef TextureInfo InfoType;

    static const bool IsMemoryPoolRequired = true;

    static size_t CalculateMipDataAlignment(TDevice<TTarget>*, const InfoType&);
    static size_t CalculateMipDataSize(TDevice<TTarget>*, const InfoType&);
    static void CalculateMipDataOffsets(ptrdiff_t*, TDevice<TTarget>*, const InfoType&);
    static size_t GetRowPitch(TDevice<TTarget>*, const InfoType&);
    void Initialize(TDevice<TTarget>*, const InfoType&, TMemoryPool<TTarget>*, ptrdiff_t, size_t);

    TTexture();
    void Finalize(TDevice<TTarget>*);
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

template <class TTarget>
class TTextureView : public detail::TextureViewImpl<TTarget> {
    NN_NO_COPY(TTextureView);

public:
    typedef TextureViewInfo InfoType;

    TTextureView();
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

template <class TTarget>
class TColorTargetView : public detail::ColorTargetViewImpl<TTarget> {
    NN_NO_COPY(TColorTargetView);

public:
    typedef ColorTargetViewInfo InfoType;

    TColorTargetView();
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

template <class TTarget>
class TDepthStencilView : public detail::DepthStencilViewImpl<TTarget> {
    NN_NO_COPY(TDepthStencilView);

public:
    typedef DepthStencilViewInfo InfoType;

    TDepthStencilView();
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

}  // namespace nn::gfx