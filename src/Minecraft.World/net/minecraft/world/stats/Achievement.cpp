#include "net/minecraft/world/stats/Achievement.h"

#include "AchievementLocalization.h"
#include "net/minecraft/world/item/ItemInstance.h"

// name guessed
Achievement::Achievement(int id, const std::wstring& name, int x, int y, Item* icon, Achievement* parent)
    : Stat(id + 0x500000, std::wstring(L"achievement.").append(name)), m_x(x), m_y(y), m_parent(parent),
      m_description(achievementDescription(std::wstring(L"achievement.").append(name).append(L".desc"))),
      m_icon(new ItemInstance(icon)) {}
// name guessed
Achievement::Achievement(int id, const std::wstring& name, int x, int y, Block* icon, Achievement* parent)
    : Stat(id + 0x500000, std::wstring(L"achievement.").append(name)), m_x(x), m_y(y), m_parent(parent),
      m_description(achievementDescription(std::wstring(L"achievement.").append(name).append(L".desc"))),
      m_icon(new ItemInstance(icon)) {}
Achievement::~Achievement() {}
// name guessed
Achievement* Achievement::setFlag() {
    m_flag = true;
    return this;
}
// name guessed
Achievement* Achievement::setSpecial() {
    m_special = true;
    return this;
}
// name guessed
Achievement* Achievement::registerStat(bool addToList) {
    Stat::registerStat(addToList);
    Achievements::ALL->push_back(this);
    return this;
}
// name guessed
bool Achievement::isAchievement() {
    return true;
}
// name guessed
Achievement* Achievement::setIndependent() {
    Stat::setIndependent();
    return this;
}
// name guessed
int Achievement::getAchievementId() {
    return m_id - 0x500000;
}

// name guessed
std::wstring achievementDescription(const std::wstring&, ...) {
    return L"";
}
