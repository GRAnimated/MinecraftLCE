#include "ConsoleSaveFileCommon.h"

ESavePlatform ConsoleSaveFileCommon::getSavePlatform() {
    return this->getPlatform();
}

void ConsoleSaveFileCommon::setLocalPlatform() {
    this->header.platform = Switch;
}

void ConsoleSaveFileCommon::setPlatform(ESavePlatform platform) {
    this->header.platform = platform;
}

ByteOrder ConsoleSaveFileCommon::getSaveEndian() {
    return this->header.endian;
}

ByteOrder ConsoleSaveFileCommon::getLocalEndian() {
    return LITTLE;
}

void ConsoleSaveFileCommon::setEndian(ByteOrder order) {
    this->header.endian = order;
}