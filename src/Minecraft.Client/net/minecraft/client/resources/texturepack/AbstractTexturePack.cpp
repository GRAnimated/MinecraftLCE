#include "java/io/FileInputStream.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureManager.h"

#include "AbstractTexturePack.h"

// name guessed
// NON_MATCHING | score: 55 (lower is better)
AbstractTexturePack::AbstractTexturePack(unsigned int id, File* file, const std::wstring& name,
                                         TexturePack* pack)
    : m_id(id), m_name(name), m_file(file), m_unk90(nullptr), m_unk98(0), m_unka0(nullptr), m_unka8(0),
      m_parent(pack), m_colourTable(nullptr), m_structureManager(nullptr), m_unkd0(-1) {
    // The original constructor leaves the field at 0xc8 untouched.
}
// name guessed
AbstractTexturePack::~AbstractTexturePack() = default;

// name guessed
unsigned int AbstractTexturePack::getId() {
    return m_id;
}
// name guessed
std::wstring AbstractTexturePack::unk8() {
    return m_metadata1;
}
// name guessed
std::wstring AbstractTexturePack::unk9() {
    return m_metadata3;
}
// name guessed
std::wstring AbstractTexturePack::unk10() {
    return m_metadata4;
}
// name guessed
void AbstractTexturePack::loadIcon() {}
// name guessed
void AbstractTexturePack::unk28() {}
// name guessed
void AbstractTexturePack::unk29() {}
// name guessed
void AbstractTexturePack::unk30() {}

// name guessed
void AbstractTexturePack::unk19() {}
// name guessed
void AbstractTexturePack::unk20() {}

// name guessed
unsigned char* AbstractTexturePack::getIcon(int* size) {
    if (!m_unk98 || !m_unk90)
        loadIcon();
    *size = m_unk98;
    return static_cast<unsigned char*>(m_unk90);
}

// name guessed
unsigned char* AbstractTexturePack::getSecondaryIcon(int* size) {
    if (!m_unka8 || !m_unka0)
        unk28();
    *size = m_unka8;
    return static_cast<unsigned char*>(m_unka0);
}

// name guessed
ColourTable* AbstractTexturePack::getColourTable() {
    return m_colourTable;
}
// name guessed
StructureManager* AbstractTexturePack::getStructureManager() {
    return m_structureManager;
}
// name guessed
ArchiveFile* AbstractTexturePack::getArchive() {
    return nullptr;
}

[[noreturn]] void packLoadError(void*, const wchar_t*,
                                ...) asm("_ZN20CConsoleMinecraftApp14FatalLoadErrorEPKwz");

// name guessed
void AbstractTexturePack::loadColourTable() {
    loadDefaultColourTable();
    loadHTMLColourTable();
}

// name guessed
// NON_MATCHING | score: 847 (lower is better)
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

// name guessed
void AbstractTexturePack::loadHTMLColourTable() {
    if (CConsoleMinecraftApp::sInstance.hasArchiveFile(L"HTMLColours.col", false)) {
        auto data = CConsoleMinecraftApp::sInstance.getArchiveFile(L"HTMLColours.col", false);
        m_colourTable->read(data.m_data, data.m_length);
        delete[] data.m_data;
    }
}

// name guessed
// NON_MATCHING | score: 100 (lower is better)
void AbstractTexturePack::loadStructureManager() {
    delete m_structureManager;
    m_structureManager = new StructureManager(Minecraft::GetInstance()->getFixerUpper());
}
