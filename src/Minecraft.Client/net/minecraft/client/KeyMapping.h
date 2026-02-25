#pragma once

#include <string>

class KeyMapping {
public:
    KeyMapping(const std::wstring&, int);

    std::wstring m_keyDescription;
    int m_keyCode;
};
