#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_BufferInfoData.h>
#include <nn/gfx/gfx_Enum.h>

namespace nn::gfx {

class BufferInfo : public detail::DataContainer<BufferInfoData> {
public:
    BufferInfo() {}

    void SetDefault();

    void SetSize(size_t value) { size = value; }
    void SetGpuAccessFlags(int value) { gpuAccessFlag = value; }
    size_t GetSize() const { return size; }
    int GetGpuAccessFlags() const { return gpuAccessFlag; }
};

class BufferTextureViewInfo : public detail::DataContainer<BufferTextureViewInfoData> {
public:
    BufferTextureViewInfo() {}

    void SetDefault();

    void SetImageFormat(ImageFormat value) { format = value; }
    void SetOffset(ptrdiff_t value) { offset = value; }
    void SetSize(size_t value) { size = value; }
    void SetBufferPtr(const void* value) { pBuffer = value; }

    ImageFormat GetImageFormat() const { return static_cast<ImageFormat>(format); }
    ptrdiff_t GetOffset() const { return offset; }
    size_t GetSize() const { return size; }

    detail::Caster<const void> GetBufferPtr() const {
        return detail::Caster<const void>(pBuffer.ptr);
    }
};

}  // namespace nn::gfx