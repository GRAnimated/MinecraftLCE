#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_TextureData-api.nvn.8.h>

namespace nn::gfx {

class TextureInfo;
class TextureViewInfo;
class ColorTargetViewInfo;
class DepthStencilViewInfo;

namespace detail {
template <>
class TextureImpl<ApiVariationNvn8> : public DataContainer<TextureImplData<ApiVariationNvn8>> {
    NN_NO_COPY(TextureImpl);

public:
    typedef TextureInfo InfoType;

    static const bool IsMemoryPoolRequired;

    static size_t CalculateMipDataAlignment(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    static size_t CalculateMipDataSize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    static void CalculateMipDataOffsets(ptrdiff_t*, DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    static size_t GetRowPitch(DeviceImpl<ApiVariationNvn8>*, const InfoType&);

    TextureImpl();
    ~TextureImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&,
                    MemoryPoolImpl<ApiVariationNvn8>*, ptrdiff_t, size_t);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

template <>
class TextureViewImpl<ApiVariationNvn8>
    : public DataContainer<TextureViewImplData<ApiVariationNvn8>> {
    NN_NO_COPY(TextureViewImpl);

public:
    typedef TextureViewInfo InfoType;

    TextureViewImpl();

    ~TextureViewImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

template <>
class ColorTargetViewImpl<ApiVariationNvn8>
    : public DataContainer<ColorTargetViewImplData<ApiVariationNvn8>> {
    NN_NO_COPY(ColorTargetViewImpl);

public:
    typedef ColorTargetViewInfo InfoType;

    ColorTargetViewImpl();

    ~ColorTargetViewImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

template <>
class DepthStencilViewImpl<ApiVariationNvn8>
    : public DataContainer<DepthStencilViewImplData<ApiVariationNvn8>> {
    NN_NO_COPY(DepthStencilViewImpl);

public:
    typedef DepthStencilViewInfo InfoType;

    DepthStencilViewImpl();
    ~DepthStencilViewImpl();
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

}  // namespace detail

}  // namespace nn::gfx