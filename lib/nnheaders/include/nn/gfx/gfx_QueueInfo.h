#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_QueueInfoData.h>

namespace nn::gfx {

class QueueInfo : public detail::DataContainer<QueueInfoData> {
public:
    QueueInfo();
    void SetDefault();
    void SetCapability(int);
    int GetCapability() const;
};

}  // namespace nn::gfx