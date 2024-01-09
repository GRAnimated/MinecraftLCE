#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_BufferData-api.nvn.8.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/types.h>

namespace nn::gfx {

class BufferInfo;
class BufferTextureViewInfo;
class GpuAddress;

namespace detail {

template <>
class BufferImpl<ApiVariationNvn8> : public DataContainer<BufferImplData<ApiVariationNvn8>> {
    NN_NO_COPY(BufferImpl);

public:
    typedef BufferInfo InfoType;

    static const bool IsMemoryPoolRequired = true;

    static size_t GetBufferAlignment(DeviceImpl<ApiVariationNvn8>*, const InfoType&);

    BufferImpl();
    ~BufferImpl();

    void Initialize(DeviceImpl<ApiVariationNvn8>*, const BufferInfo&,
                    MemoryPoolImpl<ApiVariationNvn8>*, ptrdiff_t, size_t);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
    void* Map() const;
    void Unmap() const;
    void FlushMappedRange(ptrdiff_t, size_t) const;
    void InvalidateMappedRange(ptrdiff_t, size_t) const;
    void GetGpuAddress(GpuAddress*) const;
};

template <>
class BufferTextureViewImpl<ApiVariationNvn8>
    : public DataContainer<BufferTextureViewImplData<ApiVariationNvn8>> {
    NN_NO_COPY(BufferTextureViewImpl);

public:
    typedef BufferTextureViewInfo InfoType;

    static size_t GetOffsetAlignment(DeviceImpl<ApiVariationNvn8>*, const InfoType&);

    BufferTextureViewImpl();
    ~BufferTextureViewImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

}  // namespace detail

}  // namespace nn::gfx