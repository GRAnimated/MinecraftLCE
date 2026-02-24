#include "net/minecraft/client/resources/texturepack/TexturePack.h"

bool TexturePack::hasAudio() {
    return this->m_hasAudio;
}
void TexturePack::setHasAudio(bool hasAudio) {
    this->m_hasAudio = hasAudio;
}

void TexturePack::loadData() {}
