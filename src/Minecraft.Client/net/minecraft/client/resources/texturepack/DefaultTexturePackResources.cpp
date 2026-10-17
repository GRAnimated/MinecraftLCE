#include "DefaultTexturePack.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/client/ui/StringIDs.h"

DefaultTexturePack::DefaultTexturePack()
    : AbstractTexturePack(0, nullptr, std::wstring(L10N::GetString(StringIDs::Minecraft)), nullptr) {
    loadIcon();
    unk30();
    unk29();
    loadColourTable();
}

void DefaultTexturePack::loadIcon() {
    if (CConsoleMinecraftApp::sInstance.hasArchiveFile(L"Graphics\\TexturePackIcon.png", false)) {
        auto data = CConsoleMinecraftApp::sInstance.getArchiveFile(L"Graphics\\TexturePackIcon.png", false);
        m_unk90 = data.m_data;
        m_unk98 = data.m_length;
    }
}

void DefaultTexturePack::unk29() {
    m_metadata3.assign(L"LOCALISE ME: The default look of Minecraft");
}

void DefaultTexturePack::unk30() {
    m_metadata1.assign(L10N::GetString(StringIDs::Minecraft));
}
std::wstring DefaultTexturePack::unk8() {
    return std::wstring(L10N::GetString(StringIDs::Minecraft));
}
std::wstring DefaultTexturePack::unk9() {
    return std::wstring(
        L10N::GetString(static_cast<int>(StringIDs::TheClassicMinecraftTexturesIconsAndUserInterface)));
}
void DefaultTexturePack::unk19() {}
