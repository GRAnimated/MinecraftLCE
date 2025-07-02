#include "CMinecraftApp.h"

#include "Minecraft.World/level/gamemode/GameType.h"

bool CMinecraftApp::isXuidNotch(PlayerUID* id) {
    return 0;
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
        return unk & 8 | (16 * (GameType::SURVIVAL->getId() & 3)) | 0x3C81;
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
    return this->mChangingSessionType;
}

bool CMinecraftApp::GetGameStarted() {
    return this->mGameStarted;
}
