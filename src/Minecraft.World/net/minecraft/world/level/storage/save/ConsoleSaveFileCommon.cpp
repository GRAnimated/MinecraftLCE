#include "ConsoleSaveFileCommon.h"

ESavePlatform ConsoleSaveFileCommon::getSavePlatform() {
    return this->getPlatform();
}

void ConsoleSaveFileCommon::setLocalPlatform() {
    this->m_header.m_platform = Switch;
}

void ConsoleSaveFileCommon::setPlatform(ESavePlatform platform) {
    this->m_header.m_platform = platform;
}

ByteOrder ConsoleSaveFileCommon::getSaveEndian() {
    return this->m_header.m_endian;
}

ByteOrder ConsoleSaveFileCommon::getLocalEndian() {
    return LITTLE;
}

void ConsoleSaveFileCommon::setEndian(ByteOrder order) {
    this->m_header.m_endian = order;
}
