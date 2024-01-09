#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_StateData-api.nvn.8.h>

namespace nn::gfx {

class RasterizerStateInfo;
class BlendStateInfo;
class DepthStencilStateInfo;
class VertexStateInfo;
class TessellationStateInfo;
class ViewportScissorStateInfo;

namespace detail {

template <>
class RasterizerStateImpl<ApiVariationNvn8>
    : public DataContainer<RasterizerStateImplData<ApiVariationNvn8>> {
public:
    typedef RasterizerStateInfo InfoType;

    RasterizerStateImpl();
    ~RasterizerStateImpl();

    void Initialize(DeviceImpl<ApiVariationNvn8>* device, const InfoType& info);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

template <>
class BlendStateImpl<ApiVariationNvn8>
    : public DataContainer<BlendStateImplData<ApiVariationNvn8>> {
public:
    typedef BlendStateInfo InfoType;

    static size_t GetRequiredMemorySize(const InfoType& info);

    BlendStateImpl();
    ~BlendStateImpl();

    void SetMemory(void* p, size_t s);
    void* GetMemory();
    void* GetMemory() const;

    void Initialize(DeviceImpl<ApiVariationNvn8>* device, const InfoType& info);
    void Finalize(DeviceImpl<ApiVariationNvn8>* device);
};

template <>
class DepthStencilStateImpl<ApiVariationNvn8>
    : public DataContainer<DepthStencilStateImplData<ApiVariationNvn8>> {
public:
    typedef DepthStencilStateInfo InfoType;

    DepthStencilStateImpl();
    ~DepthStencilStateImpl();

    void Initialize(DeviceImpl<ApiVariationNvn8>*, const DepthStencilStateInfo& info);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

template <>
class VertexStateImpl<ApiVariationNvn8>
    : public DataContainer<VertexStateImplData<ApiVariationNvn8>> {
public:
    typedef VertexStateInfo InfoType;

    enum RequiredMemoryInfo { RequiredMemoryInfo_Alignment = 8 };

    VertexStateImpl();
    ~VertexStateImpl();
    static size_t GetRequiredMemorySize(const InfoType&);
    void SetMemory(void*, size_t);
    void* GetMemory();
    const void* GetMemory() const;
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&,
                    const ShaderImpl<ApiVariationNvn8>*);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

template <>
class TessellationStateImpl<ApiVariationNvn8>
    : public DataContainer<TessellationStateImplData<ApiVariationNvn8>> {
public:
    typedef TessellationStateInfo InfoType;

    TessellationStateImpl();
    ~TessellationStateImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

template <>
class ViewportScissorStateImpl<ApiVariationNvn8>
    : public DataContainer<ViewportScissorStateImplData<ApiVariationNvn8>> {
public:
    typedef ViewportScissorStateInfo InfoType;

    ViewportScissorStateImpl();
    ~ViewportScissorStateImpl();
    static size_t GetRequiredMemorySize(const InfoType&);
    void SetMemory(void*, size_t);
    void* GetMemory();
    const void* GetMemory() const;
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

}  // namespace detail
}  // namespace nn::gfx