#pragma once

#include <nn/gfx/detail/gfx_Misc.h>
#include <nn/nn_BitTypes.h>

namespace nn {

namespace vi {
class Layer;
}  // namespace vi

namespace gfx {

struct SwapChainInfoData {
    uint8_t bufferCount;
    char reserved2[3];
    Bit32 format;
    uint32_t width;
    uint32_t height;
    char reserved3[8];
    detail::Ptr<vi::Layer> pLayer;
    char reserved[30];
};

}  // namespace gfx
}  // namespace nn