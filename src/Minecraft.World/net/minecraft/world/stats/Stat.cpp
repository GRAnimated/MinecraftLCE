#include "net/minecraft/world/stats/Stat.h"

Stat::Formatter* Stat::DEFAULT_FORMAT;
std::vector<Stat*>* Stat::ALL_STATS = new std::vector<Stat*>;
std::unordered_map<int, Stat*>* Stat::BY_ID = new std::unordered_map<int, Stat*>;

Stat::Stat(int id, const std::wstring& name, Formatter* formatter)
    : m_id(id), m_name(name), m_formatter(formatter) {
    initializeFlags();
}
Stat::Stat(int id, const std::wstring& name) : m_id(id), m_name(name), m_formatter(DEFAULT_FORMAT) {
    initializeFlags();
}
Stat::~Stat() {}
void Stat::initializeFlags() {
    m_flag = false;
    m_flagWord = 0;
}
Stat* Stat::setFlag() {
    m_flag = true;
    return this;
}
Stat* Stat::registerStat(bool addToList) {
    if (addToList)
        ALL_STATS->push_back(this);
    std::pair<int, Stat*> value(m_id, this);
    BY_ID->insert(value);
    return this;
}
bool Stat::isAchievement() {
    return false;
}
void Stat::setIndependent() {
    m_independent = true;
}
bool Stat::getFlag1() {
    return m_flag1;
}
bool Stat::getFlag2() {
    return m_flag2;
}
bool Stat::getFlag0() {
    return m_flag0;
}
void Stat::setFlag2(bool value) {
    m_flag2 = value;
}
void Stat::setFlag1(bool value) {
    m_flag1 = value;
}
void Stat::setFlag0(bool value) {
    m_flag0 = value;
}
bool Stat::isFlagClear() {
    return !m_flag;
}
void Stat::reservedHook() {}
