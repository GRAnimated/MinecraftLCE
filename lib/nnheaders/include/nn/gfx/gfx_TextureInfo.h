#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_TextureInfoData.h>

namespace nn::gfx {

class TextureSubresourceRange;
class TextureArrayRange;

class TextureInfo : public detail::DataContainer<TextureInfoData> {
public:
    TextureInfo() {}

    void SetDefault();

    void SetImageStorageDimension(ImageStorageDimension value) { imageStorageDimension = value; }
    void SetImageFormat(ImageFormat value) { imageFormat = value; }
    void SetGpuAccessFlags(int value) { gpuAccessFlags = value; }
    void SetTileMode(TileMode value) { tileMode = value; }
    void SetWidth(int value) { width = value; }
    void SetHeight(int value) { height = value; }
    void SetDepth(int value) { depth = value; }
    void SetArrayLength(int value) { arrayLength = value; }
    void SetSwizzle(int value) { swizzle = value; }
    void SetMultiSampleCount(int value) { multisampleCount = value; }
    void SetMipCount(int value) { mipCount = value; }

    ImageStorageDimension GetImageStorageDimension() const {
        return static_cast<ImageStorageDimension>(imageStorageDimension);
    }

    ImageFormat GetImageFormat() const { return static_cast<ImageFormat>(imageFormat); }
    int GetGpuAccessFlags() const { return gpuAccessFlags; }
    TileMode GetTileMode() const { return static_cast<TileMode>(tileMode); }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    int GetDepth() const { return depth; }
    int GetMipCount() const { return mipCount; }
    int GetArrayLength() const { return arrayLength; }
    int GetSwizzle() const { return swizzle; }
    int GetMultisampleCount() const { return multisampleCount; }
};

class TextureViewInfo : public detail::DataContainer<TextureViewInfoData> {
public:
    TextureViewInfo() {}

    void SetDefault();

    void SetImageDimension(ImageDimension value) { imageDimension = value; }

    void SetDepthStencilTextureMode(DepthStencilFetchMode value) {
        depthStencilTextureMode = value;
    }

    void SetImageFormat(ImageFormat value) { imageFormat = value; }
    void SetTexturePtr(const void* value) { pTexture = value; }

    void SetChannelMapping(ChannelMapping red, ChannelMapping green, ChannelMapping blue,
                           ChannelMapping alpha) {
        channelMapping[ColorChannel_Red] = red;
        channelMapping[ColorChannel_Green] = green;
        channelMapping[ColorChannel_Blue] = blue;
        channelMapping[ColorChannel_Alpha] = alpha;
    }

    TextureSubresourceRange& EditSubresourceRange() {
        return gfx::DataToAccessor(subresourceRange);
    }

    ImageDimension GetImageDimension() const { return static_cast<ImageDimension>(imageDimension); }

    DepthStencilFetchMode GetDepthStencilTextureMode() const {
        return static_cast<DepthStencilFetchMode>(depthStencilTextureMode);
    }

    ImageFormat GetImageFormat() const { return static_cast<ImageFormat>(imageFormat); }

    detail::Caster<const void> GetTexturePtr() const {
        return detail::Caster<const void>(pTexture.ptr);
    }

    ChannelMapping GetChannelMapping(ColorChannel channel) const {
        return static_cast<ChannelMapping>(channelMapping[channel]);
    }

    const TextureSubresourceRange& GetSubresourceRange() const {
        return gfx::DataToAccessor(subresourceRange);
    }
};

class ColorTargetViewInfo : public detail::DataContainer<ColorTargetViewInfoData> {
public:
    ColorTargetViewInfo() {}
    void SetDefault();
    void SetImageDimension(ImageDimension value) { imageDimension = value; }
    void SetImageFormat(ImageFormat value) { imageFormat = value; }
    void SetMipLevel(int value) { mipLevel = value; }
    void SetTexturePtr(const void* value) { pTexture = value; }

    TextureArrayRange& EditArrayRange() { return gfx::DataToAccessor(arrayRange); }
    ImageDimension GetImageDimension() const { return static_cast<ImageDimension>(imageDimension); }
    ImageFormat GetImageFormat() const { return static_cast<ImageFormat>(imageFormat); }
    int GetMipLevel() const { return mipLevel; }

    detail::Caster<const void> GetTexturePtr() const {
        return detail::Caster<const void>(pTexture.ptr);
    }

    const TextureArrayRange& GetArrayRange() const { return gfx::DataToAccessor(arrayRange); }
};

class DepthStencilViewInfo : public detail::DataContainer<DepthStencilViewInfoData> {
public:
    DepthStencilViewInfo() {}

    void SetDefault();

    void SetImageDimension(ImageDimension value) { imageDimension = value; }
    void SetMipLevel(int value) { mipLevel = value; }
    void SetTexturePtr(const void* value) { pTexture = value; }

    TextureArrayRange& EditArrayRange() { return gfx::DataToAccessor(arrayRange); }
    ImageDimension GetImageDimension() const { return static_cast<ImageDimension>(imageDimension); }
    int GetMipLevel() const { return mipLevel; }

    detail::Caster<const void> GetTexturePtr() const {
        return detail::Caster<const void>(pTexture.ptr);
    }

    const TextureArrayRange& GetArrayRange() const { return gfx::DataToAccessor(arrayRange); }

    template <typename TTarget>
    void SetTexturePtr(const TTexture<TTarget>*);
};

class TextureMipRange : public detail::DataContainer<TextureMipRangeData> {
public:
    TextureMipRange() {}

    void SetDefault();

    void SetMinMipLevel(int value) { minMipLevel = value; }
    void SetMipCount(int value) { mipCount = value; }

    int GetMinMipLevel() const { return minMipLevel; }
    int GetMipCount() const { return mipCount; }
};

class TextureArrayRange : public detail::DataContainer<TextureArrayRangeData> {
public:
    TextureArrayRange() {}

    void SetDefault();

    void SetBaseArrayIndex(int value) { baseArrayIndex = value; }
    void SetArrayLength(int value) { arrayLength = value; }

    int GetBaseArrayIndex() const { return baseArrayIndex; }
    int GetArrayLength() const { return arrayLength; }
};

class TextureSubresourceRange : public detail::DataContainer<TextureSubresourceRangeData> {
public:
    TextureSubresourceRange() {}

    void SetDefault();

    TextureMipRange& EditMipRange() { return gfx::DataToAccessor(mipRange); }
    TextureArrayRange& EditArrayRange() { return gfx::DataToAccessor(arrayRange); }

    const TextureMipRange& GetMipRange() const { return gfx::DataToAccessor(mipRange); }
    const TextureArrayRange& GetArrayRange() const { return gfx::DataToAccessor(arrayRange); }
};

class TextureSubresource : public detail::DataContainer<TextureSubresourceData> {
public:
    TextureSubresource() {}

    void SetDefault();

    void SetMipLevel(int value) { mipLevel = value; }
    void SetArrayIndex(int value) { arrayIndex = value; }

    int GetMipLevel() const { return mipLevel; }
    int GetArrayIndex() const { return arrayIndex; }
};

class TextureCopyRegion : public detail::DataContainer<TextureCopyRegionData> {
public:
    TextureCopyRegion() {}

    void SetDefault();

    void SetOffsetU(int value) { offsetU = value; }
    void SetOffsetV(int value) { offsetV = value; }
    void SetOffsetW(int value) { offsetW = value; }
    void SetWidth(int value) { width = value; }
    void SetHeight(int value) { height = value; }
    void SetDepth(int value) { depth = value; }
    TextureSubresource& EditSubresource() { return gfx::DataToAccessor(subresource); }
    void SetArrayLength(int value) { arrayLength = value; }

    int GetOffsetU() const { return offsetU; }
    int GetOffsetV() const { return offsetV; }
    int GetOffsetW() const { return offsetW; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    int GetDepth() const { return depth; }

    const TextureSubresource& GetSubresource() const { return gfx::DataToAccessor(subresource); }

    int GetArrayLength() const { return arrayLength; }
};

class BufferTextureCopyRegion : public detail::DataContainer<BufferTextureCopyRegionData> {
public:
    BufferTextureCopyRegion() {}

    void SetDefault();

    void SetBufferOffset(int value) { bufferOffset = value; }
    void SetBufferImageWidth(int value) { bufferImageWidth = value; }
    void SetBufferImageHeight(int value) { bufferImageHeight = value; }

    TextureCopyRegion& EditTextureCopyRegion() { return gfx::DataToAccessor(textureCopyRegion); }

    int GetBufferOffset() const { return bufferOffset; }
    int GetBufferImageWidth() const { return bufferImageWidth; }
    int GetBufferImageHeight() const { return bufferImageHeight; }

    const TextureCopyRegion& GetTextureCopyRegion() const {
        return gfx::DataToAccessor(textureCopyRegion);
    }
};

}  // namespace nn::gfx