#include "AbstractTexturePack.h"
#include "java/io/FileInputStream.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureManager.h"

[[noreturn]] void packLoadError(void*, const wchar_t*,
                                ...) asm("_ZN20CConsoleMinecraftApp14FatalLoadErrorEPKwz");

void AbstractTexturePack::loadColourTable() {
    loadDefaultColourTable();
    loadHTMLColourTable();
}

void AbstractTexturePack::loadDefaultColourTable() {
    File file(TexturePack::unk15(true).append(L"res/colours.col"));
    if (!file.exists())
        packLoadError(nullptr, nullptr, 251);
    const auto length = file.length();
    arrayWithLength<unsigned char> buffer(static_cast<unsigned int>(length), true);
    FileInputStream input(file);
    input.read(buffer, 0, static_cast<unsigned int>(length));
    input.close();
    delete m_colourTable;
    m_colourTable = new ColourTable(buffer.m_data, buffer.m_length);
    delete[] buffer.m_data;
}

void AbstractTexturePack::loadHTMLColourTable() {
    if (CConsoleMinecraftApp::sInstance.hasArchiveFile(L"HTMLColours.col", false)) {
        auto data = CConsoleMinecraftApp::sInstance.getArchiveFile(L"HTMLColours.col", false);
        m_colourTable->read(data.m_data, data.m_length);
        delete[] data.m_data;
    }
}

void AbstractTexturePack::loadStructureManager() {
    delete m_structureManager;
    m_structureManager = new StructureManager(Minecraft::GetInstance()->getFixerUpper());
}
