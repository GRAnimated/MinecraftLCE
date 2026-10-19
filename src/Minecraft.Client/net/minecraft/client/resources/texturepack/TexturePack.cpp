#include "net/minecraft/client/resources/texturepack/TexturePack.h"

// name guessed
TexturePack::TexturePack() : m_hasAudio(false) {}
// name guessed
// NON_MATCHING | score: 805 (lower is better)
TexturePack::~TexturePack() {}

// name guessed
std::wstring TexturePack::unk13(const std::wstring& value) {
    return value;
}
// name guessed
void* TexturePack::unk14() {
    return nullptr;
}
// name guessed
std::wstring TexturePack::unk15(bool titleUpdate) {
    std::wstring value;
    if (titleUpdate)
        value.assign(L"Common\\res\\TitleUpdate\\");
    else
        value.assign(L"Common/");
    return value;
}

bool TexturePack::hasAudio() {
    return this->m_hasAudio;
}
void TexturePack::setHasAudio(bool hasAudio) {
    this->m_hasAudio = hasAudio;
}

void TexturePack::loadData() {}
