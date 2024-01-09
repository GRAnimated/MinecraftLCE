#pragma once

#include <nn/gfx/detail/gfx_Sync-api.nvn.8.h>

namespace nn::gfx {

template <class TTarget>
class TFence : public detail::FenceImpl<TTarget> {
    NN_NO_COPY(TFence);

public:
    typedef FenceInfo InfoType;

    TFence();
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
    bool IsSignaled();
    SyncResult Sync(TimeSpan);
};

template <class TTarget>
class TSemaphore : public detail::SemaphoreImpl<TTarget> {
    NN_NO_COPY(TSemaphore);

public:
    typedef SemaphoreInfo InfoType;
    TSemaphore();
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
};

}  // namespace nn::gfx