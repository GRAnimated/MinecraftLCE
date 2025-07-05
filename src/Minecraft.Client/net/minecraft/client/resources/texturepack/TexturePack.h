#pragma once

class TexturePack {
public:
    virtual ~TexturePack() = default;
    virtual void unk1();
    virtual void unk2();
    virtual bool hasAudio();
    virtual void setHasAudio(bool hasAudio);
    virtual void unk3();
    virtual void loadData();
    virtual void unk4();
    virtual void unk5();
    virtual void unk6();
    virtual unsigned int getId();
    virtual void unk8();
    virtual void unk9();
    virtual void unk10();
    virtual void unk11();
    virtual void unk12();
    virtual void unk13();
    virtual void unk14();
    virtual void unk15();
    virtual void unk16();
    virtual void unk17();
    virtual void loadColourTable();
    virtual void loadStructureManager();

    bool mHasAudio;
};
