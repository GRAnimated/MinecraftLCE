#pragma once

#include "java/io/File.h"
#include "net/minecraft/client/resources/texturepack/TexturePack.h"
#include <string>

class AbstractTexturePack : public TexturePack {
public:
    AbstractTexturePack(unsigned int, File* file, const std::wstring& name, TexturePack* pack);

    void loadDefaultColourTable();

    char m_padding[0xC8];
};
