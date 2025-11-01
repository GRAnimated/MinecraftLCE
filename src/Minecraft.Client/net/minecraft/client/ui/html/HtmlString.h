#pragma once

#include <string>
#include <vector>

class HtmlString {
public:
    static std::wstring Compose(std::vector<HtmlString>*);
};
