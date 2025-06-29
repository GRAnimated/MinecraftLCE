#include "TexturePackRepository.h"
#include <unordered_map>

// NON_MATCHING | Score: 3105 (lower is better)
// confusion
TexturePackRepository::TexturePackRepository(File file, Minecraft *mc) {
    this->mFile = File();
    this->mFile2 = File();
    this->unk_80d = nullptr;
    this->unk_88d = nullptr;
    this->unk_96d = nullptr;
    this->mTexturePackMap = nullptr;
    this->unk8 = nullptr;
    this->unk9 = nullptr;
    this->unk10 = nullptr;
    this->unk11 = 1.0;

    if (!sDefaultTexturePack) {
        sDefaultTexturePack = new DefaultTexturePack();
    }

    this->unk13 = false;
    this->mDefaultTexturePack = nullptr;
    this->mTexturePacks = new std::vector<TexturePack>();
    this->mMinecraft = mc;

    this->mTexturePacks->push_back(*sDefaultTexturePack);
    (*this->mTexturePackMap)[sDefaultTexturePack->getId()] = *sDefaultTexturePack;

    this->mDefaultTexturePack = sDefaultTexturePack;
    sDefaultTexturePack->loadColourTable();
    sDefaultTexturePack->loadStructureManager();

    this->unk1 = nullptr;
    this->unk2 = nullptr;
    this->unk12 = nullptr;
}