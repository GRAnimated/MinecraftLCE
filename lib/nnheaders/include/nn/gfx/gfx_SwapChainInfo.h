#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_SwapChainInfoData.h>

namespace nn::gfx {
class SwapChainInfo : public detail::DataContainer<SwapChainInfoData> {
public:
    SwapChainInfo();
    void SetDefault();
    void SetLayer(vi::Layer*);
    void SetFormat(ImageFormat);
    void SetBufferCount(int);
    void SetWidth(int);
    void SetHeight(int);
    vi::Layer* GetLayer() const;
    ImageFormat GetFormat() const { return static_cast<ImageFormat>(format); }
    int GetBufferCount() const;
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
};
}  // namespace nn::gfx