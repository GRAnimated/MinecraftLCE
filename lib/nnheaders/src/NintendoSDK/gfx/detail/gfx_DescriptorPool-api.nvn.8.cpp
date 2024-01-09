#include <nn/gfx/detail/gfx_DescriptorPool-api.nvn.8.h>

#include <nn/gfx/detail/gfx_Buffer-api.nvn.8.h>
#include <nn/gfx/detail/gfx_Device-api.nvn.8.h>
#include <nn/gfx/detail/gfx_MemoryPool-api.nvn.8.h>
#include <nn/gfx/detail/gfx_Sampler-api.nvn.8.h>
#include <nn/gfx/detail/gfx_Texture-api.nvn.8.h>
#include <nn/gfx/gfx_DescriptorPoolInfo.h>
#include <nn/gfx/gfx_DescriptorSlot.h>
#include <nn/util/util_BytePtr.h>

#include "gfx_NvnHelper.h"

namespace nn::gfx::detail {

namespace {

const size_t g_DescriptorSlotIncrementSize[3] = {16, 1, 1};

}  // namespace

size_t DescriptorPoolImpl<ApiVariationNvn8>::CalculateDescriptorPoolSize(
    DeviceImpl<ApiVariationNvn8>* pDevice, const DescriptorPoolInfo& info) {
    switch (info.GetDescriptorPoolType()) {
    case DescriptorPoolType_TextureView: {
        int reservedTextures = 0;
        nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                            NVN_DEVICE_INFO_RESERVED_TEXTURE_DESCRIPTORS, &reservedTextures);
        int textureDescriptorSize = 0;
        nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice, NVN_DEVICE_INFO_TEXTURE_DESCRIPTOR_SIZE,
                            &textureDescriptorSize);

        return info.GetSlotCount() * textureDescriptorSize;
    }

    case DescriptorPoolType_Sampler: {
        int reservedSamplers = 0;
        nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                            NVN_DEVICE_INFO_RESERVED_SAMPLER_DESCRIPTORS, &reservedSamplers);
        int samplerDescriptorSize = 0;
        nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice, NVN_DEVICE_INFO_SAMPLER_DESCRIPTOR_SIZE,
                            &samplerDescriptorSize);
        return info.GetSlotCount() * samplerDescriptorSize;
    }

    case DescriptorPoolType_BufferView:
        return size_t(16) * info.GetSlotCount();

    default:
        NN_UNEXPECTED_DEFAULT;
        break;
    }
}

size_t DescriptorPoolImpl<ApiVariationNvn8>::GetDescriptorPoolAlignment(
    DeviceImpl<ApiVariationNvn8>* pDevice, const DescriptorPoolInfo& info) {
    switch (info.GetDescriptorPoolType()) {
    case DescriptorPoolType_TextureView: {
        int textureDescriptorSize = 0;
        nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice, NVN_DEVICE_INFO_TEXTURE_DESCRIPTOR_SIZE,
                            &textureDescriptorSize);
        return textureDescriptorSize;
    }

    case DescriptorPoolType_Sampler: {
        int samplerDescriptorSize = 0;
        nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice, NVN_DEVICE_INFO_SAMPLER_DESCRIPTOR_SIZE,
                            &samplerDescriptorSize);
        return samplerDescriptorSize;
    }

    case DescriptorPoolType_BufferView:
        return 4;

    default:
        NN_UNEXPECTED_DEFAULT;
        break;
    }
}

ptrdiff_t DescriptorPoolImpl<ApiVariationNvn8>::GetDescriptorSlotIncrementSize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice, DescriptorPoolType type) {
    return g_DescriptorSlotIncrementSize[type];
}

DescriptorPoolImpl<ApiVariationNvn8>::DescriptorPoolImpl() {}
DescriptorPoolImpl<ApiVariationNvn8>::~DescriptorPoolImpl() {}

void DescriptorPoolImpl<ApiVariationNvn8>::Initialize(DeviceImpl<ApiVariationNvn8>* pDevice,
                                                      const DescriptorPoolInfo& info,
                                                      MemoryPoolImpl<ApiVariationNvn8>* pMemoryPool,
                                                      ptrdiff_t memoryPoolOffset,
                                                      [[maybe_unused]] size_t memoryPoolSize) {
    descriptorPoolType = info.GetDescriptorPoolType();
    slotCount = info.GetSlotCount();

    if (descriptorPoolType == DescriptorPoolType_BufferView) {
        pDescriptorPool = nn::util::BytePtr(pMemoryPool->ToData()->pMemory, memoryPoolOffset).Get();
    } else {
        pDescriptorPool = nvnDescriptorPool;

        int reservedEntries = 0;
        int maxEntries = 0;
        if (descriptorPoolType == DescriptorPoolType_TextureView) {
            nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                                NVN_DEVICE_INFO_RESERVED_TEXTURE_DESCRIPTORS, &reservedEntries);
            nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                                NVN_DEVICE_INFO_MAX_TEXTURE_POOL_SIZE, &maxEntries);

            nvnTexturePoolInitialize(static_cast<NVNtexturePool*>(pDescriptorPool.ptr),
                                     pMemoryPool->ToData()->pNvnMemoryPool, memoryPoolOffset,
                                     info.GetSlotCount());
        } else {
            nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                                NVN_DEVICE_INFO_RESERVED_SAMPLER_DESCRIPTORS, &reservedEntries);
            nvnDeviceGetInteger(pDevice->ToData()->pNvnDevice,
                                NVN_DEVICE_INFO_MAX_SAMPLER_POOL_SIZE, &maxEntries);

            nvnSamplerPoolInitialize(static_cast<NVNsamplerPool*>(pDescriptorPool.ptr),
                                     pMemoryPool->ToData()->pNvnMemoryPool, memoryPoolOffset,
                                     info.GetSlotCount());
        }

        reservedSlots = reservedEntries;
    }

    flags.SetBit(Flag_Shared, false);
    state = State_Initialized;
}

void DescriptorPoolImpl<ApiVariationNvn8>::Finalize(
    [[maybe_unused]] DeviceImpl<ApiVariationNvn8>* pDevice) {
    switch (descriptorPoolType) {
    case DescriptorPoolType_TextureView:
        nvnTexturePoolFinalize(pDescriptorPool);
        break;
    case DescriptorPoolType_Sampler:
        nvnSamplerPoolFinalize(pDescriptorPool);
        break;

    default:
        break;
    }

    pDescriptorPool = nullptr;
    state = State_NotInitialized;
}

void DescriptorPoolImpl<ApiVariationNvn8>::BeginUpdate() {
    state = State_Begun;
}

void DescriptorPoolImpl<ApiVariationNvn8>::EndUpdate() {
    state = State_Initialized;
}

void DescriptorPoolImpl<ApiVariationNvn8>::SetBufferView(int indexSlot,
                                                         const GpuAddress& gpuAddress,
                                                         size_t size) {
    nn::util::BytePtr pSlot(pDescriptorPool,
                            g_DescriptorSlotIncrementSize[descriptorPoolType] * indexSlot);

    *pSlot.Get<NVNbufferAddress>() = Nvn::GetBufferAddress(gpuAddress);
    *pSlot.Advance(sizeof(NVNbufferAddress)).Get<size_t>() = size;
}

void DescriptorPoolImpl<ApiVariationNvn8>::SetSampler(
    int indexSlot, const SamplerImpl<ApiVariationNvn8>* pSampler) {
    nvnSamplerPoolRegisterSampler(pDescriptorPool, indexSlot, pSampler->ToData()->pNvnSampler);
}

void DescriptorPoolImpl<ApiVariationNvn8>::SetTextureView(
    int indexSlot, const TextureViewImpl<ApiVariationNvn8>* pTextureView) {
    nvnTexturePoolRegisterTexture(pDescriptorPool, indexSlot, pTextureView->ToData()->pNvnTexture,
                                  pTextureView->ToData()->pNvnTextureView);
}

void DescriptorPoolImpl<ApiVariationNvn8>::SetImage(
    int indexSlot, const TextureViewImpl<ApiVariationNvn8>* pImage) {
    nvnTexturePoolRegisterImage(pDescriptorPool, indexSlot, pImage->ToData()->pNvnTexture,
                                pImage->ToData()->pNvnTextureView);
}
void DescriptorPoolImpl<ApiVariationNvn8>::SetBufferTextureView(
    int indexSlot, const BufferTextureViewImpl<ApiVariationNvn8>* pBufferTexture) {
    nvnTexturePoolRegisterTexture(pDescriptorPool, indexSlot, pBufferTexture->ToData()->pNvnTexture,
                                  nullptr);
}

void DescriptorPoolImpl<ApiVariationNvn8>::SetBufferImage(
    int indexSlot, const BufferTextureViewImpl<ApiVariationNvn8>* pBufferImage) {
    nvnTexturePoolRegisterImage(pDescriptorPool, indexSlot, pBufferImage->ToData()->pNvnTexture,
                                nullptr);
}

void DescriptorPoolImpl<ApiVariationNvn8>::GetDescriptorSlot(DescriptorSlot* pOutDescriptorSlot,
                                                             int indexSlot) const {
    switch (descriptorPoolType) {
    case DescriptorPoolType_TextureView:
    case DescriptorPoolType_Sampler:
        pOutDescriptorSlot->ToData()->value = indexSlot;
        break;

    case DescriptorPoolType_BufferView:
        pOutDescriptorSlot->ToData()->value = reinterpret_cast<uintptr_t>(
            nn::util::BytePtr(pDescriptorPool.ptr, size_t(16) * indexSlot).Get());
        break;

    default:
        NN_UNEXPECTED_DEFAULT;
        break;
    }
}

int DescriptorPoolImpl<ApiVariationNvn8>::GetDescriptorSlotIndex(
    const DescriptorSlot& descriptorSlot) const {
    if (descriptorPoolType == DescriptorPoolType_BufferView) {
        return static_cast<int>(
                   nn::util::ConstBytePtr(pDescriptorPool.ptr)
                       .Distance(reinterpret_cast<const void*>(descriptorSlot.ToData()->value))) /
               16;
    }

    return descriptorSlot.ToData()->value;
}

}  // namespace nn::gfx::detail