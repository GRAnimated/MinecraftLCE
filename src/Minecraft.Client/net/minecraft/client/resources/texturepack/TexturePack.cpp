#include "net/minecraft/client/resources/texturepack/TexturePack.h"

TexturePack::TexturePack() : m_hasAudio(false) {}
TexturePack::~TexturePack() {}

std::wstring TexturePack::unk13(const std::wstring& value) {
    return value;
}
void* TexturePack::unk14() {
    return nullptr;
}
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
