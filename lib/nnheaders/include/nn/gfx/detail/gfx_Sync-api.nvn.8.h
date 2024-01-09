#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_SyncData-api.nvn.8.h>

namespace nn {

class TimeSpan;

namespace gfx {

class FenceInfo;
class SemaphoreInfo;

namespace detail {

template <>
class FenceImpl<ApiVariationNvn8> : public DataContainer<FenceImplData<ApiVariationNvn8>> {
    NN_NO_COPY(FenceImpl);

public:
    typedef FenceInfo InfoType;

    FenceImpl();
    ~FenceImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
    bool IsSignaled() const;
    SyncResult Sync(TimeSpan) const;
};

template <>
class SemaphoreImpl<ApiVariationNvn8> : public DataContainer<SemaphoreImplData<ApiVariationNvn8>> {
    NN_NO_COPY(SemaphoreImpl);

public:
    typedef SemaphoreInfo InfoType;

    SemaphoreImpl();
    ~SemaphoreImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

}  // namespace detail
}  // namespace gfx
}  // namespace nn