#pragma once

#include <nn/gfx/gfx_DescriptorSlot.h>
#include <nn/gfx/gfx_ResUserData.h>
#include <nn/gfx/gfx_TextureInfoData.h>
#include <nn/util/util_BinaryFormat.h>
#include <nn/util/util_ResDic.h>

namespace nn::gfx {

class ResTexture;
struct ResTextureContainerData;

struct ResTextureData {
    nn::util::BinaryBlockHeader blockHeader;
    TextureInfoData textureInfoData;
    uint32_t textureDataSize;
    uint32_t alignment;
    Bit8 channelMapping[4];
    Bit8 imageDimension;
    char reserved[3];
    nn::util::BinPtrToString pName;
    nn::util::BinTPtr<ResTextureContainerData> pResTextureContainerData;
    nn::util::BinTPtr<nn::util::BinTPtr<void>> pMipPtrArray;
    nn::util::BinTPtr<ResUserData> pUserDataArray;
    nn::util::BinTPtr<void> pTexture;
    nn::util::BinTPtr<void> pTextureView;
    DescriptorSlotData userDescriptorSlot;
    nn::util::BinTPtr<nn::util::ResDic> pUserDataDic;
};

struct ResTextureContainerData {
    char targetPlatform[4];
    uint32_t textureCount;
    nn::util::BinTPtr<nn::util::BinTPtr<ResTexture>> pTexturePtrArray;
    nn::util::BinTPtr<void> pTextureData;
    nn::util::BinTPtr<nn::util::ResDic> pTextureDic;
    nn::util::BinTPtr<void> pTextureMemoryPool;
    nn::util::BinTPtr<void> pCurrentMemoryPool;
    uint32_t memoryPoolOffsetBase;
    char reserved[4];
};

struct ResTextureFileData {
    nn::util::BinaryFileHeader fileHeader;
    ResTextureContainerData textureContainerData;
};

}  // namespace nn::gfx