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
    ESavePlatform getPlatform() { return this->m_platform; }
    void setPlatform(ESavePlatform platform) { this->m_platform = platform; }
    ByteOrder getEndian() { return this->m_endian; }
    void setEndian(ByteOrder order) { this->m_endian = order; }
    void setLocalPlatform() {
        this->m_platform = Switch;
        this->m_endian = LITTLE;
    }
    static ByteOrder getLocalEndian() { return LITTLE; }

    std::vector<FileEntry*> m_files;
    ESavePlatform m_platform;
    ByteOrder m_endian;
    short m_originalVersion;
    short m_version;
    void* m_unk2;
};
