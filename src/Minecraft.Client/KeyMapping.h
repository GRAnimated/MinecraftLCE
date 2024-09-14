#pragma once

#include <string>

class KeyMapping {
public:
    KeyMapping(std::wstring const&, int);

    std::wstring mKeyDescription;
    int mKeyCode;
};
