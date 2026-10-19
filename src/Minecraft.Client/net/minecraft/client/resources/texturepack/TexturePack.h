#pragma once

#include <string>

class ArchiveFile;
class ColourTable;
class StructureManager;

class TexturePack {
public:
    TexturePack();
    virtual ~TexturePack();
    virtual bool unk1() = 0;
    virtual bool unk2() = 0;
    virtual bool hasAudio();
    virtual void setHasAudio(bool hasAudio);
    virtual bool unk3() = 0;
    virtual void loadData();
    virtual void unk4() = 0;
    virtual void unk5() = 0;
    virtual void unk6() = 0;
    virtual unsigned int getId() = 0;
    virtual std::wstring unk8() = 0;
    virtual std::wstring unk9() = 0;
    virtual std::wstring unk10() = 0;
    virtual void unk11() = 0;
    virtual bool unk12() = 0;
    virtual std::wstring unk13(const std::wstring&);
    virtual void* unk14();
    virtual std::wstring unk15(bool titleUpdate);
    virtual void unk16() = 0;
    virtual void unk17() = 0;
    virtual void loadColourTable() = 0;
    virtual void loadStructureManager() = 0;
    /** Retain recovered slots while their full signatures remain unresolved.
     */
    virtual void unk18() = 0;
    virtual void unk19() = 0;
    virtual void unk20() = 0;
    virtual unsigned char* getIcon(int* size) = 0;
    virtual unsigned char* getSecondaryIcon(int* size) = 0;
    virtual void unk23() = 0;
    virtual void unk24() = 0;
    virtual ColourTable* getColourTable() = 0;
    virtual StructureManager* getStructureManager() = 0;
    virtual ArchiveFile* getArchive() = 0;  // Original vtable offset 0x108.
    virtual void unk26() = 0;
    virtual void unk27() = 0;

    bool m_hasAudio;
};
