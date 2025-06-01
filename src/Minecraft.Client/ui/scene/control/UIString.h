#pragma once

#include <memory>
#include <string>
class UIString {
public:
    class UIStringCore {
    public:
        UIStringCore(const std::wstring&);
    };

    UIString();
    UIString(wchar_t const*);
    UIString(const std::wstring&);

    bool needsUpdating();
    void setUpdated();

    std::shared_ptr<UIStringCore*> text;
};