#include "net/minecraft/client/ArchiveFile.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/resources/TexturePackRepository.h"

namespace {
// CMinecraftApp still has unrecovered storage beyond its partial declaration.
// Access this known field at its original offset without resizing that class.
__attribute__((always_inline)) inline ArchiveFile*& mediaArchive(CMinecraftApp* app) {
    return *reinterpret_cast<ArchiveFile**>(reinterpret_cast<unsigned char*>(app) + 0x210);
}
}  // namespace

void CMinecraftApp::loadMediaArchive() {
    std::wstring path(L"");
    path.assign(L"Common\\Media\\MediaNX.arc");
    if (!path.empty())
        mediaArchive(this) = new ArchiveFile(File(path));
}

bool CMinecraftApp::hasArchiveFile(const std::wstring& name, bool baseOnly) {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft && minecraft->m_texturePackRepository) {
        TexturePack* pack = minecraft->m_texturePackRepository->getSelected();
        if (pack && (baseOnly ^ true) && pack->unk1() && pack->getArchive()) {
            if (pack->getArchive()->hasFile(name))
                return true;
        }
    }
    return mediaArchive(this)->hasFile(name);
}

arrayWithLength<unsigned char> CMinecraftApp::getArchiveFile(const std::wstring& name, bool baseOnly) {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft && minecraft->m_texturePackRepository) {
        TexturePack* pack = minecraft->m_texturePackRepository->getSelected();
        if (pack && (baseOnly ^ true) && pack->unk1() && pack->getArchive()) {
            if (pack->getArchive()->hasFile(name))
                return pack->getArchive()->getFile(name);
        }
    }
    return mediaArchive(this)->getFile(name);
}
