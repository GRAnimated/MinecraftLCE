#pragma once

#include "java/io/FileEntry.h"
#include "net/minecraft/client/ByteOrder.h"
#include "net/minecraft/client/ESavePlatform.h"
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
