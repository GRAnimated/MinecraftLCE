#include "net/minecraft/client/CMinecraftApp.h"

#include "net/minecraft/client/ArchiveFile.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/resources/TexturePackRepository.h"

#include "net/minecraft/world/level/gamemode/GameType.h"

bool CMinecraftApp::isXuidNotch(PlayerUID* id) {
    return false;
}

int CMinecraftApp::GetGameHostOption(unsigned int unk, eGameHostOption option) {
    // TODO: still unreadable
    switch (option) {
    case 0:
        return unk & 3;
        break;
    case 3:
        return unk & 4;
        break;
    case 4:
        return unk & 8;
        break;
    case 5:
        return (unk & 8) | (16 * (GameType::SURVIVAL->getId() & 3)) | 0x3C81;
        break;
    case 6:
        return (unk >> 4) & 3;
        break;
    case 7:
        return unk & 0x40;
        break;
    case 8:
        return unk & 0x80;
        break;
    case 9:
        return unk & 0x100;
        break;
    case 10:
        return unk & 0x200;
        break;
    case 11:
        return unk & 0x400;
        break;
    case 12:
        return unk & 0x800;
        break;
    case 13:
        return unk & 0x1000;
        break;
    case 14:
        return unk & 0x2000;
        break;
    case 15:
        return unk & 0x1C000;
        break;
    case 16:
        return unk & 0x4000;
        break;
    case 17:
        return unk & 0x8000;
        break;
    case 18:
        return unk & 0x10000;
        break;
    case 20:
        return (unk >> 20) & 7;
        break;
    case 21:
        return (unk & 0x80000000) == 0;
        break;
    case 22:
        return unk & 0x40000;
        break;
    case 23:
        return unk & 0x80000;
        break;
    case 24:
        return ((unk >> 23) & 1) == 0;
        break;
    case 25:
        return unk & 0x1000000;
        break;
    case 26:
        return ((unk >> 25) & 1) == 0;
        break;
    case 27:
        return ((unk >> 26) & 1) == 0;
        break;
    case 28:
        return ((unk >> 27) & 1) == 0;
        break;
    case 29:
        return ((unk >> 28) & 1) == 0;
        break;
    case 30:
        return ((unk >> 29) & 1) == 0;
        break;
    case 31:
        return unk & 0x40000000;
        break;
    case 32:
        return unk;
        break;
    default:
        unk = 0;
    }

    return unk;
}

bool CMinecraftApp::GetChangingSessionType() {
    return this->m_changingSessionType;
}

bool CMinecraftApp::GetGameStarted() {
    return this->m_gameStarted;
}

/** Custom access to the archive field beyond the partial CMinecraftApp layout. */
#define MEDIA_ARCHIVE(app) (*reinterpret_cast<ArchiveFile**>(reinterpret_cast<unsigned char*>(app) + 0x210))

void CMinecraftApp::loadMediaArchive() {
    std::wstring path(L"");
    path.assign(L"Common\\Media\\MediaNX.arc");
    if (!path.empty())
        MEDIA_ARCHIVE(this) = new ArchiveFile(File(path));
}

// NON_MATCHING | score: 305 (lower is better)
bool CMinecraftApp::hasArchiveFile(const std::wstring& name, bool baseOnly) {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft && minecraft->m_texturePackRepository) {
        TexturePack* pack = minecraft->m_texturePackRepository->getSelected();
        if (pack && (baseOnly ^ true) && pack->unk1() && pack->getArchive()) {
            if (pack->getArchive()->hasFile(name))
                return true;
        }
    }
    return MEDIA_ARCHIVE(this)->hasFile(name);
}

// NON_MATCHING | score: 305 (lower is better)
arrayWithLength<unsigned char> CMinecraftApp::getArchiveFile(const std::wstring& name, bool baseOnly) {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft && minecraft->m_texturePackRepository) {
        TexturePack* pack = minecraft->m_texturePackRepository->getSelected();
        if (pack && (baseOnly ^ true) && pack->unk1() && pack->getArchive()) {
            if (pack->getArchive()->hasFile(name))
                return pack->getArchive()->getFile(name);
        }
    }
    return MEDIA_ARCHIVE(this)->getFile(name);
}

#undef MEDIA_ARCHIVE
