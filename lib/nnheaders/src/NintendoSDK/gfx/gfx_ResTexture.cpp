#include <nn/gfx/gfx_ResTexture.h>

namespace nn::gfx {

size_t ResTextureFile::GetMaxFileAlignment() {
    return 0x20000;
}

bool ResTextureFile::IsValid(const void* ptr) {
    auto pFileHeader = static_cast<const nn::util::BinaryFileHeader*>(ptr);
    return pFileHeader->IsValid(Signature, MajorVersion, MinorVersion, MicroVersion);
}

ResTextureFile* ResTextureFile::ResCast(void* ptr) {
    value_type* pData = static_cast<value_type*>(ptr);
    ResTextureFile* pRet = ToAccessor(pData);

    if (!pRet->fileHeader.IsRelocated()) {
        pRet->fileHeader.GetRelocationTable()->Relocate();
    }

    return pRet;
}

}  // namespace nn::gfx