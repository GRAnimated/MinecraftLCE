#pragma once
#include "TexturePack.h"
#include "java/io/File.h"
#include <string>

class AbstractTexturePack : public TexturePack {
public:
    AbstractTexturePack(unsigned int, File* file, const std::wstring& name, TexturePack* pack);

    void loadDefaultColourTable();

    char padding[0xC8];
};