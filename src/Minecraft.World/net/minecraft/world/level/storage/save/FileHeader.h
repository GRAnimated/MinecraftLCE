#pragma once
#include "Minecraft.Client/ByteOrder.h"
#include "Minecraft.Client/ESavePlatform.h"
#include "Minecraft.Core/io/FileEntry.h"
#include <string>
#include <vector>

class FileHeader {
public:
    FileHeader();

    static ByteOrder getEndian(ESavePlatform platform);

    std::vector<FileEntry*> files;
    ESavePlatform platform;
    ByteOrder endian;
    short originalVersion;
    short version;
    void* unk2;
};
