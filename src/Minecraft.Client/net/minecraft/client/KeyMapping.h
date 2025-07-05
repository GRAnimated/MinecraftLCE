#pragma once

#include <string>

class KeyMapping {
public:
    KeyMapping(const std::wstring&, int);

    std::wstring mKeyDescription;
    int mKeyCode;
};
