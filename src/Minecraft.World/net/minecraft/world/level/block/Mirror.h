#pragma once

#include <string>

class Mirror {
public:
    enum eTYPE { MIRROR_0, MIRROR_LEFT_RIGHT, MIRROR_FRONT_BACK };

    static Mirror* NONE;
    static Mirror* LEFT_RIGHT;

    Mirror(const std::wstring& name, eTYPE type);

    std::wstring m_name;
    eTYPE m_type;
};

static_assert(sizeof(Mirror) == 0x20, "Switch mirror layout");
