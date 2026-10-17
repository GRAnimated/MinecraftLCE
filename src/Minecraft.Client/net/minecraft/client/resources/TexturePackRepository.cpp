#include "net/minecraft/client/resources/TexturePackRepository.h"

#include <unordered_map>

TexturePack* TexturePackRepository::sDefaultTexturePack;

TexturePackRepository::TexturePackRepository(File file, Minecraft* mc) {
    if (!sDefaultTexturePack) {
        sDefaultTexturePack = new DefaultTexturePack();
    }

    this->m_unk13 = false;
    this->m_selectedTexturePack = nullptr;
    this->m_texturePacks = new std::vector<TexturePack*>();
    this->m_minecraft = mc;

    this->m_texturePacks->push_back(sDefaultTexturePack);
    this->m_texturePackMap[sDefaultTexturePack->getId()] = sDefaultTexturePack;

    this->m_selectedTexturePack = sDefaultTexturePack;
    sDefaultTexturePack->loadColourTable();
    sDefaultTexturePack->loadStructureManager();

    this->m_unk1 = nullptr;
    this->m_unk2 = nullptr;
    this->m_unk12 = nullptr;
}
