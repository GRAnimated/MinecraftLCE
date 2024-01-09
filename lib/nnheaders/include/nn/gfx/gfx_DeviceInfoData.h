#pragma once

#include <nn/nn_BitTypes.h>

namespace nn::gfx {
struct DeviceInfoData {
    Bit8 debugMode;
    char reserved2[3];
    uint16_t apiMajorVersion;
    uint16_t apiMinorVersion;
    char reserved[56];
};
}  // namespace nn::gfx