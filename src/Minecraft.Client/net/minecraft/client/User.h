#pragma once

#include <string>

class User {
public:
    static void staticCtor();

    User(const std::wstring& name, const std::wstring& session);

    std::wstring m_name;
    std::wstring m_session;
    std::wstring m_unk;
};
