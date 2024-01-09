/**
 * @file deviceimpl.h
 * @brief Device implementation for GFX.
 */

#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_DeviceData-api.nvn.8.h>

namespace nn::gfx {

class DeviceInfo;

namespace detail {

template <>
class DeviceImpl<ApiVariationNvn8> : public DataContainer<DeviceImplData<ApiVariationNvn8>> {
    NN_NO_COPY(DeviceImpl);

public:
    typedef DeviceInfo InfoType;

    DeviceImpl();
    ~DeviceImpl();
    void Initialize(const InfoType&);
    void Finalize();
};

}  // namespace detail

}  // namespace nn::gfx
