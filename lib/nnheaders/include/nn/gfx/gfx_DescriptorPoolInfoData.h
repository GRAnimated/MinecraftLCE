#pragma once

#include <nn/nn_BitTypes.h>

namespace nn::gfx {
struct DescriptorPoolInfoData {
    Bit8 descriptorPoolType;
    char reserved2[3];
    uint32_t slotCount;
    char reserved[24];
};
}  // namespace nn::gfx