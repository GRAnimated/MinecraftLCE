#pragma once

#include <string>

class ConsoleInputStream {
public:
    virtual ~ConsoleInputStream();
    virtual void info(const std::wstring&) = 0;
    virtual void warn(const std::wstring&) = 0;
    virtual std::wstring getConsoleName() = 0;
};