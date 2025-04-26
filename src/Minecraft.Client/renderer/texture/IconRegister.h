#pragma once
#include <string>

class Texture;

class IconRegister {
public:
    virtual ~IconRegister();
    virtual Texture* registerIcon(std::wstring const&) = 0;
    virtual int getIconType() = 0;
};