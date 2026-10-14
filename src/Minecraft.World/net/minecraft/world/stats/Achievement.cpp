#include "net/minecraft/world/stats/Achievement.h"

#include "AchievementLocalization.h"
#include "net/minecraft/world/item/ItemInstance.h"

Achievement::Achievement(int id, const std::wstring& name, int x, int y, Item* icon, Achievement* parent)
    : Stat(id + 0x500000, std::wstring(L"achievement.").append(name)), m_x(x), m_y(y), m_parent(parent),
      m_description(achievementDescription(std::wstring(L"achievement.").append(name).append(L".desc"))),
      m_icon(new ItemInstance(icon)) {}
Achievement::Achievement(int id, const std::wstring& name, int x, int y, Block* icon, Achievement* parent)
    : Stat(id + 0x500000, std::wstring(L"achievement.").append(name)), m_x(x), m_y(y), m_parent(parent),
      m_description(achievementDescription(std::wstring(L"achievement.").append(name).append(L".desc"))),
      m_icon(new ItemInstance(icon)) {}
Achievement::~Achievement() {}
Achievement* Achievement::setFlag() {
    m_flag = true;
    return this;
}
Achievement* Achievement::setSpecial() {
    m_special = true;
    return this;
}
Achievement* Achievement::registerStat(bool addToList) {
    Stat::registerStat(addToList);
    Achievements::ALL->push_back(this);
    return this;
}
bool Achievement::isAchievement() {
    return true;
}
Achievement* Achievement::setIndependent() {
    Stat::setIndependent();
    return this;
}
int Achievement::getAchievementId() {
    return m_id - 0x500000;
}
