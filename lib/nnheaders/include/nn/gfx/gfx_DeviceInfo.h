#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_DeviceInfoData.h>
#include <nn/gfx/gfx_Enum.h>

namespace nn::gfx {

class DeviceInfo : public detail::DataContainer<DeviceInfoData> {
public:
    DeviceInfo();
    void SetDefault();
    void SetDebugMode(DebugMode);
    void SetApiVersion(int, int);
    DebugMode GetDebugMode() const;
    int GetApiMajorVersion() const;
    int GetApiMinorVersion() const;
};

}  // namespace nn::gfx