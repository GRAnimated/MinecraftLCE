#pragma once

#include <string>
#include <unordered_map>

class ItemIdFix {
public:
    static void staticCtor();
    static std::unordered_map<int, std::wstring> ID_TO_NAME;
};
