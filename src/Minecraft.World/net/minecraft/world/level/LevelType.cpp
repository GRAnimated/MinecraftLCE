#include "net/minecraft/world/level/LevelType.h"

LevelType* LevelType::NORMAL;
LevelType* LevelType::FLAT;
LevelType* LevelType::LARGE_BIOMES;
LevelType* LevelType::AMPLIFIED;
LevelType* LevelType::CUSTOMIZED;
LevelType* LevelType::NORMAL_1_1;

LevelType* LevelType::TYPES[16];

LevelType::LevelType(int id, const std::wstring& name, int version) {
    this->_init(id, name, version);
}

LevelType::LevelType(int id, const std::wstring& name) {
    this->_init(id, name, 0);
}

void LevelType::_init(int id, const std::wstring& name, int version) {
    this->m_id = id;
    this->m_hasHelpText = false;
    this->m_name = name;
    this->m_version = version;
    this->m_selectableByUser = true;

    LevelType::TYPES[id] = this;
}

std::wstring LevelType::getGeneratorName() {
    return this->m_name;
}

int LevelType::getVersion() {
    return this->m_version;
}

LevelType* LevelType::setHasReplacement() {
    this->m_hasReplacement = true;
    return this;
}

LevelType* LevelType::setHasHelpText() {
    this->m_hasHelpText = true;
    return this;
}

LevelType* LevelType::setSelectableByUser(bool state) {
    this->m_selectableByUser = state;
    return this;
}

void LevelType::staticCtor() {
    LevelType::TYPES[0] = nullptr;
    LevelType::TYPES[1] = nullptr;
    LevelType::TYPES[2] = nullptr;
    LevelType::TYPES[3] = nullptr;
    LevelType::TYPES[4] = nullptr;
    LevelType::TYPES[5] = nullptr;
    LevelType::TYPES[6] = nullptr;
    LevelType::TYPES[7] = nullptr;
    LevelType::TYPES[8] = nullptr;
    LevelType::TYPES[9] = nullptr;
    LevelType::TYPES[10] = nullptr;
    LevelType::TYPES[11] = nullptr;
    LevelType::TYPES[12] = nullptr;
    LevelType::TYPES[13] = nullptr;
    LevelType::TYPES[14] = nullptr;
    LevelType::TYPES[15] = nullptr;

    LevelType::NORMAL = (new LevelType(0, L"default", 1))->setHasReplacement();
    LevelType::FLAT = new LevelType(1, L"flat");
    LevelType::LARGE_BIOMES = new LevelType(2, L"largeBiomes");
    LevelType::AMPLIFIED = (new LevelType(3, L"amplified"))->setHasHelpText();
    LevelType::CUSTOMIZED = new LevelType(4, L"customized");

    // where are other 3 types

    LevelType::NORMAL_1_1 = (new LevelType(8, L"default_1_1", 0))->setSelectableByUser(false);
}
