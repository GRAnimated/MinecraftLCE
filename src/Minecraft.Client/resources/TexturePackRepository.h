#pragma once
#include "Minecraft.Core/io/File.h"
#include "cstdint"
#include "texturepack/DefaultTexturePack.h"
#include "unordered_map"

class Minecraft;

class TexturePackRepository {
public:
    TexturePackRepository(File, Minecraft*);

    void addDebugPacks();
    bool getSelected();

    static DefaultTexturePack *sDefaultTexturePack;

    void * unk1;
    void * unk2;
    Minecraft *mMinecraft;
    File mFile;
    File mFile2;
    std::vector<TexturePack> *mTexturePacks;
    void * unk_80d;
    void * unk_88d;
    void * unk_96d;
    std::unordered_map<unsigned int, TexturePack> *mTexturePackMap;
    void * unk8;
    void * unk9;
    void * unk10;
    float unk11;
    DefaultTexturePack *mDefaultTexturePack;
    void * unk12;
    // unknown if this is meant to be here
    bool unk13;
    // unsigned char padding[0xA8];
};