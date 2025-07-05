#include "net/minecraft/client/resources/texturepack/TexturePack.h"

bool TexturePack::hasAudio() {
    return this->mHasAudio;
}
void TexturePack::setHasAudio(bool hasAudio) {
    this->mHasAudio = hasAudio;
}

void TexturePack::loadData() {}
