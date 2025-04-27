#pragma once
#include <string>
#include "Minecraft.Client/ESavePlatform.h"
#include "Minecraft.Client/ByteOrder.h"

class FileHeader {
    FileHeader();

    static ByteOrder getEndian(ESavePlatform platform);

    std::wstring filename;
    ESavePlatform platform;
    ByteOrder endian;
    short originalVersion;
    short version;
    void *unk2;
};
