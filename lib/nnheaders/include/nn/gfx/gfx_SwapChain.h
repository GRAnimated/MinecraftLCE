#pragma once

#include <nn/gfx/detail/gfx_SwapChain-api.nvn.8.h>

namespace nn::gfx {

template <class TTarget>
class TSwapChain : public detail::SwapChainImpl<TTarget> {
    NN_NO_COPY(TSwapChain);

public:
    typedef SwapChainInfo InfoType;

    static const bool IsMemoryPoolRequired = true;

    static size_t GetScanBufferAlignment(TDevice<TTarget>*, const InfoType&);
    static size_t CalculateScanBufferSize(TDevice<TTarget>*, const InfoType&);

    TSwapChain();
    void Initialize(TDevice<TTarget>*, const InfoType&, TMemoryPool<TTarget>*, ptrdiff_t, size_t);
    void Finalize(TDevice<TTarget>*);
    int GetScanBufferViews(TColorTargetView<TTarget>**, int);
    int GetScanBuffers(TTexture<TTarget>**, int);
    AcquireScanBufferResult AcquireNextScanBufferIndex(int*, TSemaphore<TTarget>*,
                                                       TFence<TTarget>*);
    int AcquireNextScanBufferIndex();
    TColorTargetView<TTarget>* AcquireNextScanBufferView();
    TTexture<TTarget>* AcquireNextScanBuffer();
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

}  // namespace nn::gfx