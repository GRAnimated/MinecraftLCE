#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_CommandBufferInfoData.h>
#include <nn/gfx/gfx_Enum.h>

namespace nn::gfx {

class CommandBufferInfo : public detail::DataContainer<CommandBufferInfoData> {
public:
    CommandBufferInfo();
    void SetDefault();
    void SetCommandBufferType(CommandBufferType);
    void SetQueueCapability(int);
    CommandBufferType GetCommandBufferType() const;
    int GetQueueCapability() const;
};

}  // namespace nn::gfx