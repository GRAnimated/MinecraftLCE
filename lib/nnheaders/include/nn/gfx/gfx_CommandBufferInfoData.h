#pragma once

#include <nn/nn_BitTypes.h>

namespace nn::gfx {

struct CommandBufferInfoData {
    Bit8 commandBufferType;
    char reserved2;
    Bit16 queueCapability;
    char reserved[28];
};

}  // namespace nn::gfx