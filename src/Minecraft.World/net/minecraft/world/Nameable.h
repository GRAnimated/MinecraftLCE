#pragma once

#include <string>

class Nameable {
public:
    Nameable();

    virtual std::wstring getName() = 0;
    virtual std::wstring getCustomName() = 0;
    virtual bool hasCustomName() = 0;
    virtual std::wstring getDisplayName() = 0;
};
