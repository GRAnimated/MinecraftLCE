#pragma once

#include <nn/gfx/gfx_Device.h>
#include <nn/gfx/gfx_ResTextureData.h>
#include <nn/gfx/gfx_TextureInfo.h>
#include <nn/util.h>
#include <nn/util/AccessorBase.h>

namespace nn::gfx {

class ResTexture : public nn::util::AccessorBase<ResTextureData> {
    NN_NO_COPY(ResTexture);

public:
    static const int Signature = 0x49545242;

    static ResTexture* ToAccessor(value_type*);
    static ResTexture& ToAccessor(value_type&);
    static const ResTexture* ToAccessor(const value_type*);
    static const ResTexture& ToAccessor(const value_type&);

    TextureInfo* GetTextureInfo();
    const TextureInfo* GetTextureInfo() const;
    detail::Caster<void> GetTexture();
    detail::Caster<const void> GetTexture() const;
    detail::Caster<void> GetTextureView();
    detail::Caster<const void> GetTextureView() const;
    const char* GetName() const;
    size_t GetDataSize() const;
    ResUserData* GetUserData(int);
    const ResUserData* GetUserData(int) const;
    const nn::util::ResDic* GetUserDataDic() const;
    void SetUserDescriptorSlot(const DescriptorSlot&);
    void GetUserDescriptorSlot(DescriptorSlot*) const;
};

class ResTextureFile : public nn::util::AccessorBase<ResTextureFileData> {
    NN_NO_COPY(ResTextureFile);

public:
    static const int64_t Signature = 0x58544E42;
    static const int MajorVersion = 4;
    static const int MinorVersion = 0;
    static const int MicroVersion = 0;

    static size_t GetMaxFileAlignment();

    static ResTextureFile* ToAccessor(value_type* pData) {
        return static_cast<ResTextureFile*>(pData);
    }

    static ResTextureFile& ToAccessor(value_type& data) {
        return static_cast<ResTextureFile&>(data);
    }

    static const ResTextureFile* ToAccessor(const value_type*);
    static const ResTextureFile& ToAccessor(const value_type&);
    static bool IsValid(const void*);
    static ResTextureFile* ResCast(void*);

    ResTexture* GetResTexture(int);
    const ResTexture* GetResTexture(int) const;
    const nn::util::ResDic* GetTextureDic() const;
    nn::util::BinaryFileHeader* GetBinaryFileHeader();
    const nn::util::BinaryFileHeader* GetBinaryFileHeader() const;

    template <typename TTarget>
    void Initialize(TDevice<TTarget>*);

    template <typename TTarget>
    void Initialize(TDevice<TTarget>*, TMemoryPool<TTarget>*, ptrdiff_t, size_t);

    template <typename TTarget>
    void Finalize(TDevice<TTarget>*);
};

}  // namespace nn::gfx