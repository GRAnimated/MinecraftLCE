#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_DescriptorPoolInfoData.h>
#include <nn/gfx/gfx_Enum.h>

namespace nn::gfx {
class DescriptorPoolInfo : public detail::DataContainer<DescriptorPoolInfoData> {
public:
    DescriptorPoolInfo();
    void SetDefault();
    void SetDescriptorPoolType(DescriptorPoolType);
    void SetSlotCount(int);

    DescriptorPoolType GetDescriptorPoolType() const {
        return static_cast<DescriptorPoolType>(descriptorPoolType);
    }

    int GetSlotCount() const { return slotCount; }
};
}  // namespace nn::gfx