#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/types.h>

namespace nn::gfx {
struct GpuAddressData {
    uint64_t value;
    uint64_t impl;
};

class GpuAddress : public detail::DataContainer<GpuAddressData> {
public:
    GpuAddress();
    void Offset(ptrdiff_t);
};
}  // namespace nn::gfx