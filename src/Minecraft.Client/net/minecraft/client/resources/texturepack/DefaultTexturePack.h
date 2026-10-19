#pragma once

#include "AbstractTexturePack.h"

class DefaultTexturePack : public AbstractTexturePack {
public:
    DefaultTexturePack();
    bool unk1() override;
    bool unk2() override;
    bool hasAudio() override;
    bool unk3() override;
    bool unk12() override;
    void* unk14() override;
    std::wstring unk8() override;
    std::wstring unk9() override;
    void loadIcon() override;
    void unk29() override;
    void unk30() override;
    void unk18() override;
    void unk19() override;
};
