#pragma once

#include "cstdint"
#include "java/io/File.h"
#include "texturepack/DefaultTexturePack.h"
#include <cstddef>
#include <unordered_map>
#include <vector>

class Minecraft;

class TexturePackRepository {
public:
    TexturePackRepository(File, Minecraft*);

    void addDebugPacks();
    TexturePack* getSelected();
    bool isUsingDefault();

    static TexturePack* sDefaultTexturePack;

    void* m_unk1;
    void* m_unk2;
    Minecraft* m_minecraft;
    File m_file;
    File m_file2;
    std::vector<TexturePack*>* m_texturePacks;
    std::vector<TexturePack*> m_packs;
    std::unordered_map<unsigned int, TexturePack*> m_texturePackMap;
    TexturePack* m_selectedTexturePack;
    void* m_unk12;
    // unknown if this is meant to be here
    bool m_unk13;
    // unsigned char padding[0xA8];
};

static_assert(offsetof(TexturePackRepository, m_texturePacks) == 0x48, "Original pack list offset");
static_assert(offsetof(TexturePackRepository, m_texturePackMap) == 0x68, "Original pack index offset");
static_assert(offsetof(TexturePackRepository, m_selectedTexturePack) == 0x90, "Original selection offset");
static_assert(sizeof(TexturePackRepository) == 0xa8, "Original repository layout");
