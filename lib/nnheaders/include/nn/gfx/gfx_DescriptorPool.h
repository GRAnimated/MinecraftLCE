#pragma once

#include <nn/gfx/detail/gfx_DescriptorPool-api.nvn.8.h>

namespace nn::gfx {

template <class TTarget>
class TDescriptorPool : public detail::DescriptorPoolImpl<TTarget> {
    NN_NO_COPY(TDescriptorPool);

public:
    typedef DescriptorPoolInfo InfoType;

    static size_t CalculateDescriptorPoolSize(TDevice<TTarget>*, const InfoType&);
    static size_t GetDescriptorPoolAlignment(TDevice<TTarget>*, const InfoType&);
    static ptrdiff_t GetDescriptorSlotIncrementSize(TDevice<TTarget>*, DescriptorPoolType);

    TDescriptorPool();
    void Initialize(TDevice<TTarget>*, const InfoType&, TMemoryPool<TTarget>*, ptrdiff_t, size_t);
    void Finalize(TDevice<TTarget>*);
    void BeginUpdate();
    void EndUpdate();
    void SetBufferView(int, const GpuAddress&, size_t);
    void SetSampler(int, const TSampler<TTarget>*);
    void SetTextureView(int, const TTextureView<TTarget>*);
    void SetImage(int, const TTextureView<TTarget>*);
    void SetBufferTextureView(int, const TBufferTextureView<TTarget>*);
    void SetBufferImage(int, const TBufferTextureView<TTarget>*);
    void GetDescriptorSlot(DescriptorSlot*, int) const;
    int GetDescriptorSlotIndex(const DescriptorSlot&) const;
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

}  // namespace nn::gfx