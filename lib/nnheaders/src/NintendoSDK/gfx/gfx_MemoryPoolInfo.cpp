#include <nn/gfx/gfx_MemoryPoolInfo.h>

#include <nn/gfx/gfx_Enum.h>

namespace nn::gfx {

void MemoryPoolInfo::SetDefault() {
    SetMemoryPoolProperty(MemoryPoolProperty_GpuCached | MemoryPoolProperty_CpuUncached);
    SetPoolMemory(nullptr, 0);
}

}  // namespace nn::gfx