#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_QueueData-api.nvn.8.h>

namespace nn::gfx {

class QueueInfo;

namespace detail {

template <>
class QueueImpl<ApiVariationNvn8> : public DataContainer<QueueImplData<ApiVariationNvn8>> {
    NN_NO_COPY(QueueImpl);

public:
    typedef QueueInfo InfoType;

    QueueImpl();
    ~QueueImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
    void ExecuteCommand(CommandBufferImpl<ApiVariationNvn8>*, FenceImpl<ApiVariationNvn8>*);
    void Flush() const;
    void Sync() const;
    void SetSemaphore(SemaphoreImpl<ApiVariationNvn8>*);
    void SyncSemaphore(const SemaphoreImpl<ApiVariationNvn8>*);
    void CopyToScanBuffer(SwapChainImpl<ApiVariationNvn8>*,
                          const ColorTargetViewImpl<ApiVariationNvn8>*);
    void Present(SwapChainImpl<ApiVariationNvn8>*, int);
};

}  // namespace detail
}  // namespace nn::gfx