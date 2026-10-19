#include "net/minecraft/world/stats/Stat.h"

Stat::Formatter* Stat::DEFAULT_FORMAT;  // name guessed
std::vector<Stat*>* Stat::ALL_STATS = new std::vector<Stat*>;
std::unordered_map<int, Stat*>* Stat::BY_ID = new std::unordered_map<int, Stat*>;

// name guessed
Stat::Stat(int id, const std::wstring& name, Formatter* formatter)
    : m_id(id), m_name(name), m_formatter(formatter) {
    initializeFlags();
}
// name guessed
Stat::Stat(int id, const std::wstring& name) : m_id(id), m_name(name), m_formatter(DEFAULT_FORMAT) {
    initializeFlags();
}
// name guessed
Stat::~Stat() {}
// name guessed
void Stat::initializeFlags() {
    m_flag = false;
    m_flagWord = 0;
}
// name guessed
Stat* Stat::setFlag() {
    m_flag = true;
    return this;
}
// name guessed
Stat* Stat::registerStat(bool addToList) {
    if (addToList)
        ALL_STATS->push_back(this);
    std::pair<int, Stat*> value(m_id, this);
    BY_ID->insert(value);
    return this;
}
// name guessed
bool Stat::isAchievement() {
    return false;
}
// name guessed
void Stat::setIndependent() {
    m_independent = true;
}
// name guessed
bool Stat::getFlag1() {
    return m_flag1;
}
// name guessed
bool Stat::getFlag2() {
    return m_flag2;
}
// name guessed
bool Stat::getFlag0() {
    return m_flag0;
}
// name guessed
void Stat::setFlag2(bool value) {
    m_flag2 = value;
}
// name guessed
void Stat::setFlag1(bool value) {
    m_flag1 = value;
}
// name guessed
void Stat::setFlag0(bool value) {
    m_flag0 = value;
}
// name guessed
bool Stat::isFlagClear() {
    return !m_flag;
}
// name guessed
void Stat::reservedHook() {}
