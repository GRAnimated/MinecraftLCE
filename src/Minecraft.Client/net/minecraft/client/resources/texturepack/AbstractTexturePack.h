#pragma once

#include "java/io/File.h"
#include "net/minecraft/client/resources/texturepack/TexturePack.h"
#include <cstddef>
#include <string>

class AbstractTexturePack : public TexturePack {
public:
    AbstractTexturePack(unsigned int, File* file, const std::wstring& name, TexturePack* pack);
    ~AbstractTexturePack() override;

    void loadDefaultColourTable();
    void loadHTMLColourTable();

    void unk4() override;
    void unk5() override;
    void unk6() override;
    unsigned int getId() override;
    std::wstring unk8() override;
    std::wstring unk9() override;
    std::wstring unk10() override;
    void unk11() override;
    void* unk14() override = 0;
    void unk16() override;
    void unk17() override;
    void loadColourTable() override;
    void loadStructureManager() override;
    void unk18() override;
    void unk19() override;
    void unk20() override;
    unsigned char* getIcon(int* size) override;
    unsigned char* getSecondaryIcon(int* size) override;
    void unk23() override;
    void unk24() override;
    ColourTable* getColourTable() override;
    StructureManager* getStructureManager() override;
    ArchiveFile* getArchive() override;
    void unk26() override;
    void unk27() override;
    virtual void loadIcon();
    virtual void unk28();
    virtual void unk29();
    virtual void unk30();

    unsigned int m_id;
    std::wstring m_name;
    File* m_file;
    std::wstring m_metadata1;
    std::wstring m_metadata2;
    std::wstring m_metadata3;
    std::wstring m_metadata4;
    void* m_unk90;
    int m_unk98;
    void* m_unka0;
    int m_unka8;
    TexturePack* m_parent;
    ColourTable* m_colourTable;
    StructureManager* m_structureManager;
    void* m_unkc8;
    int m_unkd0;
};

static_assert(offsetof(AbstractTexturePack, m_id) == 0xc, "Original base tail-padding reuse");
static_assert(offsetof(AbstractTexturePack, m_file) == 0x28, "Original pack file offset");
static_assert(offsetof(AbstractTexturePack, m_colourTable) == 0xb8, "Original colour table offset");
static_assert(offsetof(AbstractTexturePack, m_structureManager) == 0xc0, "Original structure manager offset");
static_assert(sizeof(AbstractTexturePack) == 0xd8, "Original abstract pack layout");
