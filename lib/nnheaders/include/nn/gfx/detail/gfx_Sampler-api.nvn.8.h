#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_SamplerData-api.nvn.8.h>

namespace nn::gfx {

class SamplerInfo;

namespace detail {
template <>
class SamplerImpl<ApiVariationNvn8> : public DataContainer<SamplerImplData<ApiVariationNvn8>> {
    NN_NO_COPY(SamplerImpl);

public:
    typedef SamplerInfo InfoType;

    SamplerImpl();
    ~SamplerImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

}  // namespace detail
}  // namespace nn::gfx