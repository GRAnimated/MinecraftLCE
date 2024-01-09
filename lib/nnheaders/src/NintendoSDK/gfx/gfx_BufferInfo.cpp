#include <nn/gfx/gfx_BufferInfo.h>

namespace nn::gfx {

void BufferInfo::SetDefault() {
    SetSize(0);
    SetGpuAccessFlags(0);
}

void BufferTextureViewInfo::SetDefault() {
    SetImageFormat(ImageFormat_Undefined);
    SetOffset(0);
    SetSize(0);
    SetBufferPtr(nullptr);
}

}  // namespace nn::gfx