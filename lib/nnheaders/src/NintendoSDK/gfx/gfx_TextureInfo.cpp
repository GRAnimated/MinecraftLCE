#include <nn/gfx/gfx_TextureInfo.h>

namespace nn::gfx {

void TextureInfo::SetDefault() {
    SetImageStorageDimension(ImageStorageDimension_2d);
    SetImageFormat(ImageFormat_Undefined);
    SetGpuAccessFlags(0);
    SetTileMode(TileMode_Optimal);
    SetWidth(1);
    SetHeight(1);
    SetDepth(1);
    SetMipCount(1);
    SetArrayLength(0);
    SetSwizzle(0);
    SetMultiSampleCount(1);
}

void TextureViewInfo::SetDefault() {
    SetImageDimension(ImageDimension_2d);
    SetDepthStencilTextureMode(DepthStencilFetchMode_DepthComponent);
    SetImageFormat(ImageFormat_Undefined);
    EditSubresourceRange().SetDefault();
    SetChannelMapping(ChannelMapping_Red, ChannelMapping_Green, ChannelMapping_Blue,
                      ChannelMapping_Alpha);
    SetTexturePtr(nullptr);
}

void ColorTargetViewInfo::SetDefault() {
    SetImageDimension(ImageDimension_2d);
    SetImageFormat(ImageFormat_Undefined);
    SetMipLevel(0);
    EditArrayRange().SetDefault();
    SetTexturePtr(nullptr);
}

void DepthStencilViewInfo::SetDefault() {
    SetImageDimension(ImageDimension_2d);
    SetMipLevel(0);
    EditArrayRange().SetDefault();
    SetTexturePtr(nullptr);
}

void TextureMipRange::SetDefault() {
    SetMinMipLevel(0);
    SetMipCount(1);
}

void TextureArrayRange::SetDefault() {
    SetBaseArrayIndex(0);
    SetArrayLength(1);
}

void TextureSubresourceRange::SetDefault() {
    EditMipRange().SetDefault();
    EditArrayRange().SetDefault();
}

void TextureSubresource::SetDefault() {
    SetMipLevel(0);
    SetArrayIndex(0);
}

void TextureCopyRegion::SetDefault() {
    SetOffsetU(0);
    SetOffsetV(0);
    SetOffsetW(0);
    SetWidth(1);
    SetHeight(1);
    SetDepth(1);
    EditSubresource().SetDefault();
    SetArrayLength(1);
}

void BufferTextureCopyRegion::SetDefault() {
    SetBufferOffset(0);
    SetBufferImageWidth(0);
    SetBufferImageHeight(0);
    EditTextureCopyRegion().SetDefault();
}

}  // namespace nn::gfx