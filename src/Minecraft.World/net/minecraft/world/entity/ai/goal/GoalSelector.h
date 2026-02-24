#pragma once

#include <vector>

class GoalSelector {
public:
    class InternalGoal {};

    void disableControlFlag(int);
    void enableControlFlag(int);

    std::vector<GoalSelector::InternalGoal> m_internalGoals1;
    std::vector<GoalSelector::InternalGoal> m_internalGoals2;
    void* m_qword30;
    int m_dword38;
};
