#pragma once

#include "cstdint"
#include "java/io/File.h"
#include "texturepack/DefaultTexturePack.h"
#include <unordered_map>

class Minecraft;

class TexturePackRepository {
public:
    TexturePackRepository(File, Minecraft*);

    void addDebugPacks();
    bool getSelected();

    static DefaultTexturePack* sDefaultTexturePack;

    void* m_unk1;
    void* m_unk2;
    Minecraft* m_minecraft;
    File m_file;
    File m_file2;
    std::vector<TexturePack>* m_texturePacks;
    void* m_unk80d;
    void* m_unk88d;
    void* m_unk96d;
    std::unordered_map<unsigned int, TexturePack>* m_texturePackMap;
    void* m_unk8;
    void* m_unk9;
    void* m_unk10;
    float m_unk11;
    DefaultTexturePack* m_defaultTexturePack;
    void* m_unk12;
    // unknown if this is meant to be here
    bool m_unk13;
    // unsigned char padding[0xA8];
};
