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
    UIString(const wchar_t*);
    UIString(const std::wstring&);

    bool needsUpdating();
    void setUpdated();

    std::shared_ptr<UIStringCore*> text;
};
