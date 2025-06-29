#pragma once
#include "Minecraft.Core/io/File.h"
#include "TexturePack.h"
#include <string>

class AbstractTexturePack : public TexturePack {
public:
    AbstractTexturePack(unsigned int, File *file, const std::wstring &name, TexturePack *pack);

    void loadDefaultColourTable();

    char padding[0xC8];
};