#include "AbstractTexturePack.h"

AbstractTexturePack::AbstractTexturePack(unsigned int id, File* file, const std::wstring& name,
                                         TexturePack* pack)
    : m_id(id), m_name(name), m_file(file), m_unk90(nullptr), m_unk98(0), m_unka0(nullptr), m_unka8(0),
      m_parent(pack), m_colourTable(nullptr), m_structureManager(nullptr), m_unkd0(-1) {
    // The original constructor leaves the field at 0xc8 untouched.
}
AbstractTexturePack::~AbstractTexturePack() = default;

unsigned int AbstractTexturePack::getId() {
    return m_id;
}
std::wstring AbstractTexturePack::unk8() {
    return m_metadata1;
}
std::wstring AbstractTexturePack::unk9() {
    return m_metadata3;
}
std::wstring AbstractTexturePack::unk10() {
    return m_metadata4;
}
void AbstractTexturePack::loadIcon() {}
void AbstractTexturePack::unk28() {}
void AbstractTexturePack::unk29() {}
void AbstractTexturePack::unk30() {}

void AbstractTexturePack::unk19() {}
void AbstractTexturePack::unk20() {}

unsigned char* AbstractTexturePack::getIcon(int* size) {
    if (!m_unk98 || !m_unk90)
        loadIcon();
    *size = m_unk98;
    return static_cast<unsigned char*>(m_unk90);
}

unsigned char* AbstractTexturePack::getSecondaryIcon(int* size) {
    if (!m_unka8 || !m_unka0)
        unk28();
    *size = m_unka8;
    return static_cast<unsigned char*>(m_unka0);
}

ColourTable* AbstractTexturePack::getColourTable() {
    return m_colourTable;
}
StructureManager* AbstractTexturePack::getStructureManager() {
    return m_structureManager;
}
ArchiveFile* AbstractTexturePack::getArchive() {
    return nullptr;
}
