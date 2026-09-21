#include "ConsoleSaveFileCommon.h"

ESavePlatform ConsoleSaveFileCommon::getSavePlatform() {
    return this->m_header.getPlatform();
}

void ConsoleSaveFileCommon::setLocalPlatform() {
    this->m_header.setLocalPlatform();
}

void ConsoleSaveFileCommon::setPlatform(ESavePlatform platform) {
    this->m_header.setPlatform(platform);
}

ByteOrder ConsoleSaveFileCommon::getSaveEndian() {
    return this->m_header.getEndian();
}

ByteOrder ConsoleSaveFileCommon::getLocalEndian() {
    return FileHeader::getLocalEndian();
}

void ConsoleSaveFileCommon::setEndian(ByteOrder order) {
    this->m_header.setEndian(order);
}
