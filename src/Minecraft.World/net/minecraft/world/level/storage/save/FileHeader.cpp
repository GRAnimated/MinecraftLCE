#include "net/minecraft/world/level/storage/save/FileHeader.h"

FileHeader::FileHeader() {
    this->m_version = 10;
    this->m_unk2 = nullptr;
    this->m_originalVersion = 0;
    this->m_platform = ESavePlatform::Switch;
    this->m_endian = ByteOrder::LITTLE;
}
