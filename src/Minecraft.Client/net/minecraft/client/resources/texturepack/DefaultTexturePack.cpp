#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/client/ui/StringIDs.h"

#include "DefaultTexturePack.h"

// name guessed
bool DefaultTexturePack::unk1() {
    return true;
}
// name guessed
bool DefaultTexturePack::unk2() {
    return true;
}
// name guessed
bool DefaultTexturePack::hasAudio() {
    return false;
}
// name guessed
bool DefaultTexturePack::unk3() {
    return false;
}
// name guessed
bool DefaultTexturePack::unk12() {
    return true;
}
// name guessed
void* DefaultTexturePack::unk14() {
    return nullptr;
}

// name guessed
// NON_MATCHING | score: 0 (lower is better)
DefaultTexturePack::DefaultTexturePack()
    : AbstractTexturePack(0, nullptr, std::wstring(L10N::GetString(StringIDs::Minecraft)), nullptr) {
    loadIcon();
    unk30();
    unk29();
    loadColourTable();
}

// name guessed
void DefaultTexturePack::loadIcon() {
    if (CConsoleMinecraftApp::sInstance.hasArchiveFile(L"Graphics\\TexturePackIcon.png", false)) {
        auto data = CConsoleMinecraftApp::sInstance.getArchiveFile(L"Graphics\\TexturePackIcon.png", false);
        m_unk90 = data.m_data;
        m_unk98 = data.m_length;
    }
}

// name guessed
void DefaultTexturePack::unk29() {
    m_metadata3.assign(L"LOCALISE ME: The default look of Minecraft");
}

// name guessed
// NON_MATCHING | score: 405 (lower is better)
void DefaultTexturePack::unk30() {
    m_metadata1.assign(L10N::GetString(StringIDs::Minecraft));
}
// name guessed
std::wstring DefaultTexturePack::unk8() {
    return std::wstring(L10N::GetString(StringIDs::Minecraft));
}
// name guessed
std::wstring DefaultTexturePack::unk9() {
    return std::wstring(
        L10N::GetString(static_cast<int>(StringIDs::TheClassicMinecraftTexturesIconsAndUserInterface)));
}
// name guessed
void DefaultTexturePack::unk19() {}
