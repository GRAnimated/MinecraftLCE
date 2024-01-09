#pragma once

#include <nn/nn_BitTypes.h>

namespace nn::gfx {

struct SamplerInfoData {
    Bit8 addressU;
    Bit8 addressV;
    Bit8 addressW;
    Bit8 comparisonFunction;
    Bit8 borderColorType;
    uint8_t maxAnisotropy;
    Bit16 filterMode;
    float minLod;
    float maxLod;
    float lodBias;
    char reserved[12];
};

}  // namespace nn::gfx