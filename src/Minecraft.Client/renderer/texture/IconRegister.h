#pragma once
#include <string>

class IconRegister{
public:
    virtual ~IconRegister();
    virtual void* registerIcon(std::wstring const&) = 0;
    virtual int getIconType() = 0;
};