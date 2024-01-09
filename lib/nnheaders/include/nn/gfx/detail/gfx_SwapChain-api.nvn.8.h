#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>

namespace nn::gfx {

class SwapChainInfo;

namespace detail {

template <>
class SwapChainImpl<ApiVariationNvn8> : public DataContainer<SwapChainImplData<ApiVariationNvn8>> {
    NN_NO_COPY(SwapChainImpl);

public:
    typedef SwapChainInfo InfoType;

    static const bool IsMemoryPoolRequired = true;

    static size_t GetScanBufferAlignment(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    static size_t CalculateScanBufferSize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);

    SwapChainImpl();
    ~SwapChainImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&,
                    MemoryPoolImpl<ApiVariationNvn8>*, ptrdiff_t, size_t);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
    int GetScanBufferViews(TColorTargetView<ApiVariationNvn8>**, int);
    int GetScanBuffers(TTexture<ApiVariationNvn8>**, int);
    AcquireScanBufferResult AcquireNextScanBufferIndex(int*, SemaphoreImpl<ApiVariationNvn8>*,
                                                       FenceImpl<ApiVariationNvn8>*);
    int AcquireNextScanBufferIndex();
    ColorTargetViewImpl<ApiVariationNvn8>* AcquireNextScanBufferView();
    TextureImpl<ApiVariationNvn8>* AcquireNextScanBuffer();
};

}  // namespace detail
}  // namespace nn::gfx