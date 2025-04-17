#pragma once
#include <string>

class User {
    public:
    static void staticCtor();

    User(const std::wstring &name, const std::wstring &session);

    std::wstring mName;
    std::wstring mSession;
    std::wstring unk;
};