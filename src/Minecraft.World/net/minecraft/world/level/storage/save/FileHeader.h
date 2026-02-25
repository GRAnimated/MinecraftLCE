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

    std::vector<FileEntry*> m_files;
    ESavePlatform m_platform;
    ByteOrder m_endian;
    short m_originalVersion;
    short m_version;
    void* m_unk2;
};
