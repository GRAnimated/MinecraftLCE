#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_DescriptorPoolData-api.nvn.8.h>
#include <nn/gfx/gfx_Enum.h>

namespace nn::gfx {

class DescriptorPoolInfo;
class DescriptorSlot;
class GpuAddress;

namespace detail {

template <>
class DescriptorPoolImpl<ApiVariationNvn8>
    : public DataContainer<DescriptorPoolImplData<ApiVariationNvn8>> {
    NN_NO_COPY(DescriptorPoolImpl);

public:
    typedef DescriptorPoolInfo InfoType;

    static size_t CalculateDescriptorPoolSize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    static ptrdiff_t GetDescriptorSlotIncrementSize(DeviceImpl<ApiVariationNvn8>*,
                                                    DescriptorPoolType);
    static size_t GetDescriptorPoolAlignment(DeviceImpl<ApiVariationNvn8>*, const InfoType&);

    DescriptorPoolImpl();
    ~DescriptorPoolImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&,
                    MemoryPoolImpl<ApiVariationNvn8>*, ptrdiff_t, size_t);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
    void BeginUpdate();
    void EndUpdate();
    void SetBufferView(int, const GpuAddress&, size_t);
    void SetSampler(int, const SamplerImpl<ApiVariationNvn8>*);
    void SetTextureView(int, const TextureViewImpl<ApiVariationNvn8>*);
    void SetImage(int, const TextureViewImpl<ApiVariationNvn8>*);
    void SetBufferTextureView(int, const BufferTextureViewImpl<ApiVariationNvn8>*);
    void SetBufferImage(int, const BufferTextureViewImpl<ApiVariationNvn8>*);
    void GetDescriptorSlot(DescriptorSlot*, int) const;
    int GetDescriptorSlotIndex(const DescriptorSlot&) const;
};
}  // namespace detail
}  // namespace nn::gfx