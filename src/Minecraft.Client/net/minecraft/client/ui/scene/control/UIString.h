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
    UIString(int);

    bool needsUpdating();
    void setUpdated();

    std::shared_ptr<UIStringCore*> m_text;
};
