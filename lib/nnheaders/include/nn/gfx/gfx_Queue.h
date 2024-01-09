#pragma once

#include <nn/gfx/detail/gfx_Queue-api.nvn.8.h>

namespace nn::gfx {

template <class TTarget>
class TQueue : public detail::QueueImpl<TTarget> {
    NN_NO_COPY(TQueue);

public:
    typedef QueueInfo InfoType;

    TQueue();
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
    void ExecuteCommand(TCommandBuffer<TTarget>*, TFence<TTarget>*);
    void Flush();
    void Sync();
    void SetSemaphore(TSemaphore<TTarget>*);
    void SyncSemaphore(const TSemaphore<TTarget>*);
    void CopyToScanBuffer(TSwapChain<TTarget>*, const TColorTargetView<TTarget>*);
    void Present(TSwapChain<TTarget>*, int);
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

}  // namespace nn::gfx