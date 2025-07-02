#include "User.h"

User::User(const std::wstring& name, const std::wstring& session) {
    this->mName = name;
    this->mSession = session;
}
