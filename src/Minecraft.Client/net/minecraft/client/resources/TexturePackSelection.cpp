#include "net/minecraft/client/resources/TexturePackRepository.h"

TexturePack* TexturePackRepository::getSelected() {
    if (m_selectedTexturePack && m_selectedTexturePack->unk1() && m_selectedTexturePack->unk2())
        return m_selectedTexturePack;
    return sDefaultTexturePack;
}

bool TexturePackRepository::isUsingDefault() {
    return getSelected() == sDefaultTexturePack;
}
