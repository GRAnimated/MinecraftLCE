#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_SyncInfoData.h>

namespace nn::gfx {

class FenceInfo : public detail::DataContainer<FenceInfoData> {
public:
    FenceInfo() {}
    void SetDefault();
};

class SemaphoreInfo : public detail::DataContainer<SemaphoreInfoData> {
public:
    SemaphoreInfo() {}
    void SetDefault();
};

}  // namespace nn::gfx