#pragma once

#include <string>

class KeyMapping {
public:
    KeyMapping(std::wstring const&, int);

private:
    std::wstring mName;
    int mKey;
};
