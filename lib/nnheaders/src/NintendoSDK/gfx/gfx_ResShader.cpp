#include <nn/gfx/gfx_ResShader.h>

namespace nn::gfx {

size_t ResShaderFile::GetMaxFileAlignment() {
    return 4096;
}

bool ResShaderFile::IsValid(const void* ptr) {
    const nn::util::BinaryFileHeader* pFileHeader =
        static_cast<const nn::util::BinaryFileHeader*>(ptr);

    return pFileHeader->IsValid(Signature, MajorVersion, MinorVersion, MicroVersion);
}

ResShaderFile* ResShaderFile::ResCast(void* ptr) {
    value_type* pData = static_cast<value_type*>(ptr);
    ResShaderFile* pRet = ToAccessor(pData);

    if (!pRet->fileHeader.IsRelocated()) {
        pRet->fileHeader.GetRelocationTable()->Relocate();
    }

    return pRet;
}

}  // namespace nn::gfx