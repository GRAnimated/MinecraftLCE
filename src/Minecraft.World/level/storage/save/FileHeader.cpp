#include "Minecraft.World/level/storage/save/FileHeader.h"

FileHeader::FileHeader() {
    this->version = 10;
    this->unk2 = nullptr;
    this->originalVersion = 0;
    this->platform = ESavePlatform::Switch;
    this->endian = ByteOrder::LITTLE;
}