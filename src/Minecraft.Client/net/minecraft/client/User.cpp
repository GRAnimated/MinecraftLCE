#include "net/minecraft/client/User.h"

User::User(const std::wstring& name, const std::wstring& session) {
    this->m_name = name;
    this->m_session = session;
}
