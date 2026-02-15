#include "net/minecraft/client/resources/TexturePackRepository.h"
#include <unordered_map>

// NON_MATCHING | Score: 3105 (lower is better)
// confusion
TexturePackRepository::TexturePackRepository(File file, Minecraft* mc) {
    this->m_file = File();
    this->m_file2 = File();
    this->m_unk80d = nullptr;
    this->m_unk88d = nullptr;
    this->m_unk96d = nullptr;
    this->m_texturePackMap = nullptr;
    this->m_unk8 = nullptr;
    this->m_unk9 = nullptr;
    this->m_unk10 = nullptr;
    this->m_unk11 = 1.0;

    if (!sDefaultTexturePack) {
        sDefaultTexturePack = new DefaultTexturePack();
    }

    this->m_unk13 = false;
    this->m_defaultTexturePack = nullptr;
    this->m_texturePacks = new std::vector<TexturePack>();
    this->m_minecraft = mc;

    this->m_texturePacks->push_back(*sDefaultTexturePack);
    (*this->m_texturePackMap)[sDefaultTexturePack->getId()] = *sDefaultTexturePack;

    this->m_defaultTexturePack = sDefaultTexturePack;
    sDefaultTexturePack->loadColourTable();
    sDefaultTexturePack->loadStructureManager();

    this->m_unk1 = nullptr;
    this->m_unk2 = nullptr;
    this->m_unk12 = nullptr;
}
