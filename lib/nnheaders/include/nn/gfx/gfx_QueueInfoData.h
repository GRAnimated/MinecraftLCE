#pragma once

#include <nn/nn_BitTypes.h>

namespace nn::gfx {

struct QueueInfoData {
    Bit16 capability;
    char reserved[30];
};

}  // namespace nn::gfx