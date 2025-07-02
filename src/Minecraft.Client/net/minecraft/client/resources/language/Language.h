#pragma once

#include <string>

class Language {
public:
    static Language* getInstance();

    std::wstring getElement(const std::wstring&, ...);
};
