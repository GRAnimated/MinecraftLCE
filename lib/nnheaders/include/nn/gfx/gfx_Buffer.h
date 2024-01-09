#pragma once

#include <nn/gfx/detail/gfx_Buffer-api.nvn.8.h>
#include <nn/gfx/gfx_Common.h>

namespace nn::gfx {

template <class TTarget>
class TBuffer : public detail::BufferImpl<TTarget> {
    NN_NO_COPY(TBuffer);

public:
    typedef BufferInfo InfoType;

    static const bool IsMemoryPoolRequired = true;

    static size_t GetBufferAlignment(TDevice<TTarget>*, const InfoType&);

    TBuffer();
    void Initialize(TDevice<TTarget>*, const InfoType&, TMemoryPool<TTarget>*, ptrdiff_t, size_t);
    void Finalize(TDevice<TTarget>*);
    void* Map() const;
    void Unmap() const;
    void FlushMappedRange(ptrdiff_t, size_t) const;
    void InvalidateMappedRange(ptrdiff_t, size_t) const;
    void GetGpuAddress(GpuAddress*) const;
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

}  // namespace nn::gfx