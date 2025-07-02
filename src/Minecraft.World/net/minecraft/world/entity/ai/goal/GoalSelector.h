#pragma once

#include <vector>

class GoalSelector {
public:
    class InternalGoal {};
    std::vector<GoalSelector::InternalGoal> internalGoals1;
    std::vector<GoalSelector::InternalGoal> internalGoals2;
    void* qword30;
    int dword38;
};