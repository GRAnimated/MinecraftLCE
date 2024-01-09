#pragma once

#include <nn/util/util_BinTypes.h>

namespace nn::gfx {

struct ResUserDataData {
    nn::util::BinPtrToString pName;
    nn::util::BinPtr pData;
    uint32_t count;
    uint8_t type;
    char reserved[43];
};

}  // namespace nn::gfx
