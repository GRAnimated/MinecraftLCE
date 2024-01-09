#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_RootSignatureData-api.common.h>

namespace nn::gfx {

class RootSignatureInfo;

namespace detail {
template <class TTarget>
class RootSignatureImplCommon
    : public DataContainer<RootSignatureImplData<ApiType<LowLevelApi_Common>>> {
public:
    typedef RootSignatureInfo InfoType;

    static size_t GetRequiredMemorySize(const InfoType&);

    RootSignatureImplCommon();
    ~RootSignatureImplCommon();

    void SetMemory(void*, size_t);
    void* GetMemory();
    const void* GetMemory() const;
    void Initialize(DeviceImpl<TTarget>*, const InfoType&);
    void Finalize(DeviceImpl<TTarget>*);
};
}  // namespace detail
}  // namespace nn::gfx